#include "disdukcapil.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int keyStr = 18; // Tidak boleh >= 26
int keyInt = 7;  // Tidak boleh >= 10
// Procedure tambah admin

AktivitasPengguna aktifPengguna;

void gotoxy(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loading()
{
    system("cls");
    system("color B");

    gotoxy(30, 9);
    printf("              =======================");
    gotoxy(30, 10);
    printf("               MOHON TUNGGU SEBENTAR");
    gotoxy(30, 12);
    printf("              =======================");

    Sleep(500);
    gotoxy(30, 11);
    printf("                     . ");
    Sleep(500);
    printf(". ");
    Sleep(500);
    printf(". ");
    Sleep(500);
    printf(". ");
    Sleep(500);
    printf(". ");
}

int pilihanMenuAwal()
{
    loading();
    int input;
    system("cls");
    char terminate;

    gotoxy(30, 2);
    printf("                     SELAMAT DATANG                         \n");
    gotoxy(30, 3);
    printf("                           DI                               \n");
    gotoxy(30, 4);
    printf("             SISTEM DISDUKCAPIL BERBASIS CLI                 \n\n");
    gotoxy(30, 5);
    printf("               ===========================                   \n\n");
    gotoxy(30, 7);
    printf("                1. MASUK                             \n");
    gotoxy(30, 8);
    printf("                2. KELUAR                            \n");

    gotoxy(30, 11);
    printf("          PILIHAN	: ");
    scanf("%d", &input);
    scanf("%c", &terminate);

    switch (input)
    {
    case 1:
        loginAdmin();
        break;

    case 2:
        system("cls");
        break;
    }
}

void addAdmin()
{
    // Membungkus password & username menjadi struct
    Admin admin;

    // input username
    printf("Masukkan Username : ");
    scanf("%s", admin.username);
    // input password
    printf("Masukkan Password : ");
    scanf("%s", admin.password);

    // proses enkripsi sebelum masuk file
    generateAngkaGeser(&admin.jumlahGeser);              // Sebelum disimpan ke file, generate key terlebih dahulu untuk disimpan ke struct
    enkripsiPassword(admin.password, admin.jumlahGeser); // Enkripsi password dengan parameter input password dan jumlahgeser sebelumnya
    simpanFileAdmin(admin);
}

// Function untuk generate kunci random & arah random
void generateAngkaGeser(int *jumlahgeser)
{
    // Inisialisasi seed/nilai acak berdasarkan waktu saat ini
    srand(time(NULL));
    // Menghasilkan nilai acak untuk pergeseran
    *jumlahgeser = rand() % 26 + 1;
}

// Proses enkripsi
void enkripsiPassword(char *password, int jumlahgeser)
{
    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            password[i] = ((password[i] - 'A') + jumlahgeser) % 26 + 'A';
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            password[i] = ((password[i] - 'a') + jumlahgeser) % 26 + 'a';
        }
    }
}

void simpanFileAdmin(Admin admin)
{
    FILE *file = fopen("admin.txt", "a"); // mode "a" untuk menambahkan ke file
    if (file == NULL)
    {
        printf("Gagal membuka file.\n");
        exit(1);
    }

    fprintf(file, "%s %s %d\n", admin.username, admin.password, admin.jumlahGeser);
    fclose(file); // menutup file
}

