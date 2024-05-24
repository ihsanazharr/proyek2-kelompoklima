#include "../disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int keyint = 7;

void tambahKK(DataKota* kota) {
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

    printf("=================================================\n");

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
        // enkripsiInteger(kk->noKK, keyint);
        if (file == NULL) {
            printf("Gagal membuka dataKK.txt untuk penulisan\n");
            free(kk);
            return;
        }
        

        // Log Debugging
        printf("Debug: Menambahkan KK ke kota\n");
        printf("Debug: kota->firstChild sebelum: %p\n", (void*)kota->firstChild);

        if (kota->firstChild == NULL) {
            kota->firstChild = kk;
            printf("Debug: kota->firstChild diatur ke KK baru: %p\n", (void*)kota->firstChild);
        } else {
            DataKK* temp = kota->firstChild;
            // Log Debugging lebih lanjut
            printf("Debug: Melintasi sibling\n");
            while (temp->nextSibling != NULL) {
                printf("Debug: Sibling saat ini: %p, nextSibling: %p\n", (void*)temp, (void*)temp->nextSibling);
                temp = temp->nextSibling;
            }
            temp->nextSibling = kk;
            printf("Debug: Menambahkan KK sebagai nextSibling: %p\n", (void*)temp->nextSibling);
        }

        printf("Debug: kota->firstChild sesudah: %p\n", (void*)kota->firstChild);
        printf("Debug: kk ditambahkan: %p\n", (void*)kk);

        fprintf(file, "%d %s\n", kk->id, kk->noKK);
        fclose(file);
        printf("KK berhasil Tersimpan\n");

        // catatAktivitas("Menambahkan Kartu Keluarga", kk->noKK);
    }

    char pilihUser;
    printf("\nApakah ingin menambah data lagi? [Y/N] : ");
    scanf(" %c", &pilihUser);
    getchar(); // Untuk mengkonsumsi karakter newline yang tersisa oleh scanf
    if (pilihUser == 'Y' || pilihUser == 'y') {
        tambahKK(kota);
    }
}
