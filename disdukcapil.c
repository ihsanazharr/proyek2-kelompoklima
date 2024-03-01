#include "disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Procedure tambah admin
void addAdmin(){
    //membungkus password&username menjadi struct
    Admin admin;

    //input username
    printf("Masukkan username admin : ");
    scanf("%s", admin.username);

    //input password
    printf("Masukkan password admin : ");
    scanf("%s", admin.password);

    //proses enkripsi sebelum masuk ke file
    generateAngkaGeser(&admin.jumlahGeser, &admin.arahGeser);//Sebelum disimpan ke file, generate key terlebih dahulu untuk disimpan ke struct
    enkripsiPassword(admin.password, admin.jumlahGeser);//Enkripsi password dengan parameter input password dan jumlahgeser sebelumnya
    simpanFileAdmin(admin);//Menyimpan hasil username,password(enkripsi),jumlahgeser,arahgeser
}

//Function untuk generate kunci random & arah random
void generateAngkaGeser(int *jumlahgeser, char *arahgeser){
    //Inisialisasi seed/nilai acak berdasarkan waktu saat ini
    srand(time(NULL));
    //Menghasilkan nilai acak untuk pergeseran
    *jumlahgeser = rand() % 26 + 1;
    //Menghasilkan nilai acak untur arah kiri atau kanan
    *arahgeser = rand() % 2 == 0 ? 'L' : 'R';
}

//Proses enkripsi
void enkripsiPassword(char *password, int jumlahgeser){
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = ((password[i] - 'A') + jumlahgeser) % 26 + 'A';
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = ((password[i] - 'a') + jumlahgeser) % 26 + 'a';
        }
    }
}

void simpanFileAdmin(Admin admin){
    FILE *file = fopen("admin.txt", "a");//mode "a" untuk menambahkan ke file
    if (file == NULL){
        printf("Gagal membuka file.\n");
        exit(1);
    }

    fprintf(file, "%s %s %d %c\n", admin.username,admin.password,admin.jumlahGeser,admin.arahGeser);
    fclose(file); //menutup file
}