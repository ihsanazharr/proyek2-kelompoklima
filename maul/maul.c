#include "../disdukcapil.h"
#include "../ihsan/ihsan.h"
#include "maul.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int keystr = 18;
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

    while (1) {
        fflush(stdin);
        printf("Masukkan No KK (16 digit): ");
        fgets(kk->noKK, sizeof(kk->noKK), stdin);
        kk->noKK[strcspn(kk->noKK, "\n")] = '\0';

        if (strlen(kk->noKK) != 16) {
            printf("Nomor KK harus terdiri dari 16 digit. Silakan coba lagi.\n");
            continue;
        }

        bool valid = true;
        for (int i = 0; i < 16; i++) {
            if (kk->noKK[i] < '0' || kk->noKK[i] > '9') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            printf("Nomor KK harus terdiri dari angka. Silakan coba lagi.\n");
            continue;
        }

        break;
    }

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
        if (file == NULL) {
            printf("Gagal membuka dataKK.txt untuk penulisan\n");
            free(kk);
            return;
        }

        enkripsiInteger(kk->noKK, keyint);
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

void hapusKK()
{
    system("cls");
    FILE *file, *temp;
    DataKK kk;
    char userInput[20];
    char userInputCpy[20];
    char userChoose;
    bool found = false;
    int n = 0;

    file = fopen("dataKK.txt", "r");
    temp = fopen("tempKK.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    printf("Masukkan no kk yang ingin dihapus: ");
    scanf("%s", userInput);
    strcpy(userInputCpy, userInput);
    enkripsiInteger(userInput, keyint);

    int i = 0;
    rewind(file);
    while (fscanf(file, "%d %s", &kk.id, kk.noKK) != EOF)
    {

        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(userInput, kk.noKK) != 0)
        {
            if (found == false)
            {
                i++;
            }
        }
        else
        {
            found = true;
        }
    }

    if (found)
    {
        printf("Data dengan noKK %s ditemukan.\n", userInputCpy);
        printf("Apakah Anda yakin ingin menghapus kk ini? [Y/N]: ");
        scanf(" %c", &userChoose);
        if (userChoose == 'Y' || userChoose == 'y')
        {
            printf("Data dengan noKK %s telah dihapus.\n", userInputCpy);
            Sleep(2000);
            rewind(file);
            char line[1000];
            int n = 0;
            while (fgets(line, sizeof(line), file) != NULL)
            {
                if (n == i)
                {
                    n++;
                    continue;
                }
                fputs(line, temp);
                n++;
            }
            catatAktivitas("Menghapus kk penduduk", userInputCpy);
        }
        else
        {
            printf("Penghapusan kk dibatalkan.\n");
            n = 1;
            Sleep(2000);
        }
    }

    if (!found)
    {
        fclose(file);
        fclose(temp);
        remove("tempKK.txt");
        printf("Data tidak ditemukan!!!");
        Sleep(2000);
        return;
    }

    if (n == 1)
    {
        fclose(file);
        fclose(temp);
        remove("tempKK.txt");
        Sleep(2000);
        return;
    }

    fclose(file);
    fclose(temp);
    remove("dataKK.txt");
    rename("tempKK.txt", "dataKK.txt");
}

void hapusKota()
{
    system("cls");
    FILE *file, *temp;
    DataKota kota;
    char userInput[20];
    char userInputCpy[20];
    char userChoose;
    bool found = false;
    int n = 0;

    file = fopen("dataKota.txt", "r");
    temp = fopen("tempKota.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    printf("Masukkan nama kota yang ingin dihapus: ");
    scanf("%s", userInput);
    strcpy(userInputCpy, userInput);
    enkripsiHuruf(userInput, keystr);

    int i = 0;
    rewind(file);
    while (fscanf(file, "%d %s", &kota.id, kota.namaKota) != EOF)
    {

        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(userInput, kota.namaKota) != 0)
        {
            if (found == false)
            {
                i++;
            }
        }
        else
        {
            found = true;
        }
    }

    if (found)
    {
        printf("Data dengan namaKota %s ditemukan.\n", userInputCpy);
        printf("Apakah Anda yakin ingin menghapus kota ini? [Y/N]: ");
        scanf(" %c", &userChoose);
        if (userChoose == 'Y' || userChoose == 'y')
        {
            printf("Data dengan namaKota %s telah dihapus.\n", userInputCpy);
            Sleep(2000);
            rewind(file);
            char line[1000];
            int n = 0;
            while (fgets(line, sizeof(line), file) != NULL)
            {
                if (n == i)
                {
                    n++;
                    continue;
                }
                fputs(line, temp);
                n++;
            }
            catatAktivitas("Menghapus kota penduduk", userInputCpy);
        }
        else
        {
            printf("Penghapusan kota dibatalkan.\n");
            n = 1;
            Sleep(2000);
        }
    }

    if (!found)
    {
        fclose(file);
        fclose(temp);
        remove("tempKota.txt");
        printf("Data tidak ditemukan!!!");
        Sleep(2000);
        return;
    }

    if (n == 1)
    {
        fclose(file);
        fclose(temp);
        remove("tempKota.txt");
        Sleep(2000);
        return;
    }

    fclose(file);
    fclose(temp);
    remove("dataKota.txt");
    rename("tempKota.txt", "dataKota.txt");
}