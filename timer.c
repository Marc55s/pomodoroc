#include "timer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <sys/time.h>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

char* getCurrentTime() {
    time_t now = time(0);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove the newline character
    return time_str;
}

#ifdef _WIN32
    void sleep_ms(int milliseconds) {
        Sleep(milliseconds);
    }
#else
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif

#ifdef _WIN32
    unsigned long getTickCount() {
        return GetTickCount64();
    }
#else
    unsigned long getTickCount() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return (time.tv_sec * 1000) + (time.tv_usec / 1000);
    }
#endif

#ifdef _WIN32
    int kbhit_linux() {
        return kbhit();
    }
#else
    int kbhit_linux() {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if(ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }
#endif

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
    clock_t start, end;
    double elapsed;
    int minutes = 0, seconds = 0;
    int pause = 0;

    start = clock();

    while (1) {
        if (kbhit_linux()) {
            if (getchar() == ' ') {
                pause = !pause;
            }
        }

        if (!pause) {
            elapsed = ((double)(clock() - start)) / CLOCKS_PER_SEC;
            minutes = (int)elapsed / 60;
            seconds = (int)elapsed % 60;

            printf("\rElapsed time: %02d:%02d", minutes, seconds);
            fflush(stdout);
        }

        sleep_ms(3);
    }

    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC / 60.0;
    printf("\nElapsed time: %.3f seconds\n", elapsed);
}

