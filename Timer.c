#include "Timer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void printCurrentTime() {
  time_t now = time(0);
  char *time_str = ctime(&now);
  time_str[strlen(time_str) - 1] = '\0'; // Remove the newline character
  printf("\r%s", time_str);
  fflush(stdout); // Ensure the output is immediately printed}
}

void startTimer(double minutes) {
  // Convert minutes to milliseconds
  unsigned long total_milliseconds = minutes * 60 * 1000;

  // Get the starting tick count
  unsigned long start_time = GetTickCount();

  while (total_milliseconds > 0) {
    // Get the current tick count
    unsigned long current_time = GetTickCount();

    // Calculate elapsed time
    unsigned long elapsed_time = current_time - start_time;

    // Update total_milliseconds
    unsigned long remaining_milliseconds =
        (total_milliseconds > elapsed_time) ? total_milliseconds - elapsed_time
                                            : 0;

    // Calculate minutes and seconds
    unsigned long mins_left = remaining_milliseconds / (60 * 1000);
    unsigned long secs_left = (remaining_milliseconds % (60 * 1000)) / 1000;

    // Print remaining time
    printf("\rTime remaining: %02lu:%02lu", mins_left, secs_left);
    fflush(stdout);

    // Sleep for 1 second
    Sleep(1000);
  }

  // Print timer done message
  printf("\nTimer done!\n");
}
