#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "../disdukcapil.h"

extern int keyStr;
extern int keyInt;

void displayDecryptedNoKKList()
{
    FILE *file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    DataPenduduk data;
    char line[1000];
    printf("=================================================\n");
    printf("\tDaftar No.KK Penduduk (Terdekripsi)\n");
    printf("=================================================\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Menggunakan sscanf untuk membaca data dari satu baris
        sscanf(line, "%d %s %s %[^\n]s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        char decryptedNoKK[18];
        strcpy(decryptedNoKK, data.noKK);
        dekripsiInteger(decryptedNoKK, keyInt);
        printf("%s (Normal: %s)\n", decryptedNoKK, data.noKK);
    }
    printf("=================================================\n");

    fclose(file);
}

bool searchKK(char noKK[20])
{
    FILE *file;
    DataPenduduk data;
    bool found = false;
    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return false;
    }
    rewind(file);
    enkripsiInteger(noKK, keyInt);
    while (fscanf(file, "%d %s %s", &data.id, data.NIK, data.noKK) != EOF)
    {

        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(noKK, data.noKK) == 0)
        {
            found = true;
            break;
        }
    }
    fclose(file);
    return found;
}

bool searchNIK(char NIK[50], char KK[20])
{
    FILE *file;
    DataPenduduk data;
    bool found = false;
    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return false;
    }
    enkripsiInteger(NIK, keyInt);
    enkripsiInteger(KK, keyInt);
    rewind(file);
    while (fscanf(file, "%d %s %s %s %s %c", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk) != EOF)
    {

        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(NIK, data.NIK) == 0 && strcmp(KK, data.noKK) == 0)
        {
            found = true;
            break;
        }
    }
    dekripsiInteger(NIK, keyInt);
    dekripsiInteger(KK, keyInt);
    fclose(file);
    return found;
}

char getGenderFromNIK(char NIK[50])
{
    FILE *file;
    DataPenduduk data;
    bool found = false;
    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return false;
    }
    enkripsiInteger(NIK, keyInt);
    rewind(file);
    while (fscanf(file, "%d %s %s %s %s %c", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk) != EOF)
    {

        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(NIK, data.NIK) == 0)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        dekripsiInteger(NIK, keyInt);
        fclose(file);
        return data.jk;
    }
    else
    {
        dekripsiInteger(NIK, keyInt);
        fclose(file);
        return 0;
    }
}

void tampilkanIsiKK(DataPenduduk data, char userInput[20])
{
    system("cls");
    FILE *file;
    file = fopen("dataPenduduk.txt", "r");
    printf("====== List data dalam KK %s ======\n\n", userInput);
    enkripsiInteger(userInput, keyInt);
    rewind(file);
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }

        if (strcmp(data.noKK, userInput) == 0)
        {
            dekripsiInteger(data.NIK, keyInt);
            printf("NIK             :    %s\n", data.NIK);
            printf("Nama            :    %s\n", data.nama);
            printf("Jenis Kelamin   :    %c\n", data.jk);
            printf("Agama           :    %s\n", data.agama);
            printf("Status          :    %s\n\n", data.status);
        }
    }
    dekripsiInteger(userInput, keyInt);
    fclose(file);
}

void tampilkanIsiNIK(DataPenduduk data, char userInput[50])
{
    FILE *file;
    file = fopen("dataPenduduk.txt", "r");
    rewind(file);
    enkripsiInteger(userInput, keyInt);
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }

        if (strcmp(data.NIK, userInput) == 0)
        {
            dekripsiInteger(data.NIK, keyInt);
            printf("NIK             :    %s\n", data.NIK);
            printf("Nama            :    %s\n", data.nama);
            printf("Jenis Kelamin   :    %c\n", data.jk);
            printf("Agama           :    %s\n", data.agama);
            break;
        }
    }
    fclose(file);
}

