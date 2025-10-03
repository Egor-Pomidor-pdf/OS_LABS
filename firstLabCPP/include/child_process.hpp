#pragma once
#include "pipe.hpp"
#include <string>

class ChildProcess {
private:
    ProcessHandle pid;
    Pipe* pipe;  // Ассоциированный пайп (stdin для child будет read end)
    std::string file_name;
    bool is_child1;

public:
    ChildProcess(Pipe* p, const std::string& f, bool is_c1);
    void execute();  // Запускает child с argv = {"child", file_name.c_str(), NULL}, redirect stdin to pipe read
    ProcessHandle getPid() const { return pid; }
};