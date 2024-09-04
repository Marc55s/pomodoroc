#define PROJECT_NAME_SIZE 64

struct project {
    char name[PROJECT_NAME_SIZE];
    double time;
};
int save_project(struct project proj);
int load_projects();
void list_projects();
