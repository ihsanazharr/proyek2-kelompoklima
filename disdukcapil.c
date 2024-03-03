#include "disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    int keyStr = 18; // Tidak boleh >= 26
    int keyInt = 7;  // Tidak boleh >= 10

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

// Implementasi fungsi editPenduduk
void editPenduduk()
{
    FILE *file;
    DataPenduduk dat;
    char targetNIK[18];
    char temp[50];
    int found = 0;

    printf("Masukkan NIK penduduk yang akan diedit: ");
    scanf("%s", targetNIK);

    // Proses dekripsi file sebelum pembacaan data
    dekripsiFilePenduduk();

    file = fopen("dataPenduduk.txt", "r+");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    while (fscanf(file, "%d %s %s %c %s %s %s %s",
                  &dat.id, dat.NIK, dat.nama, &dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status) != EOF)
    {
        // Proses dekripsi pada NIK untuk pencocokan
        dekripsiInteger(dat.NIK, 7);

        if (strcmp(targetNIK, dat.NIK) == 0)
        {
            printf("Data ditemukan. Masukkan perubahan:\n");
            printf("Nama Lengkap: ");
            scanf("%s", dat.nama);
            printf("Jenis Kelamin (L/P): ");
            scanf(" %c", &dat.jk);
            printf("Alamat: ");
            scanf("%s", dat.alamat);
            printf("Tempat Lahir: ");
            scanf("%s", dat.tempat_lahir);
            printf("Agama: ");
            scanf("%s", dat.agama);
            printf("Status: ");
            scanf("%s", dat.status);

            // Proses enkripsi NIK sebelum penyimpanan
            enkripsiInteger(dat.NIK, 7);

            // Posisi kursor dipindahkan ke awal data yang akan diubah
            fseek(file, -1 * (strlen(dat.NIK) + strlen(dat.nama) + 6), SEEK_CUR);

            // Menulis perubahan ke file
            fprintf(file, "%d %s %s %c %s %s %s %s",
                    dat.id, dat.NIK, dat.nama, dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Data dengan NIK %s tidak ditemukan.\n", targetNIK);
    }

    // Proses enkripsi file setelah penyimpanan
    enkripsiFilePenduduk();
}

// Fungsi untuk melakukan enkripsi pada seluruh data di file dataPenduduk.txt
void enkripsiFilePenduduk()
{
    FILE *fileInput, *fileOutput;
    DataPenduduk dat;

    fileInput = fopen("dataPenduduk.txt", "r");
    fileOutput = fopen("tempDataPenduduk.txt", "w");

    if (fileInput == NULL || fileOutput == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    while (fscanf(fileInput, "%d %s %s %c %s %s %s %s",
                  &dat.id, dat.NIK, dat.nama, &dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status) != EOF)
    {
        // Proses enkripsi pada NIK sebelum penyimpanan
        enkripsiInteger(dat.NIK, 7);

        fprintf(fileOutput, "%d %s %s %c %s %s %s %s\n",
                dat.id, dat.NIK, dat.nama, dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status);
    }

    fclose(fileInput);
    fclose(fileOutput);

    // Menghapus file asli dan mengganti dengan file yang telah dienkripsi
    remove("dataPenduduk.txt");
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");
}

// Fungsi untuk melakukan dekripsi pada seluruh data di file dataPenduduk.txt
void dekripsiFilePenduduk()
{
    FILE *fileInput, *fileOutput;
    DataPenduduk dat;

    fileInput = fopen("dataPenduduk.txt", "r");
    fileOutput = fopen("tempDataPenduduk.txt", "w");

    if (fileInput == NULL || fileOutput == NULL)
    {
        printf("File tidak dapat dibuka!");
        exit(1);
    }

    while (fscanf(fileInput, "%d %s %s %c %s %s %s %s",
                  &dat.id, dat.NIK, dat.nama, &dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status) != EOF)
    {
        // Proses dekripsi pada NIK sebelum pembacaan
        dekripsiInteger(dat.NIK, 7);

        fprintf(fileOutput, "%d %s %s %c %s %s %s %s\n",
                dat.id, dat.NIK, dat.nama, dat.jk, dat.alamat, dat.tempat_lahir, dat.agama, dat.status);
    }

    fclose(fileInput);
    fclose(fileOutput);

    // Menghapus file asli dan mengganti dengan file yang telah didekripsi
    remove("dataPenduduk.txt");
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");
}