void changeKK(DataPenduduk data, char *NIKSource, char *KKDestination)
{
    FILE *file, *temp;
    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("tempData.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Gagal membuka/membuat file!\n");
        exit(1);
    }

    char *kawin = "Kawin";
    rewind(file);
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }

        if (strcmp(NIKSource, data.NIK) == 0)
        {
            strcpy(data.noKK, KKDestination);
            strcpy(data.status, kawin);
        }

        fprintf(temp, "%d %s %s %s %s %c %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
    }
    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("tempData.txt", "dataPenduduk.txt");
}

void changeStatus(DataPenduduk data, char *NIK)
{
    FILE *file, *temp;
    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Gagal membuka/membuat file!\n");
        exit(1);
    }

    char *kawin = "Kawin";
    rewind(file);
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }

        if (strcmp(NIK, data.NIK) == 0)
        {
            strcpy(data.status, kawin);
        }

        fprintf(temp, "%d %s %s %s %s %c %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
    }
    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("temp.txt", "dataPenduduk.txt");
}

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void logKejadianPenting (char noKK1[20], char noKK2[20], char NIK1[50], char NIK2[50], char *kejadianPenting){
    FILE *log;
    log = fopen("logKejadianPenting.txt", "a");
    if (log == NULL){
        printf("Gagal membuka file\n");
        exit(1);
    }

    time_t now;
    time (&now);
    char *local = ctime(&now);
    removeNewline(local);
    if (strcmp(kejadianPenting, "Pernikahan") == 0) {
        printf("TRIGGERED\n");
        dekripsiInteger(noKK1, keyInt);
        dekripsiInteger(noKK2, keyInt);
        dekripsiInteger(NIK1, keyInt);
        dekripsiInteger(NIK2, keyInt);
        fprintf(log, "%s - Telah terjadi pernikahan pada KK %s dan KK %s, dengan NIK pasangan %s dan %s\n", local, noKK1, noKK2, NIK1, NIK2);
        fclose(log);
        return;
    }
    fprintf(log, "%s - Telah terjadi %s pada KK %s dengan NIK %s\n", local, kejadianPenting, noKK1, NIK1);
    fclose(log);
}

void Pernikahan()
{
    system("cls");
    FILE *file;
    DataPenduduk data;
    int input;
    char userInput1[20];
    char userInput2[20];
    char userInput3[50];
    char userInput4[50];
    char userInputCpy1[50];
    char userInputCpy2[50];
    char gender1 = ' ';
    char gender2 = ' ';
    bool found = false;
    bool sah = false;
    bool valid = false;

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    while (!found)
    {
        displayDecryptedNoKKList();
        printf("Masukkan No.KK kedua pasangan\n");
        printf("No KK Pertama: ");
        fflush(stdin);
        scanf("%s", userInput1);
        if (searchKK(userInput1) == false)
        {
            printf("No KK tersebut tidak ditemukan\n");
            continue;
        }
        printf("No KK Kedua: ");
        fflush(stdin);
        scanf("%s", userInput2);
        if (searchKK(userInput2) == false)
        {
            printf("No KK tersebut tidak ditemukan\n");
            continue;
        }
        strcpy(userInputCpy1, userInput1);
        strcpy(userInputCpy2, userInput2);
        dekripsiInteger(userInputCpy1, keyInt);
        dekripsiInteger(userInputCpy2, keyInt);
        found = true;
    }

    found = false;
    while (!sah)
    {
        while (!valid)
        {
            system("cls");
            tampilkanIsiKK(data, userInputCpy1);
            printf("Masukkan NIK calon pengantin pertama: ");
            fflush(stdin);
            scanf("%s", userInput3);
            if (searchNIK(userInput3, userInputCpy1) == true)
            {
                valid = true;
            }
            else
            {
                printf("NIK tersebut tidak terdaftar dalam KK!\n");
                valid = false;
                Sleep(2000);
            }
        }

        valid = false;
        while (!valid)
        {
            system("cls");
            tampilkanIsiKK(data, userInputCpy2);
            printf("Masukkan NIK calon pengantin kedua: ");
            fflush(stdin);
            scanf("%s", userInput4);
            if (searchNIK(userInput4, userInputCpy2) == true)
            {
                valid = true;
            }
            else
            {
                printf("NIK tersebut tidak terdaftar dalam KK!\n");
                Sleep(2000);
            }
        }

        gender1 = getGenderFromNIK(userInput3);
        gender2 = getGenderFromNIK(userInput4);

        if (gender1 == gender2)
        {
            printf("Tidak bisa menikahi sesama jenis!\n");
            Sleep(3000);
            sah = false;
        }
        else
        {
            system("cls");
            printf("Mohon Tunggu...");
            Sleep(1000);
            valid = false;
            while (!valid)
            {
                system("cls");
                tampilkanIsiNIK(data, userInput3);
                printf("\nAkan menikah dengan\n\n");
                tampilkanIsiNIK(data, userInput4);
                printf("\n===== Opsi Perpindahan KK =====\n\n");
                printf("1. Pengantin 1 masuk KK pengantin 2\n");
                printf("2. Pengantin 2 masuk KK pengantin 1\n\n");
                printf("Opsi: ");
                fflush(stdin);
                scanf("%d", &input);
                switch (input)
                {
                case 1:
                    logKejadianPenting(userInput1, userInput2, userInput3, userInput4, "Pernikahan");
                    changeKK(data, userInput3, userInput2);
                    changeStatus(data, userInput3);
                    valid = true;
                    sah = true;
                    break;
                case 2:
                    logKejadianPenting(userInput1, userInput2, userInput3, userInput4, "Pernikahan");
                    changeKK(data, userInput4, userInput1);
                    changeStatus(data, userInput4);
                    valid = true;
                    sah = true;
                    break;
                }
            }
        }
    }
    fclose(file);
    remove("temp.txt");
    remove("dataPenduduk.txt");
    rename("tempData.txt", "dataPenduduk.txt");
    printf("Pernikahan berhasil!\n");
    Sleep(2000);
}

