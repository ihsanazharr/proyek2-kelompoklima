#ifndef DISDUKCAPIL_H
#define DISDUKCAPIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ihsan/ihsan.h"
#include "maul/maul.h"

#define MAX_NAMA_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct Admin
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int jumlahGeser; // tambahan subvar untuk jumlah geser
} Admin;

typedef struct AktivitasPengguna
{
    char username[MAX_USERNAME_LENGTH];
    bool loggedIn;
} AktivitasPengguna;

// Admin functions
void gotoxy(int x, int y);
int pilihanMenuAwal();
void menuAwal();
void addAdmin();
int checkUsernameExists(const char* username);
void enkripsiPassword(char *password, int jumlahGeser);
void generateAngkaGeser(int *jumlahgeser);
void simpanFileAdmin(Admin admin);
void loginAdmin();
void dekripsiPassword(char *passwordCompare, int jumlahGeser);
void tampilkanTree();

// Add penduduk functions
void addPenduduk(DataKota *kota);
void enkripsiHuruf(char *kalimat, int key);
void dekripsiHuruf(char *kalimat, int key);
void enkripsiInteger(char *num, int key);
void dekripsiInteger(char *num, int key);
void removeNewline(char *str);


// Delete data function
void deleteData();

// Edit penduduk functions
void editPenduduk();


// History functions
void catatAktivitas(char *aksi, char *NIK);
void catatLogin();
void catatEdit();
void showKota();
void logKejadianPenting(char *noKK1, char *noKK2, char *NIK1, char *NIK2, char *kejadianPenting);

// Important events functions
void kejadianPenting();
void displayDecryptedNoKKList();
bool searchKK(char noKK[20]);
bool searchNIK(char NIK[50], char KK[20]);
char getGenderFromNIK(char NIK[50]);
void tampilkanIsiKK(DataPenduduk data, char userInput[20]);
void tampilkanIsiNIK(DataPenduduk data, char userInput[50]);
void changeKK(DataPenduduk data, char *NIKSource, char *KKDestination, char *newCity);
void changeStatus(DataPenduduk data, char *NIK);
void Pernikahan();
void Kematian();
void Kelahiran();

#endif // DISDUKCAPIL_H