// Procedure Login
void loginAdmin()
{
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }
    Admin admin;
    char usernameCompare[50];
    char passwordCompare[50];
    bool loginBerhasil;

    while (!loginBerhasil)
    {
        system("cls"); // Assuming you are using Windows, change to "clear" if on Unix/Linux
        printf("==============================\n");
        printf("======  SILAHKAN LOGIN  ======\n");
        printf("==============================\n\n");
        printf("Masukkan Username: ");
        scanf("%s", admin.username);
        printf("Masukkan Password: ");
        scanf("%s", admin.password);

        for (int i = 0; i < 50; i++)
        {
            fscanf(file, "%s %s %d", usernameCompare, passwordCompare, &admin.jumlahGeser);
            dekripsiPassword(passwordCompare, admin.jumlahGeser);

            if (strcmp(admin.username, usernameCompare) == 0 && strcmp(admin.password, passwordCompare) == 0)
            {
                loginBerhasil = true;
                strcpy(aktifPengguna.username, admin.username);
                aktifPengguna.loggedIn = true;
                catatLogin(); // Mencatat aktivitas login
                menuAwal();
                break;
            }
        }
        if (loginBerhasil != true)
        {
            printf("Username atau Password Salah, silakan coba lagi.\n");
            rewind(file);
        }
    }
}

void menuAwal()
{
    int pilihan;
    do
    {
        loading();
        system("cls");
        printf("Menu:\n");
        printf("1. Lihat Data Penduduk\n");
        printf("2. Edit Penduduk\n");
        printf("3. Add Penduduk\n");
        printf("4. Delete Data Penduduk\n");
        printf("5. Tambah Admin\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            showPenduduk();
            system("cls");
            break;
        case 2:
            editPenduduk();
            system("cls");
            break;
        case 3:
            addPenduduk();
            system("cls");
            break;
        case 4:
            deleteData();
            system("cls");
            break;
        case 5:
            addAdmin();
            // system("cls");
            break;
        case 6:
            pilihanMenuAwal();
            system("cls");
            break;
        default:
            printf("Masukkan tidak valid, coba kembali.\n");
            break;
        }
    } while (pilihan != 5);
}

void dekripsiPassword(char *passwordCompare, int jumlahGeser)
{
    int i;
    for (i = 0; i < strlen(passwordCompare); i++)
    {
        if (passwordCompare[i] >= 'A' && passwordCompare[i] <= 'Z')
        {
            passwordCompare[i] = ((passwordCompare[i] - 'A') - jumlahGeser + 26) % 26 + 'A';
        }
        else if (passwordCompare[i] >= 'a' && passwordCompare[i] <= 'z')
        {
            passwordCompare[i] = ((passwordCompare[i] - 'a') - jumlahGeser + 26) % 26 + 'a';
        }
    }
}

// add Data Penduduk
void addPenduduk()
{
    DataPenduduk dat;
    FILE *file;
    int cek = 0;
    char fnama[18];
    int count = 0, a;

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

    system("cls"); // Assuming you are using Windows, change to "clear" if on Unix/Linux
    printf("=================================================\n");
    printf("\tINPUT DATA PENDUDUK\n");
    printf("=================================================\n");
    dat.id = count;
    printf("NIK: ");
    scanf("%s", dat.NIK);
    fflush(stdin);
    printf("Nama Lengkap: ");
    fgets(dat.nama, sizeof(dat.nama), stdin);
    dat.nama[strcspn(dat.nama, "\n")] = '\0'; // Menghilangkan karakter newline jika ada
    fflush(stdin);
    printf("Jenis Kelamin (L/P): ");
    scanf("%c", &dat.jk);
    fflush(stdin);
    printf("Alamat: ");
    fgets(dat.alamat, sizeof(dat.alamat), stdin);
    dat.alamat[strcspn(dat.alamat, "\n")] = '\0'; // Menghilangkan karakter newline jika ada
    fflush(stdin);
    printf("Tempat Lahir: ");
    fgets(dat.tempat_lahir, sizeof(dat.tempat_lahir), stdin);
    dat.tempat_lahir[strcspn(dat.tempat_lahir, "\n")] = '\0'; // Menghilangkan karakter newline jika ada
    fflush(stdin);
    printf("Agama: ");
    fgets(dat.agama, sizeof(dat.agama), stdin);
    dat.agama[strcspn(dat.agama, "\n")] = '\0'; // Menghilangkan karakter newline jika ada
    fflush(stdin);
    printf("Status: ");
    fgets(dat.status, sizeof(dat.status), stdin);
    dat.status[strcspn(dat.status, "\n")] = '\0'; // Menghilangkan karakter newline jika ada
    fflush(stdin);
    printf("=================================================\n");

    enkripsiInteger(dat.NIK, keyInt);
    file = fopen("dataPenduduk.txt", "a");
    while (fscanf(file, "%s", fnama) != EOF)
    {
        if (strcmp(dat.NIK, fnama) == 0)
        {
            cek = 1;
            break;
        }
    }
    fclose(file);

    if (cek == 1)
    {
        printf("Data Duplikat\n");
        return;
    }
    else
    {
        file = fopen("dataPenduduk.txt", "a");
        enkripsiHuruf(dat.alamat, keyStr);
        fprintf(file, "%d %s %s %c %s %s %s %s\n", dat.id, dat.NIK, dat.nama, dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status);
        fclose(file);
        printf("Data berhasil tersimpan\n");

        // Catat aktivitas pengguna
        catatAktivitas("Menambahkan data penduduk", dat.NIK);
    }
}

