#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORKSPACES 40
#define MAX_ID_LENGTH 40
#define MAX_BUFFER_SIZE 1024

int calculate_number_of_workspaces(){
    char workspaces[MAX_WORKSPACES][MAX_ID_LENGTH];
    int workspace_ids[MAX_WORKSPACES];
    FILE *fp;
    char command[] = "hyprctl workspaces -j | jq '.[].id'";
    char buffer[MAX_ID_LENGTH];
    int num_workspaces = 0;
    int sauv;

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Erreur lors de l'exécution de la commande.\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL && num_workspaces < MAX_WORKSPACES) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(workspaces[num_workspaces], buffer, MAX_ID_LENGTH - 1); 
        workspaces[num_workspaces][MAX_ID_LENGTH - 1] = '\0'; 
        
        
        workspace_ids[num_workspaces] = atoi(buffer);
        
        num_workspaces++;
    }

    pclose(fp);

    for (int i = 0; i < num_workspaces-1; i++) {
        if (workspace_ids[i] >= workspace_ids[i+1]){
            sauv = workspace_ids[i];
            workspace_ids[i] = workspace_ids[i+1];
            workspace_ids[i+1] = sauv;
        }
    }
    for (int i = 0; i < num_workspaces; i++) {printf("workspace: %d\n", workspace_ids[i]);}
    printf("le workspace le plus grand est: %d\n",workspace_ids[num_workspaces-1]);
    return workspace_ids[num_workspaces-1];
}


int main() {
    char buffer[MAX_BUFFER_SIZE];
    int result;
    int number_of_workspaces = calculate_number_of_workspaces();
    printf("le workspace le plus grand est: %d\n" , number_of_workspaces);
    FILE *pipe = popen("hyprctl activeworkspace | grep -o '[0-9]' | head -n 1 | tail -1", "r");
    if (!pipe) {
        fprintf(stderr, "Erreur lors de l'exécution de la commande.\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result = atoi(buffer);
        pclose(pipe);

        if (result >= number_of_workspaces) {
            system("hyprctl dispatch workspace 1");
        } else {
            result += 1;
            char command[100];
            sprintf(command, "hyprctl dispatch workspace %d", result);
            system(command);
        }

        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Le workspace actuel n'existe pas 😳?\n");
        pclose(pipe);
        return EXIT_FAILURE;
    }
}