void Kematian()
{
    FILE *file, *temp;
    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("temp1.txt", "w");
    char userInput1[50];
    char userInput2[50];
    bool found = false;
    bool valid = false;
    DataPenduduk data;
    while (!found)
    {
        system("cls");
        displayDecryptedNoKKList();
        printf("Didalam KK mana terjadi kematian: ");
        fflush(stdin);
        scanf("%s", userInput1);
        if (searchKK(userInput1) == false)
        {
            printf("No KK tersebut tidak ditemukan\n");
            Sleep(1000);
            continue;
        }
        found = true;
    }

    while (!valid)
    {
        system("cls");
        dekripsiInteger(userInput1, keyInt);
        tampilkanIsiKK(data, userInput1);
        printf("Masukkan NIK mendiang: ");
        scanf("%s", userInput2);
        if (searchNIK(userInput2, userInput1) == false)
        {
            printf("NIK Tidak ada didalam KK!\n");
            enkripsiInteger(userInput1, keyInt);
            Sleep(1000);
            valid = false;
        }
        else
        {
            valid = true;
        }
    }

    found = false;
    enkripsiInteger(userInput2, keyInt);
    int i = 0;
    rewind(file);
    while (fscanf(file, "%d %s", &data.id, data.NIK) != EOF)
    {
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                break;
            }
        }
        if (strcmp(userInput2, data.NIK) != 0)
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
        dekripsiInteger(userInput2, keyInt);
        logKejadianPenting(userInput1, "0", userInput2, "0", "Kematian");
        printf("Data dengan NIK %s telah dihapus.\n", userInput2);
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
    }

    if (!found)
    {
        fclose(file);
        fclose(temp);
        remove("tempDataPenduduk.txt");
        printf("Data tidak ditemukan!");
        Sleep(2000);
        return;
    }

    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("temp1.txt", "dataPenduduk.txt");
}

