#pragma once
#include "child_process.hpp"
#include <string>

class ParentProcess
{
private:
    ChildProcess *child1;
    ChildProcess *child2;
    std::string file1, file2;
    std::string filename;

public:
    ParentProcess();
    ~ParentProcess();
    void start();
};