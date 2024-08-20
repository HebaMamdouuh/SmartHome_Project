#ifndef HOUSE_SYSTEM_H
#define HOUSE_SYSTEM_H

#define Max_Trials       3
#define MAX_USERS        10

typedef struct {
	u8 username[10];
	u8 password[10];
} User;

User users[MAX_USERS];

void init_voidUsers(void);

u8 verify_user(u8 * SavedPass);

void houseSystem(void);

void House_init(void);

void Menu(void);

#endif
