#include "../include/os.h"
#include <windows.h>
#include <iostream>
#include <string>

FileHandle OpenFile(const std::string &filename)
{
    HANDLE hFile = CreateFileA(
        filename.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        std::cerr << "OpenFile failed (" << GetLastError() << ")" << std::endl;

    return hFile;
}

void SetFileSize(FileHandle file, size_t size)
{
    LARGE_INTEGER li;
    li.QuadPart = size;
    if (!SetFilePointerEx(file, li, NULL, FILE_BEGIN) || !SetEndOfFile(file))
        std::cerr << "SetFileSize failed (" << GetLastError() << ")" << std::endl;
}

void* MapFile(FileHandle file, size_t size)
{
    HANDLE hMap = CreateFileMapping(file, NULL, PAGE_READWRITE, 0, (DWORD)size, NULL);
    if (!hMap)
    {
        std::cerr << "CreateFileMapping failed (" << GetLastError() << ")" << std::endl;
        return nullptr;
    }

    void* addr = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, size);
    CloseHandle(hMap);

    if (!addr)
        std::cerr << "MapViewOfFile failed (" << GetLastError() << ")" << std::endl;

    return addr;
}

void UnmapFile(void* mapped_memory, size_t /*size*/)
{
    if (!UnmapViewOfFile(mapped_memory))
        std::cerr << "UnmapViewOfFile failed (" << GetLastError() << ")" << std::endl;
}

void CloseFile(FileHandle file)
{
    if (!CloseHandle(file))
        std::cerr << "CloseFile failed (" << GetLastError() << ")" << std::endl;
}

// Создание дочернего процесса (без пайпов)
ProcessHandle CreateChildProcess(const char* exe, char* const* argv)
{
    std::string cmdline;
    for (int i = 0; argv[i]; ++i)
    {
        if (i > 0) cmdline += " ";
        cmdline += argv[i];
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL, (LPSTR)cmdline.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ")" << std::endl;
        return INVALID_HANDLE_VALUE;
    }

    CloseHandle(pi.hThread);
    return pi.hProcess;
}

int WaitProcess(ProcessHandle pid)
{
    WaitForSingleObject(pid, INFINITE);
    CloseHandle(pid);
    return 0;
}

ProcessHandle Fork() { std::cerr << "Fork not supported on Windows" << std::endl; return INVALID_HANDLE_VALUE; }
int Exec(const char* /*exe*/, char* const* /*argv*/) { std::cerr << "Exec not supported on Windows" << std::endl; return -1; }
