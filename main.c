#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256
#define DATABASE_FILE "contacts.db"

typedef struct {
    int id;
    char first_name [50];
    char last_name [50];
    char phone [100];
} Contact;

void insert_contact(Contact **contacts, int *contact_count, int *capacity,
                    char *id, char *first_name, char *last_name, char *phone);
void select_contacts(Contact *contacts, int contact_count);

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

            int id_num = atoi(id);

            for (int i = 0; i < contact_count ; i++){
                if (contacts[i].id == id_num){
                    for(int j = i; j < contact_count - 1; j++){
                        contacts[j] = contacts[j + 1];
                    }
                    printf("Contact deleted\n");
                    contact_count--;
                    break;
                }
            }

        }else if (strcmp(command, "find") == 0){

            char *query = strtok(NULL, " ");

            if (query == NULL) {
                printf("Usage: find <id|name>\n");
                continue;
            }

            int id_num = atoi(query);
            int found = 0;

            printf("ID    Name            Surname         Phone\n");
            printf("-----------------------------------------------\n");

            for(int i = 0; i < contact_count; i++){
                if(
                    contacts[i].id == id_num ||
                    strcmp(query, contacts[i].first_name) == 0 || 
                    strcmp(query, contacts[i].last_name) == 0 
                ){
                    printf("%-5d %-15s %-15s %-30s\n", 
                        contacts[i].id, contacts[i].first_name, contacts[i].last_name, contacts[i].phone);
                    found = 1;
                }
            }

            if(!found){
                printf("Contact not found\n");
            }

        }
        else if (strcmp(command, "help") == 0){
            
            printf("Available commands:\ninsert <id> <first_name> <last_name> <phone>\nselect\ndelete <id>\nfind <id|name>\nclear\nhelp\nexit\n");

        }else if (strcmp(command, "clear") == 0){

            contact_count = 0;
            printf("All contacts cleared\n");

        }else if (strcmp(command, "save") == 0){

            FILE *file = fopen(DATABASE_FILE, "w");

            if (file == NULL){
                printf("Error opening file\n");
                continue;
            }

            for (int i = 0; i < contact_count; i++){
                fprintf(file, "%d %s %s %s\n",
                    contacts[i].id,
                    contacts[i].first_name,
                    contacts[i].last_name,
                    contacts[i].phone);
            }

            fclose(file);

            printf("Database saved successfully.\n");

        }else if (strcmp(command, "load") == 0){

            FILE *file = fopen(DATABASE_FILE, "r");

            if (file == NULL){
                printf("No database file found.\n");
                continue;
            }

            contact_count = 0;

            Contact temp;

            while (fscanf(file, "%d %s %s %s",
                &temp.id,
                temp.first_name,
                temp.last_name,
                temp.phone) == 4){

            if (capacity == 0){
                contacts = malloc(sizeof(Contact) * 4);
                capacity = 4;
            }

            if (contact_count >= capacity){
                capacity = capacity * 2;

                Contact *temp_ptr = realloc(contacts, sizeof(Contact) * capacity);

                if (temp_ptr == NULL){
                    printf("Memory allocation failed\n");
                    free(contacts);
                    exit(1);
                }

                contacts = temp_ptr;
            }

            contacts[contact_count] = temp;
            contact_count++;
        }

            fclose(file);
            printf("Database loaded successfully.\n");

        }
        else if (strcmp(command, "update") == 0){

            char *id = strtok(NULL, " ");
            char *field = strtok(NULL, " ");
            char *value = strtok(NULL, " ");

            if (id == NULL || field == NULL || value == NULL){
                printf("Usage: update <id> <field> <value>\n");
                continue;
            }

            int id_num = atoi(id);
            int updated = 0;

            for (int i = 0; i < contact_count; i++) {

                if (contacts[i].id == id_num) {

                    if (strcmp(field, "first_name") == 0) {
                        strcpy(contacts[i].first_name, value);
                    }
                    else if (strcmp(field, "last_name") == 0) {
                        strcpy(contacts[i].last_name, value);
                    }
                    else if (strcmp(field, "phone") == 0) {
                        strcpy(contacts[i].phone, value);
                    }
                    else {
                        printf("Invalid field.\n");
                        break;
                    }

                    printf("Contact updated.\n");
                    updated = 1;
                    break;
                }
            }

            if(!updated){
                printf("Invalid field.\n");
            }

        }
        else{
            printf("Unknown command\n");
        }       
    }

    free(contacts);

    return 0;

}

void insert_contact(Contact **contacts, int *contact_count, int *capacity,
                    char *id, char *first_name, char *last_name, char *phone){

    int id_num = atoi(id);

    Contact new_contact;

    for (int i = 0; i < *contact_count; i++){
        if ((*contacts)[i].id == id_num){
            printf("Error: Contact with ID %d already exists.\n", id_num);
            return;
        }
    }

    if (*capacity == 0){
        *contacts = malloc(sizeof(Contact) * 4);
        *capacity = 4;
    }

    if (*contact_count >= *capacity){
        *capacity = *capacity * 2;

        Contact *temp = realloc(*contacts, sizeof(Contact) * (*capacity));

        if (temp == NULL){
            printf("Memory allocation failed\n");
            free(*contacts);
            exit(1);
        }

        *contacts = temp;
    }

    new_contact.id = id_num;
    strcpy(new_contact.first_name, first_name);
    strcpy(new_contact.last_name, last_name);
    strcpy(new_contact.phone, phone);

    (*contacts)[*contact_count] = new_contact;
    (*contact_count)++;

    printf("Contact inserted successfully.\n");
}

void select_contacts(Contact *contacts, int contact_count){

    if (contact_count == 0){
        printf("No contacts found.\n");
        return;
    }

    printf("ID    Name            Surname         Phone\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < contact_count; i++){
        printf("%-5d %-15s %-15s %-30s\n",
            contacts[i].id,
            contacts[i].first_name,
            contacts[i].last_name,
            contacts[i].phone);
    }
}