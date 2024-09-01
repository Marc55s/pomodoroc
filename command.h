typedef void (*Commandfunc)(double time);

struct CommandMap{
    Commandfunc function;
    double time;
};
void executeCMD(struct CommandMap cmd);
struct CommandMap executeCMDArgs(int argc, char **args);
void start(double time);
void startbreak(double time);
void startstudy(double time);
