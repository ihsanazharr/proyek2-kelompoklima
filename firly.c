#include "disdukcapil.h"
// int keyStr = 18; // Tidak boleh >= 26
// int keyInt = 7;  // Tidak boleh >= 10

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
    printf("=================================================\n");
    printf("\tDaftar NIK Penduduk (Terdekripsi)\n");
    printf("=================================================\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Menggunakan sscanf untuk membaca data dari satu baris
        sscanf(line, "%d %s %s %[^\n]s %c %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status);
        char decryptedNoKK[18];
        strcpy(decryptedNoKK, data.noKK);
        dekripsiInteger(decryptedNoKK, 7);
        printf("%s (Normal: %s)\n", decryptedNoKK, data.noKK);
    }
    printf("=================================================\n");

    fclose(file);
}

void kejadianPenting(){
    system("cls");
    int input;
    do {
        printf("Silakan pilih kejadian penting:\n\n");
        printf("1. Pernikahan\n");
        printf("2. Kelahiran\n");
        printf("3. Kematian");

        fflush(stdin);
        scanf("%d", &input);
        // switch (input){
        //     case 1:
        //         // Terjadi Pernikahan

        //     case 2:
        //         // Terjadi Kematian

        //     case 3:
        //         // Terjadi Kematian
        //     }

    } while (input != '0');

}

bool searchKK(char noKK[50]){
    FILE *file;
    DataPenduduk data;
    bool found = false;
    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL){
        printf("File tidak dapat dibuka\n");
        return false;
    }
    rewind(file);
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
    return found;
}

void Pernikahan()
{
    system("cls");
    FILE *file, *temp;
    DataPenduduk data;
    char userInput1[50];
    char userInput2[20];
    char userInputCpy1[20];
    char userInputCpy2[20];
    char userChoose;
    bool validation;
    bool found = false;
    int n = 0;

    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("tempDataPenduduk.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    while (!found){
	    displayDecryptedNoKKList();
        printf("Masukkan No.KK kedua pasangan\n");
        printf("No KK Pertama: ");
        fflush(stdin);
        scanf("%s", userInput1);
        strcpy(userInputCpy1, userInput1);
        enkripsiInteger(userInputCpy1, 7);
        if (searchKK(userInputCpy1) == false){
            printf("No KK tersebut tidak ditemukan\n");
            continue;
        }
        printf("No KK Kedua: ");
        fflush(stdin);
        scanf("%s", userInput2);
        strcpy(userInputCpy2, userInput2);
        enkripsiInteger(userInputCpy2, 7);
        if (searchKK(userInputCpy2) == false){
            printf("No KK tersebut tidak ditemukan\n");
            continue;
        }
        strcpy(userInputCpy1, userInput1);
        strcpy(userInputCpy2, userInput2);
        enkripsiInteger(userInput1, 7);
        enkripsiInteger(userInput2, 7);
        found = true;
    }

    found = false;
    while (!found){
        displayDecryptedNikList();

    }




//     if (found){
//         printf("Data dengan NIK %s ditemukan.\n", userInputCpy);
//         printf("Apakah Anda yakin ingin menghapus data ini? [Y/N]: ");
//         scanf(" %c", &userChoose);
//         if (userChoose == 'Y' || userChoose == 'y') {
//             printf("Data dengan NIK %s telah dihapus.\n", userInputCpy);
//             Sleep(2000);
//             rewind(file);
//             char line[1000];
//             int n = 0;
//             while (fgets(line, sizeof(line), file) != NULL)
//             {
//                 if (n == i)
//                 {
//                     n++;
//                     continue;
//                 }
//                 fputs(line, temp);
//                 n++;
//             }     
//             catatAktivitas("Menghapus data penduduk", userInputCpy);
//         } else {
//             printf("Penghapusan data dibatalkan.\n");
//             n = 1;
//             Sleep(2000);
//         }
//     }

//     if (!found){
//         fclose(file);
//         fclose(temp);
//         remove("tempDataPenduduk.txt");
//         printf("Data tidak ditemukan!!!");
//         Sleep(2000);
//         return;
//     }
    
//     if (n == 1){
//         fclose(file);
//         fclose(temp);
//         remove("tempDataPenduduk.txt");
//         Sleep(2000);
//         return;
//     }

//     fclose(file);
//     fclose(temp);
//     remove("dataPenduduk.txt");
//     rename("tempDataPenduduk.txt", "dataPenduduk.txt");
 }