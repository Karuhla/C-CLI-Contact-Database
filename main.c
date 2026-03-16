#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contacts.h"

#define INPUT_SIZE 256

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
            char *first_name = strtok(NULL, " ");
            char *last_name = strtok(NULL, " ");
            char *phone = strtok(NULL, " ");

            if (id == NULL || first_name == NULL || last_name == NULL || phone == NULL){
                printf("Usage: insert <id> <first_name> <last_name> <phone>\n");
                continue;
            }

            insert_contact(&contacts, &contact_count, &capacity,
                            id, first_name, last_name, phone);

        }else if (strcmp(command, "select") == 0){          

            select_contacts(contacts, contact_count);

        }else if (strcmp(command, "delete") == 0){

            char *id = strtok(NULL, " ");

            if (id == NULL){
                printf("Usage: delete <id>\n");
                continue;
            }

            delete_contact(contacts, &contact_count, id);
            
        }else if (strcmp(command, "find") == 0){

            
            char *query = strtok(NULL, " ");

            if (query == NULL){
                printf("Usage: find <id|name>\n");
                continue;
            }

            find_contact(contacts, contact_count, query);

        }
        else if (strcmp(command, "help") == 0){
            
            print_help();

        }else if (strcmp(command, "clear") == 0){

            clear_contacts(&contact_count);

        }else if (strcmp(command, "save") == 0){

            save_contacts(contacts, contact_count);

        }else if (strcmp(command, "load") == 0){

            load_contacts(&contacts, &contact_count, &capacity);

        }
        else if (strcmp(command, "update") == 0){

            char *id = strtok(NULL, " ");
            char *field = strtok(NULL, " ");
            char *value = strtok(NULL, " ");

            if (id == NULL || field == NULL || value == NULL){
                printf("Usage: update <id> <field> <value>\n");
                continue;
            }

            update_contact(contacts, contact_count, id, field, value);

        }
        else{
            printf("Unknown command\n");
        }       
    }

    free(contacts);

    return 0;

}