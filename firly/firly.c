#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
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
    printf("==================================================\n");
    printf(" Daftar No.KK Penduduk didalam file (Terdekripsi)\n");
    printf("==================================================\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Menggunakan sscanf untuk membaca data dari satu baris
        sscanf(line, "%d %s %s", &data.id, data.NIK, data.noKK);
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
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
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
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
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
            dekripsiInteger(data.noKK, keyInt);
            printf("No.KK           :    %s\n", data.noKK);
            printf("NIK             :    %s\n", data.NIK);
            printf("Nama            :    %s\n", data.nama);
            printf("Jenis Kelamin   :    %c\n", data.jk);
            printf("Agama           :    %s\n", data.agama);
            break;
        }
    }
    fclose(file);
}

void changeKK(DataPenduduk data, char *NIKSource, char *KKDestination, char *newCity)
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
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
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
            strcpy(data.namaKota, newCity);
        }

        fprintf(temp, "%d %s %s %s %s %c %s %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota);
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
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
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

        fprintf(temp, "%d %s %s %s %s %c %s %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota);
    }
    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("temp.txt", "dataPenduduk.txt");
}

void removeNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void logKejadianPenting(char *noKK1, char *noKK2, char *NIK1, char *NIK2, char *kejadianPenting)
{
    FILE *log;
    log = fopen("logKejadianPenting.txt", "a");
    if (log == NULL)
    {
        printf("Gagal membuka file\n");
        exit(1);
    }

    time_t now;
    time(&now);
    char *local = ctime(&now);
    removeNewline(local);
    if (strcmp(kejadianPenting, "Pernikahan") == 0)
    {
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
    char confirm;
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
    bool again = true;
    char newCity[50];

    while (again)
    {

        file = fopen("dataPenduduk.txt", "r");
        if (file == NULL)
        {
            printf("Error membuka/membuat file!");
            exit(1);
        }

        found = false;
        while (!found)
        {
            system("cls");
            displayDecryptedNoKKList();
            printf("Masukkan No.KK kedua pasangan\n");
            printf("No KK Pertama: ");
            fflush(stdin);
            scanf(" %s", userInput1);
            if (searchKK(userInput1) == false)
            {
                printf("No KK tersebut tidak ditemukan, kembali ke menu awal\n");
                Sleep(2000);
                kejadianPenting();
                return;
            }
            printf("No KK Kedua: ");
            fflush(stdin);
            scanf(" %s", userInput2);
            if (searchKK(userInput2) == false)
            {
                printf("No KK tersebut tidak ditemukan, kembali ke menu awal\n");
                Sleep(2000);
                kejadianPenting();
                return;
            }

            if (strcmp(userInput1, userInput2) == 0)
            {
                printf("No KK tidak boleh sama! Silakan coba lagi\n");
                Sleep(2000);
                continue;
            }
            else
            {
                found = true;
            }
            strcpy(userInputCpy1, userInput1);
            strcpy(userInputCpy2, userInput2);
            dekripsiInteger(userInputCpy1, keyInt);
            dekripsiInteger(userInputCpy2, keyInt);
        }

        sah = false;
        while (!sah)
        {
            valid = false;
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
                Sleep(1500);
                printf("Kembali ke menu awal? (Y/N): ");
                valid = false;
                while (!valid)
                {
                    fflush(stdin);
                    scanf(" %c", &confirm);
                    if (confirm == 'Y' || confirm == 'y')
                    {
                        menuAwal();
                        return;
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        sah = true;
                        valid = true;
                        again = true;
                        fclose(file);
                    }
                    else
                    {
                        printf("Input tidak valid!\n");
                        Sleep(2000);
                        valid = false;
                    }
                }
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

                    printf("Masukkan kota baru: ");
                    fflush(stdin);
                    scanf("%s", newCity);
                    enkripsiHuruf(newCity, keyStr);

                    newCity[strcspn(newCity, "\n")] = '\0';

                    switch (input)
                    {
                    case 1:
                        logKejadianPenting(userInput1, userInput2, userInput3, userInput4, "Pernikahan");
                        enkripsiInteger(userInput3, keyInt);
                        enkripsiInteger(userInput2, keyInt);
                        changeKK(data, userInput3, userInput2, newCity);
                        changeStatus(data, userInput3);
                        dekripsiInteger(userInput3, keyInt);
                        dekripsiInteger(userInput2, keyInt);
                        valid = true;
                        sah = true;
                        break;
                    case 2:
                        logKejadianPenting(userInput1, userInput2, userInput3, userInput4, "Pernikahan");
                        enkripsiInteger(userInput4, keyInt);
                        enkripsiInteger(userInput1, keyInt);
                        changeKK(data, userInput4, userInput1, newCity);
                        changeStatus(data, userInput4);
                        dekripsiInteger(userInput4, keyInt);
                        dekripsiInteger(userInput1, keyInt);
                        valid = true;
                        sah = true;
                        break;
                    }
                }
                fclose(file);
                remove("temp.txt");
                remove("dataPenduduk.txt");
                rename("tempData.txt", "dataPenduduk.txt");
                printf("Pernikahan berhasil!\n\n");
                valid = false;
                printf("Apakah anda ingin menambahkan data pernikahan lagi? (Y/N): ");
                while (!valid)
                {
                    fflush(stdin);
                    scanf(" %c", &confirm);
                    if (confirm == 'Y' || confirm == 'y')
                    {
                        again = true;
                        valid = true;
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        menuAwal();
                        return;
                    }
                    else
                    {
                        printf("Input tidak valid!\n");
                        Sleep(2000);
                        valid = false;
                    }
                }
            }
        }
    }
}