void enkripsiHuruf(char *kalimat, int key)
{
    for (int i = 0; kalimat[i] != '\0'; i++)
    {
        if (kalimat[i] >= 'A' && kalimat[i] <= 'Z')
        {
            kalimat[i] = 'A' + ((kalimat[i] - 'A' + key) % 26);
        }
        else if (kalimat[i] >= 'a' && kalimat[i] <= 'z')
        {
            kalimat[i] = 'a' + ((kalimat[i] - 'a' + key) % 26);
        }
    }
}

void dekripsiHuruf(char *kalimat, int key)
{
    for (int i = 0; kalimat[i] != '\0'; i++)
    {
        if (kalimat[i] >= 'A' && kalimat[i] <= 'Z')
        {
            kalimat[i] = 'A' + ((kalimat[i] - 'A' - key + 26) % 26);
        }
        else if (kalimat[i] >= 'a' && kalimat[i] <= 'z')
        {
            kalimat[i] = 'a' + ((kalimat[i] - 'a' - key + 26) % 26);
        }
    }
}

void enkripsiInteger(char *num, int key)
{
    for (int i = 0; num[i] != '\0'; i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            num[i] = '0' + ((num[i] - '0' + key) % 10);
        }
    }
}

void dekripsiInteger(char *num, int key)
{
    for (int i = 0; num[i] != '\0'; i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            num[i] = '0' + ((num[i] - '0' - key + 10) % 10);
        }
    }
}
// Prosedur masih belum dipakai

