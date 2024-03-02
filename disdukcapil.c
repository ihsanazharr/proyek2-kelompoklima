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
                password[i] = ((password[i] - 'A') - jumlahgeser + 26) % 26 + 'A';
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
                password[i] = ((password[i] - 'a') - jumlahgeser + 26) % 26 + 'a';
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

        for (int i = 0; i < 5; i++)
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