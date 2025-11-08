#include "../include/child_process.hpp"
#include "../include/os.h"

ChildProcess::ChildProcess(const std::string &mmap_f, const std::string &out_f, bool is_c1)
    : mmap_filename(mmap_f), file_name(out_f), is_child1(is_c1), pid(INVALID_PIPE_HANDLE) {}

void ChildProcess::execute()
{
#ifdef _WIN32
    const char *exe = "child.exe";
#else
    const char *exe = "./child";
#endif
    char *argv[] = {(char *)"child", (char *)mmap_filename.c_str(), (char *)file_name.c_str(), NULL};
    pid = CreateChildProcess(exe, argv);
}