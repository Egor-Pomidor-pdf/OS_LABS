#include <iostream>
#include <fstream>
#include <string>
#include "../include/os.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "No filename provided" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    size_t mapped_size = 1024;
    std::string output_filename = argv[2];
    std::ofstream outfile(output_filename);
    int fd = OpenFile(filename);
    void *mapped_memory = MapFile(fd, mapped_size);
    CloseFile(fd);

    char *mem_ptr = static_cast<char *>(mapped_memory);
    size_t offset = 0;

    while (offset < mapped_size)
    {
        char *mem_ptr = static_cast<char *>(mapped_memory) + offset;
        if (mem_ptr[0] == 0)
        {
            continue;
        }

        std::string line(mem_ptr + 1);
        size_t len = line.find('\n');
        if (len != std::string::npos)
            line.resize(len);

        std::reverse(line.begin(), line.end());
        std::cout << line << std::endl;
        outfile << line << std::endl;

        mem_ptr[0] = 0;
        offset += len + 2;
        UnmapFile(mapped_memory, mapped_size);
        return 0;
    }
}