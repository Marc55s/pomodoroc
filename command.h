typedef void (*Commandfunc)(double time);
typedef void (*CommandBifunc)(char *name, double time);

struct CommandMap{
    Commandfunc function;
    CommandBifunc bifunction;
    double time;
    char* param;
};
int executeCMD(struct CommandMap cmd);
struct CommandMap executeCMDArgs(int argc, char **args);
void start(double time);
void startbreak(double time);
void startstudy(double time);
void add(char *name, double time);
void startproject();
