#pragma once
#include <string>
#include "os.h"


class ChildProcess
{
private:
    ProcessHandle pid;
    std::string mmap_filename;
    std::string file_name;
    bool is_child1;

public:
    ChildProcess(const std::string &mmap_f, const std::string &out_f, bool is_c1);
    void execute();
    ProcessHandle getPid() const { return pid; }
};