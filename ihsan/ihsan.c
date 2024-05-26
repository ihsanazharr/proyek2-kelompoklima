#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../disdukcapil.h"
#define MAX_LINE_LENGTH 1000

static int keyStr = 18; // Tidak boleh >= 26
static int keyInt = 7;  // Tidak boleh >= 10

DataKK* searchKartuKeluargaByNoKK(DataProvinsi *root, const char *noKK) {
    if (root == NULL) {
        return NULL;
    }

    DataKota *kotaNode = root->firstChild;
    while (kotaNode != NULL) {
        DataKK *kkNode = kotaNode->firstChild;
        while (kkNode != NULL) {
            if (strcmp(kkNode->noKK, noKK) == 0) {
                return kkNode;
            }
            kkNode = kkNode->nextSibling;
        }
        kotaNode = kotaNode->nextSibling;
    }
    return NULL;
}

// Fungsi untuk menampilkan data penduduk dari node KK
void tampilkanDataPendudukDariKK(DataKK *kkNode) {
    if (kkNode == NULL) {
        printf("Kartu Keluarga tidak ditemukan.\n");
        return;
    }

    DataPenduduk *pendudukNode = kkNode->firstChild;
    while (pendudukNode != NULL) {
        printf("NIK: %s\n", pendudukNode->NIK);
        printf("Nama: %s\n", pendudukNode->nama);
        printf("Jenis Kelamin: %c\n", pendudukNode->jk);
        printf("Alamat: %s\n", pendudukNode->alamat);
        printf("Tempat Lahir: %s\n", pendudukNode->tempat_lahir);
        printf("Agama: %s\n", pendudukNode->agama);
        printf("Status: %s\n", pendudukNode->status);
        printf("No KK: %s\n", pendudukNode->noKK);
        printf("Tanggal Lahir: %s\n", pendudukNode->tanggalLahir);
        printf("Nama Kota: %s\n", pendudukNode->namaKota);
        printf("-----------------------------\n");

        pendudukNode = pendudukNode->nextSibling;
    }
}

void menuCariKartuKeluarga(DataProvinsi *root) {
    system("cls");
    char noKK[20];
    FILE *file, *temp;
    DataPenduduk data;
    char userChoose;
    bool found = false;
    int n = 0;

    file = fopen("dataKK.txt", "r");
    temp = fopen("tempDataKK.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    displayDecryptedNoKK();

    printf("Masukkan no KK: ");
    scanf("%s", noKK);

    DataKK *kkNode = searchKartuKeluargaByNoKK(root, noKK);
    tampilkanDataPendudukDariKK(kkNode);

    char userChoice;
    printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        menuAwal();
    } else {
        menuCariKartuKeluarga(root);
    }
}

void tambahKota(DataProvinsi* provinsi) {
    DataKota* kota = (DataKota*)malloc(sizeof(DataKota));
    kota->parent = provinsi;
    kota->firstChild = NULL;
    kota->nextSibling = NULL;

    FILE *file;
    int count = 0, a;
    int cek = 0;

    file = fopen("dataKota.txt", "r");
    if (file != NULL) {
        for (a = getc(file); a != EOF; a = getc(file)) {
            if (a == '\n') {
                count = count + 1;
            }
        }
        fclose(file);
    }
    
    kota->id = count;
    
    fflush(stdin);
    printf("Masukkan Nama Kota: ");
    fgets(kota->namaKota, sizeof(kota->namaKota), stdin);
    kota->namaKota[strcspn(kota->namaKota, "\n")] = '\0';
    for (int i = 0; kota->namaKota[i]; i++) {
        if (kota->namaKota[i] == ' ') {
            kota->namaKota[i] = '_';
        }
    }
    
    printf("=================================================\n");

    if (cek == 1) {
        printf("Data Duplikat\n");
        free(kota); // Jangan lupa bebaskan memori yang dialokasikan
        return;
    } else {
        file = fopen("dataKota.txt", "a");
        enkripsiHuruf(kota->namaKota, keyStr);
        
        // Tambahkan kota sebagai anak pertama atau sebagai saudara dari anak yang sudah ada
        if (provinsi->firstChild == NULL) {
            provinsi->firstChild = kota;
        } else {
            DataKota* temp = provinsi->firstChild;
            while (temp->nextSibling != NULL) {
                temp = temp->nextSibling;
            }
            temp->nextSibling = kota;
        }

        fprintf(file, "%d %s\n", kota->id, kota->namaKota);
        fclose(file);
        printf("Data berhasil tersimpan\n");

        // Catat aktivitas pengguna
        catatAktivitas("Menambahkan data kota", kota->namaKota);
    }

    // Pilihan untuk menambah data lagi
    char pilihanUser;
    printf("\nApakah Anda ingin menambah data lagi? (Y/N): ");
    scanf(" %c", &pilihanUser);
    if (pilihanUser == 'Y' || pilihanUser == 'y') {
        tambahKota(provinsi); // Rekursif untuk menambah data lagi jika dipilih
    }
}

void displayDecryptedNoKK()
{
    FILE *file = fopen("dataKK.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    DataKK data;
    char line[MAX_LINE_LENGTH];
    printf("=================================================\n");
    printf("\tDaftar Nomor Kartu Kekuarga (Terdekripsi)\n");
    printf("=================================================\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Menggunakan sscanf untuk membaca data dari satu baris
        sscanf(line, "%d %s ", &data.id, data.noKK);
        char decryptedNoKK[18];
        strcpy(decryptedNoKK, data.noKK);
        dekripsiInteger(decryptedNoKK, keyInt);
        printf("%s (Normal: %s)\n", decryptedNoKK, data.noKK);
    }
    printf("=================================================\n");

    fclose(file);
}

void showKota() {
    // system("cls"); // Clear screen

    FILE *file;
    DataKota data;
    DataKota kota[100]; // Assuming a maximum of 100 records

    file = fopen("dataKota.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }

    int count = 0;
    while (fscanf(file, "%d %s", &data.id, data.namaKota) != EOF) {
        dekripsiHuruf(data.namaKota, keyStr);
        kota[count++] = data;
    }

    fclose(file);

    if (count == 0) {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }
    // Sorting
    bubbleSort(kota, count);

    printf("==============================================================================================\n");
    printf("| %-5s | %-20s |\n", "ID", "Nama Kota");
    printf("==============================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("| %-5d | %-20s |\n", kota[i].id, kota[i].namaKota);
    }

    printf("=============================================================================================================================================================================================\n");

    // Meminta pengguna untuk mencari data berdasarkan nama atau kembali ke menu
    // char userChoice;
    // printf("\nApakah Anda ingin mencari data berdasarkan nama? [Y/N]: ");
    // scanf(" %c", &userChoice);
    // if (userChoice == 'Y' || userChoice == 'y') {
    //     searchByName(kota, count);
    // } else {
    //     printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    //     scanf(" %c", &userChoice);
    //     if (userChoice == 'Y' || userChoice == 'y') {
    //         menuAwal();
    //     } else {
    //         printf("Terima kasih.\n");
    //     }
    // }
    getchar();
    getchar();
}


