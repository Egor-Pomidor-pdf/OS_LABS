#include "../include/parent_process.hpp"
#include "../include/os.h"
#include <iostream>

ParentProcess::ParentProcess()
    : child1(nullptr), child2(nullptr)
{
}

ParentProcess::~ParentProcess()
{
    delete child1;
    delete child2;
}

void ParentProcess::start()
{
    std::string mmap_file_short, mmap_file_long;
    std::string out_file_short, out_file_long;

    std::cout << "Enter mmap file for short lines: ";
    std::getline(std::cin, mmap_file_short);
    std::cout << "Enter mmap file for long lines: ";
    std::getline(std::cin, mmap_file_long);
    std::cout << "Enter output file for short lines: ";
    std::getline(std::cin, out_file_short);
    std::cout << "Enter output file for long lines: ";
    std::getline(std::cin, out_file_long);

    const size_t mapped_size = 1024;
    void *mapped_short = nullptr;
    void *mapped_long = nullptr;

    int fd_short = OpenFile(mmap_file_short);
    SetFileSize(fd_short, mapped_size);
    mapped_short = MapFile(fd_short, mapped_size);
    CloseFile(fd_short);

    int fd_long = OpenFile(mmap_file_long);
    SetFileSize(fd_long, mapped_size);
    mapped_long = MapFile(fd_long, mapped_size);
    CloseFile(fd_long);

    child1 = new ChildProcess(mmap_file_short, out_file_short, false);
    child1->execute();

    child2 = new ChildProcess(mmap_file_long, out_file_long, false);
    child2->execute();

    std::cout << "Enter lines (empty line to end):" << std::endl;
    std::string line;
    size_t offset_short = 0;
    size_t offset_long = 0;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            break;

        const char *data = line.c_str();
        size_t len = line.size();

        if (len <= 10)
        {
            if (offset_short + len + 2 > mapped_size)
                break;
            char *mem_ptr = static_cast<char *>(mapped_short) + offset_short;
            memcpy(mem_ptr + 1, data, len);
            mem_ptr[len + 1] = '\n';
            mem_ptr[0] = 1;

            while (mem_ptr[0] != 0)
            {
            }

            offset_short += len + 2;
        }
        else
        {
            if (offset_long + len + 2 > mapped_size)
                break;
            char *mem_ptr = static_cast<char *>(mapped_long) + offset_long;
            memcpy(mem_ptr + 1, data, len);
            mem_ptr[len + 1] = '\n';
            mem_ptr[0] = 1;

            while (mem_ptr[0] != 0)
            {
            }

            offset_long += len + 2;
        }
    }

    std::cout << "Parent: input finished." << std::endl;

    WaitProcess(child1->getPid());
    WaitProcess(child2->getPid());

    std::cout << "Parent: children finished." << std::endl;

    if (mapped_short)
        UnmapFile(mapped_short, mapped_size);
    if (mapped_long)
        UnmapFile(mapped_long, mapped_size);
}
