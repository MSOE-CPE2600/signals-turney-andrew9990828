#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_VOLLEYS 10
#define GAME_OVER   999  // special marker value

static pid_t opponent_pid = 0;

void handler(int sig, siginfo_t *info, void *ucontext) {
    (void)ucontext;
    opponent_pid = info->si_pid;
    int volley = info->si_value.sival_int;

    if (volley == GAME_OVER) {
        printf("Receiver: received GAME_OVER from PID %d — exiting.\n", opponent_pid);
        exit(0);
    }

    printf("Receiver: got volley %d from PID %d\n", volley, opponent_pid);
    if (volley >= MAX_VOLLEYS) {
        printf("Receiver: game over after %d volleys! notifying opponent...\n", volley);
        union sigval end;
        end.sival_int = GAME_OVER;
        sigqueue(opponent_pid, SIGUSR1, end);
        exit(0);
    }

    struct timespec ts = {1 + rand() % 2, 0};
    nanosleep(&ts, NULL);

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
