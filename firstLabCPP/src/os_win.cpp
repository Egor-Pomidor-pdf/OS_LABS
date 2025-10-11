#include "../include/os.h"
#include <iostream> 

int CreatePipe(PipeHandle fd[2]) {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&fd[0], &fd[1], &saAttr, 0)) {
        std::cerr << "CreatePipe failed" << std::endl;
        return -1;
    }

    if (!SetHandleInformation(fd[1], HANDLE_FLAG_INHERIT, 0)) {
        std::cerr << "SetHandleInformation failed" << std::endl;
        return -1;
    }

    return 0;
}

int PipeRead(PipeHandle fd, char* buf, size_t size) {
    DWORD bytesRead;
    if (!ReadFile(fd, buf, size, &bytesRead, NULL)) {
        return -1;
    }
    return bytesRead;
}

int PipeWrite(PipeHandle fd, const char* buf, size_t size) {
    DWORD bytesWritten;
    if (!WriteFile(fd, buf, size, &bytesWritten, NULL)) {
        return -1;
    }
    return bytesWritten;
}

int ClosePipe(PipeHandle fd) {
    return !CloseHandle(fd);
}

ProcessHandle CreateChildProcess(const char* exe, char* const* argv, PipeHandle stdin_handle) {
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = stdin_handle;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    std::string cmdline;
    for (int i = 0; argv[i]; ++i) {
        if (i > 0) cmdline += " ";
        cmdline += argv[i];
    }

    if (!CreateProcessA(NULL, (LPSTR)cmdline.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ")" << std::endl;
        return INVALID_HANDLE_VALUE;
    }

    CloseHandle(pi.hThread);

    return pi.hProcess;
}

int WaitProcess(ProcessHandle pid) {
    WaitForSingleObject(pid, INFINITE);
    CloseHandle(pid);
    return 0;
}

int Dup2(PipeHandle oldfd, int newfd) {
    return 0;
}

ProcessHandle Fork() {
    std::cerr << "Fork not supported on Windows" << std::endl;
    return INVALID_HANDLE_VALUE;
}

int Exec(const char* exe, char* const* argv) {
    std::cerr << "Exec not supported on Windows" << std::endl;
    return -1;
}