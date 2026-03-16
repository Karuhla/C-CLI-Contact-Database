#ifndef CONTACTS_H
#define CONTACTS_H

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
void delete_contact(Contact *contacts, int *contact_count, char *id);
void find_contact(Contact *contacts, int contact_count, char *query);
void print_help();
void clear_contacts(int *contact_count);
void save_contacts(Contact *contacts, int contact_count);
void load_contacts(Contact **contacts, int *contact_count, int *capacity);
void update_contact(Contact *contacts, int contact_count, char *id, char *field, char *value);

#endif