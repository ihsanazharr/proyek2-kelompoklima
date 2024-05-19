#ifndef DISDUKCAPIL_H
#define DISDUKCAPIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NAMA_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int jumlahGeser; // tambahan subvar untuk jumlah geser
} Admin;

typedef struct ProvinsiTreeNode
{
    int id;
    char namaProvinsi[50];
    struct ProvinsiTreeNode *parent;
    struct kotaTreeNode *firstChild;
    struct ProvinsiTreeNode *nextSibling;
} DataProvinsi;

typedef struct KotaTreeNode
{
    int id;
    char namaKota[50];
    struct ProvinsiTreeNode *parent;
    struct kotaTreeNode *firstChild;
    struct FamilyTreeNode *nextSibling;
} DataKota;

typedef struct FamilyTreeNode
{
    int id;
    char NIK[50];
    char nama[MAX_NAMA_LENGTH];
    char jk;
    char alamat[90];
    char tempat_lahir[50];
    char agama[20];
    char status[20];
    char noKK[50]; // Tambah no KK
    char tanggalLahir[50];
    struct KotaTreeNode *parent;
    struct FamilyTreeNode *firstChild;
    struct FamilyTreeNode *nextSibling;
} DataPenduduk;

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    bool loggedIn;
} AktivitasPengguna;

// admin
void gotoxy(int x, int y);
int pilihanMenuAwal();
void menuAwal();
void addAdmin();
void enkripsiPassword(char *password, int jumlahGeser);
void generateAngkaGeser(int *jumlahgeser);
void simpanFileAdmin(Admin admin);
void loginAdmin();
void dekripsiPassword(char *passwordCompare, int jumlahGeser);
void tampilkanTree();

// adddatapenduduk
void addPenduduk(DataKota *kota);
void enkripsiHuruf(char *kalimat, int key);
void dekripsiHuruf(char *kalimat, int key);
void enkripsiInteger(char *num, int key);
void dekripsiInteger(char *num, int key);

// Add Kota
void tambahKota(DataProvinsi *provinsi);

// deleteData
void deleteData();

// editdatapenduduk
void editPenduduk();
void displayNikList();
void displayDecryptedNikList();

// history
void catatAktivitas(char *aksi, char *NIK);
void catatLogin();
void catatEdit();

// Kejadian Penting
void kejadianPenting();
void displayDecryptedNoKKList();
bool searchKK(char noKK[20]);
bool searchNIK(char NIK[50], char KK[20]);
char getGenderFromNIK(char NIK[50]);
void tampilkanIsiKK(DataPenduduk data, char userInput[20]);
void tampilkanIsiNIK(DataPenduduk data, char userInput[50]);
void changeKK(DataPenduduk data, char *NIKSource, char *KKDestination);
void changeStatus(DataPenduduk data, char *NIK);
void Pernikahan();
void Kematian();
void Kelahiran();

#endif
