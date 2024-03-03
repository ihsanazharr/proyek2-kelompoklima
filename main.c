#include "disdukcapil.h"
#include <stdio.h>

int main()
{
    int pilihan;

    do
    {
        printf("Menu:\n");
        printf("1. Register Admin\n");
        printf("2. Login Admin\n");
        printf("3. Add Penduduk\n");
        printf("4. Edit Penduduk\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            addAdmin();
            break;
        case 2:
            loginAdmin();
            break;
        case 3:
            addPenduduk();
            break;
        case 4:
            // editPenduduk();
            break;
        case 5:
            printf("Program Keluar");
            break;
        default:
            printf("Masukkan tidak valid, coba kembali.\n");
            break;
        }
    } while (pilihan != 4);

    return 0;
}
