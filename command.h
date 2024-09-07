typedef void (*Commandfunc)(double time);
typedef void (*CommandCharfunc)(char *name);

struct CommandMap{
    Commandfunc function;
    CommandCharfunc charfunction;
    double time;
    char* param;
};
int executeCMD(struct CommandMap cmd);
struct CommandMap executeCMDArgs(int argc, char **args);
void start(double time);
void startbreak(double time);
void startstudy(double time);
void add(char *name);
void startproject(char *proj_name);
void listprojects();
