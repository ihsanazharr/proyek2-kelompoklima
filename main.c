#include "disdukcapil.h"
#include <stdio.h>

int main() {
    int pilihan;

    do {
        printf("Menu:\n");
        printf("1. Register Admin\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                addAdmin();
                break;
            case 2:
                printf("Program keluar\n");
                break;
            default:
                printf("Masukkan tidak valid, coba kembali.\n");
                break;
        }
    } while (pilihan != 2);

    return 0;
}