void deleteData()
{
    system("cls");
    FILE *file, *temp;
    DataPenduduk data;
    char userInput[20];
    char userInputCpy[20];
    char userChoose;
    bool found = false;

    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("tempDataPenduduk.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    printf("Masukkan NIK data yang ingin dihapus: ");
    scanf("%s", userInput);
    strcpy(userInputCpy, userInput);
    enkripsiInteger(userInput, keyInt);

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
        if (strcmp(userInput, data.NIK) != 0)
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


    if (found){
        printf("Data dengan NIK %s telah dihapus.", userInputCpy);
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
        catatAktivitas("Menghapus data penduduk", userInputCpy);
    }

    if (!found){
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
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");
}

// edit data pendudukks
void editPenduduk()
{
    FILE *file, *temp;
    DataPenduduk data;
    char userInput[50];
    char userInputCpy[50];
    char userChoose;
    bool found = false;

    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("tempDataPenduduk.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    system("cls");
    displayDecryptedNikList();
    printf("Masukkan NIK data yang ingin diedit: ");
    scanf("%s", userInput);
    strcpy(userInputCpy, userInput);
    enkripsiInteger(userInput, keyInt);

    while (fscanf(file, "%d %s %s %c %s %s %s %s", &data.id, data.NIK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        if (strcmp(userInput, data.NIK) == 0)
        {
            found = true;
            printf("Data dengan NIK %s telah ditemukan, yakin ingin mengeditnya? [Y/N]", userInputCpy);
            fflush(stdin);
            scanf(" %c", &userChoose);
            if (userChoose == 'Y' || userChoose == 'y')
            {
                printf("Masukkan data yang baru:\n");
                printf("Nama Lengkap: ");
                scanf(" %[^\n]", data.nama);
                getchar();
                printf("Jenis Kelamin (L/P): ");
                scanf(" %c", &data.jk);
                printf("Alamat: ");
                scanf(" %[^\n]", data.alamat);
                getchar();
                printf("Tempat Lahir: ");
                scanf(" %[^\n]", data.tempat_lahir);
                getchar();
                printf("Agama: ");
                scanf(" %[^\n]", data.agama);
                getchar();
                printf("Status: ");
                scanf(" %[^\n]", data.status);
                getchar();

                fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
                printf("Data berhasil diubah!\n");

                // Catat aktivitas pengguna
                catatAktivitas("Mengedit data penduduk", data.NIK);
            }
            else
            {
                fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
            }
        }
        else
        {
            fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        }
    }

    if (!found)
    {
        printf("NIK Tidak Ditemukan\n");
    }

    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");
}

void showPenduduk()
{
    system("cls");
    FILE *file;
    DataPenduduk data;
    char userChoose;

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return;
    }

    printf("====================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status");
    printf("====================================================================================================\n");

    while (fscanf(file, "%d %s %s %c %s %s %s %s", &data.id, data.NIK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s |\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
    }

    printf("====================================================================================================\n");

    fclose(file);

    printf("Apakah anda ingin kembali ke menu? [Y/N] : ");
    scanf(" %c", &userChoose);
    if (userChoose == 'Y' || userChoose == 'y')
    {
        menuAwal();
    }
}

void displayDecryptedNikList()
{
    FILE *file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    DataPenduduk data;
    char line[MAX_LINE_LENGTH];
    printf("=================================================\n");
    printf("\tDaftar NIK Penduduk (Terdekripsi)\n");
    printf("=================================================\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Menggunakan sscanf untuk membaca data dari satu baris
        sscanf(line, "%d %s %[^\n]s %c %s %s %s %s", &data.id, data.NIK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        char decryptedNik[18];
        strcpy(decryptedNik, data.NIK);
        dekripsiInteger(decryptedNik, keyInt);
        printf("%s (Normal: %s)\n", decryptedNik, data.NIK);
    }
    printf("=================================================\n");

    fclose(file);
}

void catatAktivitas(char *aksi, char *NIK)
{
    FILE *logFile = fopen("history.txt", "a");
    if (logFile == NULL)
    {
        printf("Gagal membuka file log.\n");
        return;
    }

    time_t now;
    time(&now);
    fprintf(logFile, "[%s] Pengguna %s melakukan aksi: %s pada data dengan NIK: %s\n", ctime(&now), aktifPengguna.username, aksi, NIK);
    fclose(logFile);
}

void catatLogin()
{
    FILE *logFile = fopen("history.txt", "a");
    if (logFile == NULL)
    {
        printf("Gagal membuka file log.\n");
        return;
    }

    time_t now;
    time(&now);
    fprintf(logFile, "[%s] Pengguna %s melakukan login.\n", ctime(&now), aktifPengguna.username);
    fclose(logFile);
}

void catatEdit(char *NIK)
{
    FILE *logFile = fopen("history.txt", "a");
    if (logFile == NULL)
    {
        printf("Gagal membuka file log.\n");
        return;
    }

    time_t now;
    time(&now);
    fprintf(logFile, "[%s] Pengguna %s melakukan edit pada data dengan NIK: %s\n", ctime(&now), aktifPengguna.username, NIK);
    fclose(logFile);
}

void replaceSpaceWithUnderscore(char *str)
{
    while (*str)
    {
        if (*str == ' ')
        {
            *str = '_';
        }
        str++;
    }
}
