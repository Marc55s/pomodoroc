void executeCMD(char *command);
void executeCMDArgs(char *command, char **args);
void start();
void startbreak();
void startstudy();

struct {
  char *command;
  void (*function)();
} typedef CommandMap_t;
