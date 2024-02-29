#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int geser;
    char arah;
}Admin;

void registerAdmin();
void enkripsiPassword(char *password, int geser);
void angkaGeser(int *geser, char *arah);
void simpanAdmin(Admin admin);
