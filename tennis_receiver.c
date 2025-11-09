/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file tennis_receiver.c
 * @brief Receives and returns SIGUSR1 signals to play "Signal Tennis".
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

    printf("\aReceiver: got volley %d from PID %d\n", volley, opponent_pid);
    if (volley >= MAX_VOLLEYS) {
        printf("Receiver: game over after %d volleys!\n", volley);
        exit(0);
    }

    // Random 1–2 s delay
    struct timespec ts = {1 + rand() % 2, 0};
    nanosleep(&ts, NULL);

    // Return the ball
    union sigval val;
    val.sival_int = volley + 1;
    sigqueue(opponent_pid, SIGUSR1, val);
    printf("Receiver: sent volley %d back!\n", volley + 1);
}

int main(void) {
    srand(time(NULL));

    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Receiver ready. PID = %d\n", getpid());
    while (1) pause();
}
