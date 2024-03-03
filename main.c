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
        printf("5. Delete Data Penduduk\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            addAdmin();
            system("cls");
            break;
        case 2:
            loginAdmin();
            system("cls");
            break;
        case 3:
            addPenduduk();
            system("cls");
            break;
        case 4:
            editPenduduk();
            // system("cls");
            break;
        case 5:
            deleteData();
            system("cls");
            break;
        case 6:
            printf("Program Keluar");
            system("cls");
            break;
        default:
            printf("Masukkan tidak valid, coba kembali.\n");
            break;
        }
    } while (pilihan != 5);

    return 0;
}
