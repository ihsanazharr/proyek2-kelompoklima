#include "disdukcapil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void registerAdmin(){
    Admin admin;
    printf("Masukkan nama pengguna : ");
    scanf("%s", admin.username);

    printf("Masukkan password : ");
    scanf("%s", admin.password);

    angkaGeser(&admin.geser, &admin.arah);
    enkripsiPassword(admin.password, admin.geser);
    simpanAdmin(admin);

    printf("Admin berhadil didaftarkan");
}

void enkripsiPassword(char *password, int geser){
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = ((password[i] - 'A') + geser) % 26 + 'A';
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = ((password[i] - 'a') + geser) % 26 + 'a';
        }
    }
}

void angkaGeser(int *geser, char *arah){
    srand(time(NULL));
    *geser = rand() % 26 + 1;
    *arah = rand() % 2 == 0 ? 'L' : 'R';
}

void simpanAdmin(Admin admin){
    FILE *file = fopen("daftaradmin.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %d %c\n", admin.username, admin.password, admin.geser, admin.arah);
        fclose(file);
    } else {
        printf("Tidak dapat membuka file.\n");
    }
}