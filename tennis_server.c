/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file tennis_server.c
 * @brief Serves and plays "Signal Tennis" with another process.
 *
 * Note: AI (GPT-5) was used to generate skeletons and comments for clarity.
 * All code verified and executed by Andrew Bieber.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_VOLLEYS 10

static pid_t opponent_pid = 0;

void handler(int sig, siginfo_t *info, void *ucontext) {
    (void)ucontext;
    opponent_pid = info->si_pid;
    int volley = info->si_value.sival_int;

    printf("\aServer: got volley %d from PID %d\n", volley, opponent_pid);
    if (volley >= MAX_VOLLEYS) {
        printf("Server: game over after %d volleys!\n", volley);
        exit(0);
    }

    struct timespec ts = {1 + rand() % 2, 0};
    nanosleep(&ts, NULL);

    union sigval val;
    val.sival_int = volley + 1;
    sigqueue(opponent_pid, SIGUSR1, val);
    printf("Server: returned volley %d!\n", volley + 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    opponent_pid = (pid_t)atoi(argv[1]);
    srand(time(NULL));

    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Server ready. PID = %d → opponent PID = %d\n",
           getpid(), opponent_pid);

    // Serve first
    union sigval val;
    val.sival_int = 1;
    sigqueue(opponent_pid, SIGUSR1, val);
    printf("Server: served volley 1!\n");

    while (1) pause();
}
