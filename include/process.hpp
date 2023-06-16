#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "logger.hpp"
#include <cstdio>

extern "C" {
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
}

enum class ProcessState {
    None,
    Suspended,
    Active,
};

class Process
{
    Logger m_logger = Logger("Process");
    ProcessState m_state = ProcessState::None;
    int m_pipefd[2];
    pid_t m_child_pid;
    FILE *m_file;

public:
    FILE *getStdout() const;
    ProcessState getState() const;

    bool start(char *const *argv);
    bool suspend();
    bool resume();
    bool end();
};

#endif
