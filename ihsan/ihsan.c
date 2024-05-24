#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../disdukcapil.h"

static int keyStr = 18; // Tidak boleh >= 26
static int keyInt = 7;  // Tidak boleh >= 10

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
    printf("| %-5s | %-20s |\n", "ID", "Nama Lengkap");
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
}


