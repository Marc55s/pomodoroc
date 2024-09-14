#include <time.h>
#include <string.h>
#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <sys/time.h>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif


#ifdef _WIN32
    void sleep_ms(int milliseconds) {
        Sleep(milliseconds);
    }
unsigned long getTickCount() {
    return GetTickCount64();
}
int kbhit_linux() {
    return kbhit();
}
#else
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000); // usleep takes microseconds
    }
unsigned long getTickCount() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
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

