#include <stdio.h>

#define MAX_PROJECTS 3
#define MAX_NODES 100

typedef struct {
    int duration;
    int dependencies[MAX_NODES];
    int num_dependencies;
} ProjectNode;

int calculateProjectTime(ProjectNode projects[], int num_projects, int project_index) {
    int max_time = 0;
    
    if (projects[project_index].num_dependencies == 0) {
        return projects[project_index].duration;
    }
    
    for (int i = 0; i < projects[project_index].num_dependencies; i++) {
        int dependency_index = projects[project_index].dependencies[i];
        int dependency_time = calculateProjectTime(projects, num_projects, dependency_index);
        if (dependency_time > max_time) {
            max_time = dependency_time;
        }
    }
    
    return max_time + projects[project_index].duration;
}

int main() {
    int num_projects;
    scanf("%d", &num_projects);
    
    for (int p = 0; p < num_projects; p++) {
        int num_nodes;
        scanf("%d", &num_nodes);
        
        ProjectNode projects[MAX_NODES];
        
        for (int i = 0; i < num_nodes; i++) {
            scanf("%d", &projects[i].duration);
            scanf("%d", &projects[i].num_dependencies);
            for (int j = 0; j < projects[i].num_dependencies; j++) {
                scanf("%d", &projects[i].dependencies[j]);
            }
        }
        
        int total_time = 0;
        for (int i = 0; i < num_nodes; i++) {
            int project_time = calculateProjectTime(projects, num_nodes, i);
            if (project_time > total_time) {
                total_time = project_time;
            }
        }
        
        printf("%d\n", total_time);
    }
    
    return 0;
}
