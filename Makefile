# ============================================================================
#  Andrew Bieber – CPE2600 Systems Programming
#  Lab 10: POSIX Signal Handling
#  Unified Makefile for all lab parts + Signal Tennis (extra credit)
# ============================================================================

CC      = gcc
CFLAGS  = -Wall -Werror -std=c17
TARGETS = signal_handler signal_alarm signal_segfault signal_sigaction \
           recv_signal send_signal tennis_server tennis_receiver

# ---------------------------------------------------------------------------
# Default target: build everything
# ---------------------------------------------------------------------------
all: $(TARGETS)

# Individual build rules -----------------------------------------------------
signal_handler: signal_handler.c
	$(CC) $(CFLAGS) signal_handler.c -o signal_handler

signal_alarm: signal_alarm.c
	$(CC) $(CFLAGS) signal_alarm.c -o signal_alarm

signal_segfault: signal_segfault.c
	$(CC) $(CFLAGS) signal_segfault.c -o signal_segfault

signal_sigaction: signal_sigaction.c
	$(CC) $(CFLAGS) signal_sigaction.c -o signal_sigaction

recv_signal: recv_signal.c
	$(CC) $(CFLAGS) recv_signal.c -o recv_signal

send_signal: send_signal.c
	$(CC) $(CFLAGS) send_signal.c -o send_signal

tennis_server: tennis_server.c
	$(CC) $(CFLAGS) tennis_server.c -o tennis_server

tennis_receiver: tennis_receiver.c
	$(CC) $(CFLAGS) tennis_receiver.c -o tennis_receiver

# ---------------------------------------------------------------------------
# Utility targets
# ---------------------------------------------------------------------------
clean:
	rm -f $(TARGETS) *.o

rebuild: clean all
