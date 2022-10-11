typedef struct User {
    int id;
    char name[20];
    char password[20];
    char IBAN[20];
    int money;
} User;

User users[20];