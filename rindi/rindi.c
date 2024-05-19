#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../disdukcapil.h"

// Fungsi untuk membaca data penduduk dari file
int bacaDataPenduduk(DataPenduduk penduduk[], int maxPenduduk, int* totalPenduduk, int* laki_laki, int* perempuan, int* islam, int* kristen, int* katolik, int* hindu, int* buddha, int* konghucu, int* kawin, int* belum_kawin, int* cerai_hidup, int* cerai_mati) {
    FILE *file = fopen("dataPenduduk.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file\n");
        return 0;
    }

    int count = 0;
    while (count < maxPenduduk && fscanf(file, "%d %s %s %s %s %c %s %s %s %s",
              &penduduk[count].id, penduduk[count].NIK, penduduk[count].noKK,
              penduduk[count].nama, penduduk[count].tanggalLahir, &penduduk[count].jk,
              penduduk[count].alamat, penduduk[count].tempat_lahir, penduduk[count].agama,
              penduduk[count].status) == 10) {
        // Menghitung jumlah penduduk berdasarkan jenis kelamin
        if (penduduk[count].jk == 'L') {
            (*laki_laki)++;
        } else if (penduduk[count].jk == 'P') {
            (*perempuan)++;
        }

        // Menghitung jumlah penduduk berdasarkan agama
        if (strcmp(penduduk[count].agama, "Islam") == 0) {
            (*islam)++;
        } else if (strcmp(penduduk[count].agama, "Kristen") == 0) {
            (*kristen)++;
        } else if (strcmp(penduduk[count].agama, "Katolik") == 0) {
            (*katolik)++;
        } else if (strcmp(penduduk[count].agama, "Hindu") == 0) {
            (*hindu)++;
        } else if (strcmp(penduduk[count].agama, "Buddha") == 0) {
            (*buddha)++;
        } else if (strcmp(penduduk[count].agama, "Konghucu") == 0) {
            (*konghucu)++;
        }

        if (strcmp(penduduk[count].status, "Kawin") == 0) {
            (*kawin)++;
        } else if (strcmp(penduduk[count].status, "Belum_Kawin") == 0) {
            (*belum_kawin)++;
        } else if (strcmp(penduduk[count].status, "Cerai_Hidup") == 0) {
            (*cerai_hidup)++;
        } else if (strcmp(penduduk[count].status, "Cerai_Mati") == 0) {
            (*cerai_mati)++;
        }

        // Menambah total jumlah penduduk
        (*totalPenduduk)++;
        
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("Error: Tidak ada data yang berhasil dibaca dari file\n");
        return 0;
    }

    return count;
}

void menu() {
    const int MAX_PENDUDUK = 1000;
    DataPenduduk penduduk[MAX_PENDUDUK];
    int jumlahPenduduk = 0;
    int pilihan;

    int total = 0;//Total Penduduk

    int laki_laki = 0;//Total Gender
    int perempuan = 0;

    int islam = 0;//Total Agama
    int kristen = 0;
    int katolik = 0;
    int hindu = 0;
    int buddha = 0;
    int konghucu = 0;

    int belum_kawin = 0;//Total Status Perkawinan
    int kawin = 0;
    int cerai_hidup = 0;
    int cerai_mati = 0;
    
    do {
        printf("Menu Utama:\n");
        printf("1. Baca Data Penduduk\n");
        printf("2. Hitung Persentase Demografis Jawa Barat\n");
        printf("3. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);
        getchar();  // Menangani newline setelah scanf

        switch (pilihan) {
            case 1:
                jumlahPenduduk = bacaDataPenduduk(penduduk, MAX_PENDUDUK, &total, &laki_laki, &perempuan, &islam, &kristen, &katolik, &hindu, &buddha, &konghucu, &kawin, &belum_kawin, &cerai_hidup, &cerai_mati);
                if (jumlahPenduduk > 0) {
                    printf("Data penduduk berhasil dibaca. Jumlah penduduk: %d\n", jumlahPenduduk);
                } else {
                    printf("Tidak ada data penduduk yang dibaca.\n");
                }
                break;
            case 2:
                if (jumlahPenduduk > 0) {
                    system("CLS");
                    printf("Laporan Data Demografis:\n");
                    printf("Total penduduk: %d\n\n", total);

                    printf("Laki-laki: %d (%.2f%%)\n", laki_laki, (100.0 * laki_laki / total));
                    printf("Perempuan: %d (%.2f%%)\n\n", perempuan, (100.0 * perempuan / total));
                    
                    printf("Laporan Data Agama di Provinsi Jawa Barat:\n");                    
                    printf("Islam: %d (%.2f%%)\n", islam, (100.0 * islam / total));
                    printf("Kristen: %d (%.2f%%)\n", kristen, (100.0 * kristen / total));
                    printf("Katolik: %d (%.2f%%)\n", katolik, (100.0 * katolik / total));
                    printf("Hindu: %d (%.2f%%)\n", hindu, (100.0 * hindu / total));
                    printf("Buddha: %d (%.2f%%)\n", buddha, (100.0 * buddha / total));
                    printf("Konghucu: %d (%.2f%%)\n\n", konghucu, (100.0 * konghucu / total));

                    printf("Laporan Data Status Perkawinan di Provinsi Jawa Barat:\n");
                    printf("Total penduduk: %d\n", total);
                    printf("Belum Kawin: %d (%.2f%%)\n", belum_kawin, (total > 0) ? (100.0 * belum_kawin / total) : 0);
                    printf("Kawin: %d (%.2f%%)\n", kawin, (total > 0) ? (100.0 * kawin / total) : 0);
                    printf("Cerai Hidup: %d (%.2f%%)\n", cerai_hidup, (total > 0) ? (100.0 * cerai_hidup / total) : 0);
                    printf("Cerai Mati: %d (%.2f%%)\n", cerai_mati, (total > 0) ? (100.0 * cerai_mati / total) : 0);
                } else {
                    printf("Data penduduk belum dibaca. Silakan baca data penduduk terlebih dahulu.\n");
                }
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (pilihan != 3);
}



