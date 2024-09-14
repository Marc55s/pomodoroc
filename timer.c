#include "timer.h"
#include "platformtime.h"


char* getCurrentTime() {
    time_t now = time(0);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove the newline character
    return time_str;
}
void startTimer(double minutes) {
    // Convert minutes to milliseconds
    unsigned long total_milliseconds = minutes * 60 * 1000;
    unsigned long start_time = getTickCount();

    while (total_milliseconds > 0) {
        unsigned long current_time = getTickCount();
        unsigned long elapsed_time = current_time - start_time;
        start_time = current_time;

        total_milliseconds = (total_milliseconds > elapsed_time)
            ? total_milliseconds - elapsed_time
            : 0;

        unsigned long mins_left = total_milliseconds / (60 * 1000);
        unsigned long secs_left = (total_milliseconds % (60 * 1000)) / 1000;

        printf("\rTime remaining: %02lu:%02lu", mins_left, secs_left);
        fflush(stdout);

        if (total_milliseconds > 100) {
            sleep_ms(100);
        } else {
            sleep_ms(total_milliseconds);
        }
    }
}
void startstopwatch(double *elapsed_time) {
    struct timeval start, end, pause_start;
    double total_elapsed = 0.0;
    double current_elapsed = 0.0;
    double paused_time = 0.0;
    int minutes = 0, seconds = 0;
    int pause = 0;
    int ch;

    gettimeofday(&start, NULL);

    while (1) {
        if (kbhit_linux()) {
            ch = getchar();
            if (ch == ' ') {
                if (pause) {
                    // Resuming from pause
                    gettimeofday(&pause_start, NULL);
                    paused_time += (pause_start.tv_sec - start.tv_sec) + (pause_start.tv_usec - start.tv_usec) / 1000000.0;
                    start = pause_start; // Reset start time to the resume time
                    pause = 0;
                } else {
                    // Pausing
                    gettimeofday(&pause_start, NULL);
                    total_elapsed += (pause_start.tv_sec - start.tv_sec) + (pause_start.tv_usec - start.tv_usec) / 1000000.0;
                    pause = 1;
                }
            } else if (ch == 's') {
                break;
            }
        }

        if (!pause) {
            gettimeofday(&end, NULL);
            current_elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            minutes = (int)(total_elapsed + current_elapsed) / 60;
            seconds = (int)(total_elapsed + current_elapsed) % 60;

            printf("\rElapsed time: %02d:%02d", minutes, seconds);
            fflush(stdout);
        }

        sleep_ms(100);  // Sleep for 100 milliseconds for smoother output
    }

    // Add the final elapsed time to account for any remaining time
    if (!pause) {
        gettimeofday(&end, NULL);
        total_elapsed += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    }

    *elapsed_time = total_elapsed / 60;

    printf("\nTotal elapsed time: %.3f seconds\n", total_elapsed);
}

