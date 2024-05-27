#ifndef IHSAN_H
#define IHSAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAMA_LENGTH 50

typedef struct ProvinsiTreeNode
{
    int id;
    char namaProvinsi[50];
    struct ProvinsiTreeNode *parent;
    struct KotaTreeNode *firstChild;
    struct ProvinsiTreeNode *nextSibling;
} DataProvinsi;

typedef struct KotaTreeNode
{
    int id;
    char namaKota[50];
    struct ProvinsiTreeNode *parent;
    struct KKTreeNode *firstChild;
    struct KotaTreeNode *nextSibling;
} DataKota;

typedef struct KKTreeNode
{
    int id;
    char noKK[20];
    struct KotaTreeNode *parent;
    struct FamilyTreeNode *firstChild;
    struct KKTreeNode *nextSibling;
} DataKK;

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
    char noKK[50];
    char tanggalLahir[50];
    char namaKota[50]; // Tambahkan namaKota
    struct KKTreeNode *parent;
    struct FamilyTreeNode *firstChild;
    struct FamilyTreeNode *nextSibling;
} DataPenduduk;

void showPenduduk();

void displayDecryptedNikList();

void tambahKota(DataProvinsi *provinsi);

void displayNikList();

#endif