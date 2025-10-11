#pragma once
#include "pipe.hpp"
#include <string>

class ChildProcess {
private:
    ProcessHandle pid;
    Pipe* pipe;  
    std::string file_name;
    bool is_child1;

public:
    ChildProcess(Pipe* p, const std::string& f, bool is_c1);
    void execute();  
    ProcessHandle getPid() const { return pid; }
};