/**
 * Author: biebera@msoe.edu <Andrew Bieber>
 * Class: CPE 2600
 * Professor: Turney
 *
 * @file signal_handler.c
 * @brief Registers a signal handler for SIGINT. Prints a message when SIGINT is received.
 *
 * Note: AI (GPT-5) was used to generate skeletons and Javadoc-style comments
 * to explain my work thoroughly. All code written and verified by Andrew Bieber.
 */

/**
 * Modified by: Andrew Bieber
 * Brief summary of modifications:
 *  - Updated handler prototype to POSIX-compliant form
 *  - Prints message instead of exiting (can be terminated with SIGKILL)
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT — prints a message but does not exit.
 * @param sig Signal number (expected SIGINT)
 */
void handle_signal(int sig) {
    printf("\nCaught SIGINT (%d). Use SIGKILL to terminate.\n", sig);
}

int main(void) {
    // Register the handler for SIGINT
    if (signal(SIGINT, handle_signal) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("PID: %d — waiting for SIGINT (Ctrl+C)\n", getpid());

    // Wait indefinitely until a signal arrives
    while (1) {
        pause(); // POSIX way to suspend until signal
    }

    return 0;
}
