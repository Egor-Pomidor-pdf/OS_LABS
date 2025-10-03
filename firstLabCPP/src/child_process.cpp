#include "../include/child_process.hpp"
#include "../include/os.h"

ChildProcess::ChildProcess(Pipe* p, const std::string& f, bool is_c1) 
    : pipe(p), file_name(f), is_child1(is_c1), pid(INVALID_PIPE_HANDLE) {}

void ChildProcess::execute() {
#ifdef _WIN32
    const char* exe = "child.exe";
#else
    const char* exe = "./child";
#endif
    char* argv[] = { (char*)"child", (char*)file_name.c_str(), NULL };
    pid = CreateChildProcess(exe, argv, pipe->getReadFd());
}