#include "../disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int keyint = 7;

void tambahKK(DataKota* kota) {
    system("cls");
    if (kota == NULL) {
        printf("Error: kota is NULL\n");
        return;
    }

    DataKK* kk = (DataKK*)malloc(sizeof(DataKK));
    if (kk == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Inisialisasi semua field di DataKK
    kk->parent = kota;
    kk->firstChild = NULL;
    kk->nextSibling = NULL;
    memset(kk->noKK, 0, sizeof(kk->noKK)); // pastikan noKK terinisialisasi dengan null-terminator

    FILE *file;
    int count = 0;
    char buffer[256];
    int cek = 0;

    file = fopen("dataKK.txt", "r");
    if (file != NULL) {
        while (fgets(buffer, sizeof(buffer), file)) {
            count++;
        }
        fclose(file);
    }

    kk->id = count;

    fflush(stdin);
    printf("Masukan No KK : ");
    fgets(kk->noKK, sizeof(kk->noKK), stdin);
    kk->noKK[strcspn(kk->noKK, "\n")] = '\0';

    for (int i = 0; kk->noKK[i]; i++) {
        if (kk->noKK[i] == ' ') {
            kk->noKK[i] = '_';
        }
    }

    // Cek duplikasi No KK
    file = fopen("dataKK.txt", "r");
    if (file != NULL) {
        while (fgets(buffer, sizeof(buffer), file)) {
            char fileNoKK[16];
            sscanf(buffer, "%*d %s", fileNoKK);
            if (strcmp(fileNoKK, kk->noKK) == 0) {
                cek = 1;
                break;
            }
        }
        fclose(file);
    }

    printf("========================================\n");
    if (cek == 1) {
        printf("No KK Duplikat\n");
        free(kk);
        return;
    } else {
        file = fopen("dataKK.txt", "a");
        enkripsiInteger(kk->noKK, keyint);
        if (file == NULL) {
            printf("Gagal membuka dataKK.txt untuk penulisan\n");
            free(kk);
            return;
        }

        if (fprintf(file, "%d %s\n", kk->id, kk->noKK) < 0) {
            printf("Gagal menulis ke file\n");
            fclose(file); // Tutup file sebelum keluar dari fungsi
            free(kk);
            return;
        }

        fclose(file); // Tutup file setelah selesai menulis
        catatAktivitas("Menambahkan data kk", kk->noKK); // Pindahkan ini ke sini
        printf("KK berhasil Tersimpan\n"); // Pesan pemberitahuan
    }

    char pilihUser;
    printf("\nApakah ingin menambah data lagi? [Y/N] : ");
    scanf(" %c", &pilihUser);
    getchar(); // Untuk mengkonsumsi karakter newline yang tersisa oleh scanf
    if (pilihUser == 'Y' || pilihUser == 'y') {
        tambahKK(kota);
    }
}
