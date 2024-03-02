#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int jumlahGeser;//tambahan subvar untuk jumlah geser & arah geser
    char arahGeser;
} Admin;

void addAdmin();
void enkripsiPassword(char *password, int jumlahGeser, char arahGeser);
void generateAngkaGeser(int *jumlahgeser, char *arahgeser);
void simpanFileAdmin(Admin admin);
void loginAdmin();
void dekripsiPassword(char *passwordCompare, int jumlahGeser, char arahGeser);