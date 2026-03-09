#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256

typedef struct {
    int id;
    char name [50];
    char email [100];
} Contact;

int main(){

    char input[INPUT_SIZE];
    Contact *contacts = NULL;
    int contact_count = 0;
    int capacity = 0;

    while (1){

        printf("db > ");
        fgets(input, INPUT_SIZE, stdin);

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n'){
            input[len - 1] = '\0';
        }

        char *command = strtok(input, " ");

        if (command == NULL){
            continue;
        }

        if (strcmp(command, "exit") == 0){
            printf("Goodbye!\n");
            break;
        }

        if (strcmp(command, "insert") == 0){

            Contact new_contact;

            char *id = strtok(NULL, " ");
            char *name = strtok(NULL, " ");
            char *email = strtok(NULL, " ");

            if (id == NULL || name == NULL || email == NULL){
                printf("Usage: insert <id> <name> <email>\n");
                continue;
            }

            int id_num = atoi(id);

            if (capacity == 0){
                contacts = malloc(sizeof(Contact) * 4);
                capacity = 4;
            }

            if (contact_count >= capacity) {
                capacity = capacity * 2;

                Contact *temp = realloc(contacts, sizeof(Contact) * capacity);

                if (temp == NULL) {
                    printf("Memory allocation failed\n");
                    free(contacts);
                    exit(1);
                }

                contacts = temp;
            }

            new_contact.id = id_num;
            strcpy(new_contact.name, name);
            strcpy(new_contact.email, email);

            contacts[contact_count] = new_contact;
            contact_count++;

            printf("ID: %d\n", new_contact.id);
            printf("Name: %s\n", new_contact.name);
            printf("Email: %s\n", new_contact.email);

        }else if (strcmp(command, "select") == 0){            
            
            printf("ID    Name            Email\n");
            printf("-------------------------------\n");
            for (int i = 0; i < contact_count; i++){
                printf("%-5d %-15s %-30s\n", contacts[i].id, contacts[i].name, contacts[i].email);
            }

        }else if (strcmp(command, "delete") == 0){
            printf("Delete Command detected\n");
        }else if (strcmp(command, "help") == 0){
            printf("Help Command detected\n");
        }else{
            printf("Unknown command\n");
        }       
    }

    free(contacts);

    return 0;

}