#pragma once
#include "pipe.hpp"
#include "child_process.hpp"
#include <string>

class ParentProcess {
private:
    Pipe* pipe1;
    Pipe* pipe2;
    ChildProcess* child1;
    ChildProcess* child2;
    std::string file1, file2;

public:
    ParentProcess();
    ~ParentProcess();
    void start();  
};