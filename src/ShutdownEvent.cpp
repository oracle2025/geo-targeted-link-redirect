#include "ShutdownEvent.hpp"

#include <semaphore.h>
#include <unistd.h>

#include <csignal>
#include <cstdlib>

namespace {

sem_t sem{0};//, 0};

void signalHandler(int /*signal*/)
{
    if (sem_post(&sem) == -1) {
        _exit(EXIT_FAILURE);
    }
}
} // namespace

int waitShutdownEvent()
{
    // Handle the shutdown procedure
    if (sem_init(&sem, 0, 0) == -1) {
        _exit(EXIT_FAILURE);
    }
    if (std::signal(SIGINT, signalHandler) == SIG_ERR) {
        _exit(EXIT_FAILURE);
    }
    if (std::signal(SIGTERM, signalHandler) == SIG_ERR) {
        _exit(EXIT_FAILURE);
    }

    if (sem_wait(&sem) != 0) {
        _exit(EXIT_FAILURE);
    }
    if (sem_destroy(&sem) != 0) {
        _exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