void Kematian()
{
    FILE *file, *temp;
    char userInput1[50];
    char userInput2[50];
    char confirm;
    bool found = false;
    bool valid = false;
    bool again = true;
    bool confirmBool = false;
    DataPenduduk data;
    while (again)
    {
        file = fopen("dataPenduduk.txt", "r");
        temp = fopen("temp1.txt", "w");
        found = false;
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
                Sleep(2000);
                continue;
            }
            found = true;
        }
        valid = false;
        while (!valid)
        {
            system("cls");
            dekripsiInteger(userInput1, keyInt);
            tampilkanIsiKK(data, userInput1);
            printf("Masukkan NIK mendiang: ");
            fflush(stdin);
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
            valid = false;
            printf("Data dengan NIK %s akan dihapus, apakah anda yakin? (Y/N): ", userInput2);
            while (!valid)
            {
                fflush(stdin);
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y')
                {
                    confirmBool = true;
                    valid = true;
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    confirmBool = false;
                    valid = true;
                }
                else
                {
                    printf("Input tidak valid!\n");
                    Sleep(2000);
                    valid = false;
                }
            }
            if (confirmBool)
            {
                logKejadianPenting(userInput1, "0", userInput2, "0", "Kematian");
                printf("Data dengan NIK %s telah dihapus.\n", userInput2);
                Sleep(1000);
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
            again = false;
            valid = false;
            while (!valid)
            {
                printf("Kembali ke menu? (Y/N): ");
                fflush(stdin);
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y')
                {
                    if (confirmBool)
                    {
                        fclose(file);
                        fclose(temp);
                        remove("dataPenduduk.txt");
                        rename("temp1.txt", "dataPenduduk.txt");
                        menuAwal();
                        return;
                    }
                    else
                    {
                        fclose(file);
                        fclose(temp);
                        remove("temp1.txt");
                        menuAwal();
                        return;
                    }
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    if (confirmBool)
                    {
                        fclose(file);
                        fclose(temp);
                        remove("dataPenduduk.txt");
                        rename("temp1.txt", "dataPenduduk.txt");
                        again = true;
                        valid = true;
                    }
                    else
                    {
                        fclose(file);
                        fclose(temp);
                        remove("temp1.txt");
                        again = true;
                        valid = true;
                    }
                }
                else
                {
                    printf("Input tidak valid!\n");
                    Sleep(2000);
                    valid = false;
                }
            }
        }

        if (!found)
        {
            fclose(file);
            fclose(temp);
            remove("tempDataPenduduk.txt");
            valid = false;
            while (!valid)
            {
                printf("Data tidak ditemukan, coba lagi? (Y/N): ");
                fflush(stdin);
                scanf("%c", &confirm);
                if (confirm == 'Y' || confirm == 'y')
                {
                    again = true;
                    valid = true;
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    menuAwal();
                    return;
                }
                else
                {
                    printf("Input tidak valid!\n");
                    Sleep(1000);
                    valid = false;
                }
            }
        }
    }
}

void Kelahiran()
{
    char userInput1[50];
    char confirm;
    bool found = false;
    bool again = true;
    bool valid = false;
    int count = 0, a;
    DataPenduduk data;
    FILE *file;
    while (again)
    {
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
        found = false;
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
        printf("Kota: ");
        fgets(data.namaKota, sizeof(data.namaKota), stdin);
        data.namaKota[strcspn(data.namaKota, "\n")] = '\0';
        for (int i = 0; data.namaKota[i]; i++)
        {
            if (data.namaKota[i] == ' ')
            {
                data.namaKota[i] = '_';
            }
        }

        char *status;
        status = "Belum_Kawin";
        strcpy(data.status, status);

        enkripsiInteger(data.NIK, keyInt);
        enkripsiInteger(data.noKK, keyInt);
        enkripsiHuruf(data.alamat, keyStr);
        enkripsiHuruf(data.namaKota, keyStr);
        file = fopen("dataPenduduk.txt", "a");
        fprintf(file, "%d %s %s %s %s %c %s %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota);
        dekripsiInteger(data.noKK, keyInt);
        dekripsiInteger(data.NIK, keyInt);
        logKejadianPenting(data.noKK, "0", data.NIK, "0", "Kelahiran");
        printf("Data Berhasil Ditambahkan!\n");
        printf("Apakah anda ingin menambahkan data kelahiran lagi? (Y/N): ");
        valid = false;
        while (!valid)
        {
            fflush(stdin);
            scanf(" %c", &confirm);
            if (confirm == 'Y' || confirm == 'y')
            {
                fclose(file);
                again = true;
                valid = true;
            }
            else if (confirm == 'N' || confirm == 'n')
            {
                fclose(file);
                again = false;
                valid = true;
            }
            else
            {
                printf("Input tidak valid!\n");
                Sleep(2000);
                valid = false;
            }
        }
    }
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

        case 0:
            menuAwal();
            break;
        default:
            printf("Input tidak valid!");
            Sleep(1000);
            break;
        }

    } while (userInput != 0);
}