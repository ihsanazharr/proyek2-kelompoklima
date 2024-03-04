#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int jumlahGeser; // tambahan subvar untuk jumlah geser & arah geser
    char arahGeser;
} Admin;

typedef struct
{
    int id;
    char NIK[18];
    char nama[50];
    char jk;
    char alamat[50];
    char tempat_lahir[20];
    char agama[20];
    char status[20];
} DataPenduduk;

// admin
void gotoxy(int x, int y);
int pilihanMenuAwal();
void addAdmin();
void enkripsiPassword(char *password, int jumlahGeser, char arahGeser);
void generateAngkaGeser(int *jumlahgeser, char *arahgeser);
void simpanFileAdmin(Admin admin);
void loginAdmin();
void dekripsiPassword(char *passwordCompare, int jumlahGeser, char arahGeser);

// adddatapenduduk
void addPenduduk();
void enkripsiHuruf(char *kalimat, int key);
void dekripsiHuruf(char *kalimat, int key);
void enkripsiInteger(char *num, int key);
// void dekripsiInteger(char *num, int key); Belum terpakai

// deleteData
void deleteData();

// editdatapenduduk
void editPenduduk();
void displayNikList();
void displayDecryptedNikList();