void Kelahiran()
{
    char userInput1[50];
    bool found = false;
    int count = 0, a;
    DataPenduduk data;
    FILE *file;
    file = fopen("dataPenduduk.txt", "r");
    if (file != NULL)
    {
        for (a = getc(file); a != EOF; a = getc(file))
        {
            if (a == '\n')
            {
                count = count + 1;
            }
        }
        fclose(file);
    }
    data.id = count;
    while (!found)
    {
        system("cls");
        displayDecryptedNoKKList();
        printf("Didalam KK mana terjadi kelahiran: ");
        fflush(stdin);
        scanf("%s", userInput1);
        if (searchKK(userInput1) == false)
        {
            printf("No KK tersebut tidak ditemukan\n");
            Sleep(1000);
            continue;
        }
        found = true;
    }
    system("cls");
    printf("====== Masukkan Data Bayi ======\n\n");
    printf("NIK: ");
    fflush(stdin);
    scanf("%s", data.NIK);
    dekripsiInteger(userInput1, keyInt);
    strcpy(data.noKK, userInput1);
    printf("Nama Lengkap: ");
    getchar();
    fgets(data.nama, sizeof(data.nama), stdin);
    data.nama[strcspn(data.nama, "\n")] = '\0';
    for (int i = 0; data.nama[i]; i++)
    {
        if (data.nama[i] == ' ')
        {
            data.nama[i] = '_';
        }
    }

    fflush(stdin);
    printf("Tanggal Lahir(dd/mm/yyyy): ");
    scanf("%s", data.tanggalLahir);

    fflush(stdin);
    printf("Jenis Kelamin (L/P): ");
    scanf(" %c", &data.jk);

    printf("Alamat: ");
    getchar();
    fgets(data.alamat, sizeof(data.alamat), stdin);
    data.alamat[strcspn(data.alamat, "\n")] = '\0';
    for (int i = 0; data.alamat[i]; i++)
    {
        if (data.alamat[i] == ' ')
        {
            data.alamat[i] = '_';
        }
    }
    printf("Tempat Lahir: ");
    fgets(data.tempat_lahir, sizeof(data.tempat_lahir), stdin);
    data.tempat_lahir[strcspn(data.tempat_lahir, "\n")] = '\0';
    for (int i = 0; data.tempat_lahir[i]; i++)
    {
        if (data.tempat_lahir[i] == ' ')
        {
            data.tempat_lahir[i] = '_';
        }
    }
    printf("Agama: ");
    fgets(data.agama, sizeof(data.agama), stdin);
    data.agama[strcspn(data.agama, "\n")] = '\0';
    for (int i = 0; data.agama[i]; i++)
    {
        if (data.agama[i] == ' ')
        {
            data.agama[i] = '_';
        }
    }

    char *status;
    status = "Belum_Kawin";
    strcpy(data.status, status);

    enkripsiInteger(data.NIK, keyInt);
    enkripsiInteger(data.noKK, keyInt);
    enkripsiHuruf(data.alamat, keyStr);
    file = fopen("dataPenduduk.txt", "a");
    fprintf(file, "%d %s %s %s %s %c %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
    dekripsiInteger(data.noKK, keyInt);
    dekripsiInteger(data.NIK, keyInt);
    logKejadianPenting(data.noKK, "0", data.NIK, "0", "Kelahiran");
    printf("Data Berhasil Ditambahkan");
    Sleep(2000);
    fclose(file);
}

void kejadianPenting()
{
    system("cls");
    int userInput;
    do
    {
        system("cls");
        printf("Silakan pilih kejadian penting:\n\n");
        printf("1. Pernikahan\n");
        printf("2. Kelahiran\n");
        printf("3. Kematian\n");
        printf("0. Kembali\n\n");
        printf("Opsi: ");

        fflush(stdin);
        scanf("%d", &userInput);
        switch (userInput)
        {
        case 1:
            Pernikahan();
            break;

        case 2:
            Kelahiran();
            break;

        case 3:
            Kematian();
            break;

        case 4:
            menuAwal();
            break;
        default:
            printf("Input tidak valid!");
            Sleep(1000);
            break;
        }

    } while (userInput != '0');
}

