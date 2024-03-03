#include "disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int keyStr = 18; // Tidak boleh >= 26
int keyInt = 7;  // Tidak boleh >= 10
// Procedure tambah admin
void addAdmin()
{
    // membungkus password&username menjadi struct
    Admin admin;

    // input username
    printf("Masukkan username admin : ");
    scanf("%s", admin.username);

    // input password
    printf("Masukkan password admin : ");
    scanf("%s", admin.password);

    // proses enkripsi sebelum masuk ke file
    generateAngkaGeser(&admin.jumlahGeser, &admin.arahGeser);             // Sebelum disimpan ke file, generate key terlebih dahulu untuk disimpan ke struct
    enkripsiPassword(admin.password, admin.jumlahGeser, admin.arahGeser); // Enkripsi password dengan parameter input password dan jumlahgeser sebelumnya
    simpanFileAdmin(admin);                                               // Menyimpan hasil username,password(enkripsi),jumlahgeser,arahgeser
}

// Function untuk generate kunci random & arah random
void generateAngkaGeser(int *jumlahgeser, char *arahgeser)
{
    // Inisialisasi seed/nilai acak berdasarkan waktu saat ini
    srand(time(NULL));
    // Menghasilkan nilai acak untuk pergeseran
    *jumlahgeser = rand() % 26 + 1;
    // Menghasilkan nilai acak untur arah kiri atau kanan
    *arahgeser = rand() % 2 == 0 ? 'L' : 'R';
}

// Proses enkripsi
void enkripsiPassword(char *password, int jumlahgeser, char arahGeser)
{
    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            if (arahGeser == 'R')
            {
                password[i] = ((password[i] - 'A') + jumlahgeser) % 26 + 'A';
            }
            else if (arahGeser == 'L')
            {
                password[i] = ((password[i] - 'A') + jumlahgeser + 26) % 26 + 'A';
            }
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            if (arahGeser == 'R')
            {
                password[i] = ((password[i] - 'a') + jumlahgeser) % 26 + 'a';
            }
            else if (arahGeser == 'L')
            {
                password[i] = ((password[i] - 'a') + jumlahgeser + 26) % 26 + 'a';
            }
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

    fprintf(file, "%s %s %d %c\n", admin.username, admin.password, admin.jumlahGeser, admin.arahGeser);
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

        printf("Masukkan Username: ");
        scanf("%s", admin.username);
        printf("Masukkan Password: ");
        scanf("%s", admin.password);

        for (int i = 0; i < 50; i++)
        {
            fscanf(file, "%s %s %d %c", usernameCompare, passwordCompare, &admin.jumlahGeser, &admin.arahGeser);
            dekripsiPassword(passwordCompare, admin.jumlahGeser, admin.arahGeser);

            if (strcmp(admin.username, usernameCompare) == 0 && strcmp(admin.password, passwordCompare) == 0)
            {
                printf("Login Berhasil!\n\n");
                loginBerhasil = true;
                break;
            }
        }
        if (!loginBerhasil)
        {
            printf("Username atau Password Salah, silakan coba lagi.\n");
            rewind(file);
        }
    }
}

void dekripsiPassword(char *passwordCompare, int jumlahGeser, char arahGeser)
{
    int i;
    for (i = 0; i < strlen(passwordCompare); i++)
    {
        if (passwordCompare[i] >= 'A' && passwordCompare[i] <= 'Z')
        {
            if (arahGeser == 'R')
            {
                passwordCompare[i] = ((passwordCompare[i] - 'A') - jumlahGeser) % 26 + 'A';
            }
            else if (arahGeser == 'L')
            {
                passwordCompare[i] = ((passwordCompare[i] - 'A') - jumlahGeser + 26) % 26 + 'A';
            }
        }
        else if (passwordCompare[i] >= 'a' && passwordCompare[i] <= 'z')
        {
            if (arahGeser == 'R')
            {
                passwordCompare[i] = ((passwordCompare[i] - 'a') - jumlahGeser) % 26 + 'a';
            }
            else if (arahGeser == 'L')
            {
                passwordCompare[i] = ((passwordCompare[i] - 'a') - jumlahGeser + 26) % 26 + 'a';
            }
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
    printf("Nama Lengkap: ");
    scanf("%s", dat.nama);
    fflush(stdin);
    printf("Jenis Kelamin (L/P): ");
    scanf("%c", &dat.jk);
    printf("Alamat: ");
    scanf("%s", dat.alamat);
    printf("Tempat Lahir: ");
    scanf("%s", dat.tempat_lahir);
    printf("Agama: ");
    scanf("%s", dat.agama);
    printf("Status: ");
    scanf("%s", dat.status);
    printf("=================================================\n");

    enkripsiInteger(dat.NIK, keyInt);
    file = fopen("dataPenduduk.txt", "r");
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

// void dekripsiInteger(char *num, int key)
// {
//     for (int i = 0; num[i] != '\0'; i++)
//     {
//         if (num[i] >= '0' && num[i] <= '9')
//         {
//             num[i] = '0' + ((num[i] - '0' - key + 10) % 10);
//         }
//     }
// } Prosedur masih belum dipakai
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

    while (fscanf(file, "%d %s %s %c %s %s %s %s", &data.id, data.NIK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        if (strcmp(userInput, data.NIK) != 0)
        {
            fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        }
        else
        {
            found = true;
            printf("Data dengan NIK %s telah ditemukan, yakin ingin menghapusnya? [Y/N]", userInputCpy);
            fflush(stdin);
            scanf("%c", &userChoose);
            if (userChoose == 'N' || userChoose == 'n')
            {
                fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
            }
        }
    }
    if (!found){
        printf("NIK Tidak Ditemukan\n");
    }

    if (userChoose == 'Y' || userChoose == 'y'){
        printf("Data Berhasil Dihapus!\n");
    }
    fclose(file);
    fclose(temp);
    remove("dataPenduduk.txt");
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");
}

//edit data penduduk

void editPenduduk()
{
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

    printf("Masukkan NIK data yang ingin diedit: ");
    scanf("%s", userInput);
    strcpy(userInputCpy, userInput);
    enkripsiInteger(userInput, keyInt);

    while (fscanf(file, "%d %s %s %c %s %s %s %s", &data.id, data.NIK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF)
    {
        if (strcmp(userInput, data.NIK) != 0)
        {
            fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        }
        else
        {
            found = true;
            printf("Data dengan NIK %s telah ditemukan, yakin ingin mengeditnya? [Y/N]", userInputCpy);
            fflush(stdin);
            scanf("%c", &userChoose);
            if (userChoose == 'Y' || userChoose == 'y')
            {
                // Implementasi pengeditan data
                printf("Masukkan data yang baru:\n");
                printf("Nama Lengkap: ");
                scanf("%s", data.nama);
                fflush(stdin);
                printf("Jenis Kelamin (L/P): ");
                scanf("%c", &data.jk);
                printf("Alamat: ");
                scanf("%s", data.alamat);
                printf("Tempat Lahir: ");
                scanf("%s", data.tempat_lahir);
                printf("Agama: ");
                scanf("%s", data.agama);
                printf("Status: ");
                scanf("%s", data.status);
                enkripsiHuruf(data.alamat, keyStr);
                fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
                printf("Data berhasil diubah!\n");
            }
            else
            {
                fprintf(temp, "%d %s %s %c %s %s %s %s\n", data.id, data.NIK, data.nama, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
            }
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



