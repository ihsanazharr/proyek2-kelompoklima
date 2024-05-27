#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../disdukcapil.h"
#define MAX_LINE_LENGTH 1000

static int keyStr = 18; // Tidak boleh >= 26
static int keyInt = 7;  // Tidak boleh >= 10


void showPenduduk() {
    system("cls"); // Clear screen

    FILE *file;
    DataPenduduk data;
    DataPenduduk penduduk[100]; // Assuming a maximum of 100 records

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }

    int count = 0;
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF) {
        dekripsiHuruf(data.alamat, keyStr);
        dekripsiInteger(data.NIK, keyInt);
        dekripsiInteger(data.noKK, 4);
        penduduk[count++] = data;
    }

    fclose(file);

    if (count == 0) {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }

    // Sorting
    bubbleSort(penduduk, count);

    printf("=============================================================================================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status", "No. KK", "Tanggal Lahir");
    printf("=============================================================================================================================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", penduduk[i].id, penduduk[i].NIK, penduduk[i].nama, penduduk[i].jk, penduduk[i].alamat, penduduk[i].tempat_lahir, penduduk[i].agama, penduduk[i].status, penduduk[i].noKK, penduduk[i].tanggalLahir);
    }

    printf("=============================================================================================================================================================================================\n");

    // Meminta pengguna untuk mencari data berdasarkan nama atau No. KK atau kembali ke menu
    char userChoice;
    printf("\nApakah Anda ingin mencari data berdasarkan nama? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        searchByName(penduduk, count);
    } else {
        printf("Apakah Anda ingin mencari data berdasarkan No. KK? [Y/N]: ");
        scanf(" %c", &userChoice);
        if (userChoice == 'Y' || userChoice == 'y') {
            searchByNoKK(penduduk, count);
        } else {
            printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
            scanf(" %c", &userChoice);
            if (userChoice == 'Y' || userChoice == 'y') {
                menuAwal();
            } else {
                showPenduduk();
            }
        }
    }
}

void searchByNoKK(DataPenduduk penduduk[], int count) {
    char noKK[16];
    printf("Masukkan No. KK yang ingin dicari: ");
    scanf("%s", noKK);

    printf("=============================================================================================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status", "No. KK", "Tanggal Lahir");
    printf("=============================================================================================================================================================================================\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(penduduk[i].noKK, noKK) == 0) {
            printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", penduduk[i].id, penduduk[i].NIK, penduduk[i].nama, penduduk[i].jk, penduduk[i].alamat, penduduk[i].tempat_lahir, penduduk[i].agama, penduduk[i].status, penduduk[i].noKK, penduduk[i].tanggalLahir);
            found = 1;
        }
    }

    if (!found) {
        printf("Data dengan No. KK \"%s\" tidak ditemukan.\n", noKK);
    }

    // Meminta pengguna untuk kembali ke menu atau ke pencarian No. KK
    char userChoice;
    printf("\nApakah Anda ingin mencari data lagi? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        searchByNoKK(penduduk, count);
    } else {
        printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
        scanf(" %c", &userChoice);
        if (userChoice == 'Y' || userChoice == 'y') {
            menuAwal();
        } else {
            showPenduduk();
        }
    }
}

void searchByName(DataPenduduk penduduk[], int count)
{
    char searchName[50];
    printf("Masukkan nama (huruf yang diinginkan): ");
    scanf("%s", searchName);

    printf("=============================================================================================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status", "No. KK", "Tanggal Lahir");
    printf("=============================================================================================================================================================================================\n");

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        char result[100];                                        // Menyimpan hasil pencarian nama
        strcasestr_custom(penduduk[i].nama, searchName, result); // Pencarian tanpa case sensitive
        if (result[0] != '\0')
        {
            printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", penduduk[i].id, penduduk[i].NIK, penduduk[i].nama, penduduk[i].jk, penduduk[i].alamat, penduduk[i].tempat_lahir, penduduk[i].agama, penduduk[i].status, penduduk[i].noKK, penduduk[i].tanggalLahir);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Data dengan nama yang mengandung \"%s\" tidak ditemukan.\n", searchName);
    }

    // Meminta pengguna untuk kembali ke menu atau ke pencarian nama
    char userChoice;
    printf("\nApakah Anda ingin mencari data lagi? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        searchByName(penduduk, count);
    } else {
        printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
        scanf(" %c", &userChoice);
        if (userChoice == 'Y' || userChoice == 'y') {
            menuAwal();
        } else {
            showPenduduk();
        }
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


