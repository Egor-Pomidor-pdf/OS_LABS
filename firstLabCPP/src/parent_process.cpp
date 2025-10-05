#include "../include/parent_process.hpp"
#include <iostream>

ParentProcess::ParentProcess() 
    : pipe1(new Pipe()), pipe2(new Pipe()), child1(nullptr), child2(nullptr) {}

ParentProcess::~ParentProcess() {
    delete pipe1;
    delete pipe2;
    delete child1;
    delete child2;
}

void ParentProcess::start() {
    std::cout << "Enter filename for child1: ";
    std::getline(std::cin, file1);
    std::cout << "Enter filename for child2: ";
    std::getline(std::cin, file2);

    child1 = new ChildProcess(pipe1, file1, true);
    child1->execute();
    // Close read end in parent
    ClosePipe(pipe1->getReadFd());

    child2 = new ChildProcess(pipe2, file2, false);
    child2->execute();
    // Close read end in parent
    ClosePipe(pipe2->getReadFd());

    std::cout << "Enter lines (empty line to end):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        Pipe* target_pipe = (line.length() > 10) ? pipe2 : pipe1;
        target_pipe->write(line.c_str(), line.length());
        target_pipe->write("\n", 1); 
    }

    ClosePipe(pipe1->getWriteFd());
    ClosePipe(pipe2->getWriteFd());

    WaitProcess(child1->getPid());
    WaitProcess(child2->getPid());

    std::cout << "Parent: children finished." << std::endl;
}