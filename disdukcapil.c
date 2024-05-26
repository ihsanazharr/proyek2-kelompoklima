#include "disdukcapil.h"
#include "ihsan/ihsan.c"
#include "firly/firly.c"
#include "maul/maul.c"
#include "rindi/rindi.c"
#include "ilham/ilham.c"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

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
    printf("            /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$                     \n");
    gotoxy(30, 5);
    printf("           /$$__  $$| $$  /$$/ /$$__  $$|_  $$_/                     \n");
    gotoxy(30, 6);
    printf("          | $$  \ $$| $$ /$$/ | $$  \__/  | $$          \n");
    gotoxy(30, 7);
    printf("          | $$$$$$$$| $$$$$/  |  $$$$$$   | $$                       \n");
    gotoxy(30, 8);
    printf("          | $$__  $$| $$  $$   \\____ $$  | $$                       \n");
    gotoxy(30, 9);
    printf("          | $$  | $$| $$\\  $$  /$$\\ $$  | $$                       \n");
    gotoxy(30, 10);
    printf("          | $$  | $$| $$ \\  $$ |$$$$$$/ /$$$$$$                    \n");
    gotoxy(30, 11);
    printf("          |__/  |__/|__/  \\__/ \\______/ |______/                    \n");
    gotoxy(30, 12); 
    printf("  SISTEM ADMINISTRASI KEPENDUDUKAN DAN PENCATATAN SIPIL    \n\n");
    gotoxy(30, 13);
    printf("               ===========================                   \n\n");
    gotoxy(30, 14);
    printf("                1. MASUK                             \n");
    gotoxy(30, 15);
    printf("                2. KELUAR                            \n");

    gotoxy(30, 16);
    printf("          PILIHAN	: ");
    scanf("%d", &input);
    scanf("%c", &terminate);

    switch (input)
    {
    case 1:
        loginAdmin();
        break;

    case 2:
        exit(1);
        break;
    }
}

void addAdmin()
{
    // Membungkus password & username menjadi struct
    Admin admin;
    int usernameExists;

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    do {
        // Input username
        printf("Masukkan Username : ");
        fgets(admin.username, sizeof(admin.username), stdin);
        admin.username[strcspn(admin.username, "\n")] = '\0'; // Remove newline character from input

        // Check if username already exists
        usernameExists = checkUsernameExists(admin.username);
        if (usernameExists)
        {
            printf("Username sudah ada. Silakan masukkan username yang lain.\n");
        }
    } while (usernameExists);

    // input password
    printf("Masukkan Password : ");
    fgets(admin.password, sizeof(admin.password), stdin);
    // Remove newline character from input
    admin.password[strcspn(admin.password, "\n")] = '\0';

    // proses enkripsi sebelum masuk file
    generateAngkaGeser(&admin.jumlahGeser);              // Sebelum disimpan ke file, generate key terlebih dahulu untuk disimpan ke struct
    enkripsiPassword(admin.password, admin.jumlahGeser); // Enkripsi password dengan parameter input password dan jumlahgeser sebelumnya
    simpanFileAdmin(admin);

    // Memberikan keterangan bahwa penambahan admin berhasil
    printf("Admin dengan username %s berhasil ditambahkan.\n", admin.username);
}

int checkUsernameExists(const char* username)
{
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, no usernames to check
    }

    char existingUsername[50];
    char existingPassword[50];
    int existingJumlahGeser;

    while (fscanf(file, "%s %s %d", existingUsername, existingPassword, &existingJumlahGeser) != EOF)
    {
        if (strcmp(existingUsername, username) == 0)
        {
            fclose(file);
            return 1; // Username exists
        }
    }

    fclose(file);
    return 0; // Username does not exist
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
            system("cls");
            printf("Username atau Password Salah, silakan coba lagi.\n");
            Sleep(2000);
            rewind(file);
        }
    }
}

void menuAwal()
{
    int pilihan;
    DataProvinsi provinsi;

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
        printf("6. Statistik Penduduk\n");
        printf("7. Tampilkan History\n");
        printf("8. Tambah Kota\n");
        printf("9. Lihat Kota\n");
        printf("10. Kejadian Penting\n");
        printf("11. Tampilkan Tree\n");
        printf("12. Tambah KK\n"); 
        printf("13. Cari Kartu Keluarga\n");  
        printf("0. Keluar\n");
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
            if (provinsi.firstChild == NULL)
            {
                printf("Tidak ada kota yang tersedia. Tambahkan kota terlebih dahulu.\n");
                break;
            }
            DataKota *kota = provinsi.firstChild;
            addPenduduk(kota);
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
            menu(); // Menampilkan history saat opsi 6 dipilih
            break;
        case 7:
            tampilkanHistory(); // Menampilkan history saat opsi 7 dipilih
            break;
        case 8:
            provinsi.firstChild = NULL;
            tambahKota(&provinsi); // struktur tree
            break;
        case 9:
            showKota();
            system("cls");
            break;
        case 10:
            kejadianPenting();
            system("cls");
            break;
        case 11:
            tampilkanTree();
            system("cls");
            break;
        case 12:
            tambahKK(&kota);  // Panggil fungsi addkk saat opsi 12 dipilih
            system("cls");
            break;
        case 13:
            menuCariKartuKeluarga(&provinsi);
            system("cls");
            break;
        case 0:
            pilihanMenuAwal();
            system("cls");
            break;
        default:
            printf("Masukkan tidak valid, coba kembali.\n");
            break;
        }
    } while (pilihan != 0);
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
void addPenduduk(DataKota *kota)
{
    DataPenduduk *dat = (DataPenduduk *)malloc(sizeof(DataPenduduk));
    FILE *file;
    int cek = 0;
    char fnama[100];
    int count = 0, a;
    char kkLine[100], kotaLine[100];
    int kkTerdaftar = 0, kotaTerdaftar = 0;
    int dummyId;  // Untuk membaca ID dari file

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

    system("cls");
    printf("=================================================\n");
    printf("\tINPUT DATA PENDUDUK\n");
    printf("=================================================\n");
    dat->id = count;

    printf("NIK: ");
    scanf("%s", dat->NIK);

    // Cek validitas No. KK
    fflush(stdin);
    printf("No. KK: ");
    scanf("%s", dat->noKK);

    // Enkripsi noKK sebelum memeriksa keberadaannya dalam file
    enkripsiInteger(dat->noKK, keyInt);

    // Cek validitas No. KK
    file = fopen("dataKK.txt", "r");
    if (file != NULL)
    {
        while (fgets(kkLine, sizeof(kkLine), file) != NULL)
        {
            sscanf(kkLine, "%d %s", &dummyId, fnama); // Baca ID dan noKK
            if (strcmp(dat->noKK, fnama) == 0)
            {
                kkTerdaftar = 1;
                break;
            }
        }
        fclose(file);
    }

    if (!kkTerdaftar)
    {
        printf("No. KK tidak terdaftar\n");
        free(dat);
        menuAwal();
        return;
    }

    fflush(stdin);
    printf("Nama Lengkap: ");
    fgets(dat->nama, sizeof(dat->nama), stdin);
    dat->nama[strcspn(dat->nama, "\n")] = '\0';
    for (int i = 0; dat->nama[i]; i++)
    {
        if (dat->nama[i] == ' ')
        {
            dat->nama[i] = '_';
        }
    }

    fflush(stdin);
    printf("Tanggal Lahir(dd/mm/yyyy): ");
    scanf("%s", dat->tanggalLahir);

    fflush(stdin);
    printf("Jenis Kelamin (L/P): ");
    scanf(" %c", &dat->jk);
    fflush(stdin);
    printf("Alamat: ");
    fgets(dat->alamat, sizeof(dat->alamat), stdin);
    dat->alamat[strcspn(dat->alamat, "\n")] = '\0';
    for (int i = 0; dat->alamat[i]; i++)
    {
        if (dat->alamat[i] == ' ')
        {
            dat->alamat[i] = '_';
        }
    }
    fflush(stdin);
    printf("Tempat Lahir: ");
    fgets(dat->tempat_lahir, sizeof(dat->tempat_lahir), stdin);
    dat->tempat_lahir[strcspn(dat->tempat_lahir, "\n")] = '\0';
    for (int i = 0; dat->tempat_lahir[i]; i++)
    {
        if (dat->tempat_lahir[i] == ' ')
        {
            dat->tempat_lahir[i] = '_';
        }
    }
    fflush(stdin);
    printf("Agama: ");
    fgets(dat->agama, sizeof(dat->agama), stdin);
    dat->agama[strcspn(dat->agama, "\n")] = '\0';
    for (int i = 0; dat->agama[i]; i++)
    {
        if (dat->agama[i] == ' ')
        {
            dat->agama[i] = '_';
        }
    }
    fflush(stdin);
    printf("Status: ");
    fgets(dat->status, sizeof(dat->status), stdin);
    dat->status[strcspn(dat->status, "\n")] = '\0';
    for (int i = 0; dat->status[i]; i++)
    {
        if (dat->status[i] == ' ')
        {
            dat->status[i] = '_';
        }
    }
       fflush(stdin);
    printf("Kota: ");
    fgets(dat->namaKota, sizeof(dat->namaKota), stdin);
    dat->namaKota[strcspn(dat->namaKota, "\n")] = '\0';
    for (int i = 0; dat->namaKota[i]; i++)
    {
        if (dat->namaKota[i] == ' ')
        {
            dat->namaKota[i] = '_';
        }
    }

    // Enkripsi namaKota sebelum memeriksa keberadaannya dalam file
    enkripsiHuruf(dat->namaKota, keyStr);

    // Cek validitas Kota
    file = fopen("dataKota.txt", "r");
    if (file != NULL)
    {
        while (fgets(kotaLine, sizeof(kotaLine), file) != NULL)
        {
            sscanf(kotaLine, "%d %s", &dummyId, fnama); // Baca ID dan namaKota
            if (strcmp(dat->namaKota, fnama) == 0)
            {
                kotaTerdaftar = 1;
                break;
            }
        }
        fclose(file);
    }

    if (!kotaTerdaftar)
    {
        printf("Kota tidak terdaftar\n");
        free(dat);
        menuAwal();
        return;
    }

    printf("=================================================\n");

    enkripsiInteger(dat->NIK, keyInt);
    file = fopen("dataPenduduk.txt", "a");
    while (fscanf(file, "%s", fnama) != EOF)
    {
        if (strcmp(dat->NIK, fnama) == 0)
        {
            cek = 1;
            break;
        }
    }
    enkripsiInteger(dat->noKK, keyInt);
    file = fopen("dataPenduduk.txt", "a");
    while (fscanf(file, "%s", fnama) != EOF)
    {
        if (strcmp(dat->noKK, fnama) == 0)
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
        enkripsiHuruf(dat->alamat, keyStr);
        fprintf(file, "%d %s %s %s %s %c %s %s %s %s %s\n", dat->id, dat->NIK, dat->noKK, dat->nama, dat->tanggalLahir, dat->jk, dat->alamat, dat->tempat_lahir, dat->agama, dat->status, dat->namaKota);
        fclose(file);
        printf("Data berhasil tersimpan\n");

        // Tambahkan dat sebagai anak dari kota
        dat->parent = kota;
        dat->nextSibling = kota->firstChild;
        kota->firstChild = dat;

        // Catat aktivitas pengguna
        catatAktivitas("Menambahkan data penduduk", dat->NIK);
    }

    // Pilihan untuk menambah data lagi
    char pilihanUser;
    printf("\nApakah Anda ingin menambah data lagi? (Y/N): ");
    scanf(" %c", &pilihanUser);
    if (pilihanUser == 'Y' || pilihanUser == 'y')
    {
        addPenduduk(kota); // Rekursif untuk menambah data lagi jika dipilih
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
    int n = 0;

    file = fopen("dataPenduduk.txt", "r");
    temp = fopen("tempDataPenduduk.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error membuka/membuat file!");
        exit(1);
    }

    displayDecryptedNikList();
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

    if (found)
    {
        printf("Data dengan NIK %s ditemukan.\n", userInputCpy);
        printf("Apakah Anda yakin ingin menghapus data ini? [Y/N]: ");
        scanf(" %c", &userChoose);
        if (userChoose == 'Y' || userChoose == 'y')
        {
            printf("Data dengan NIK %s telah dihapus.\n", userInputCpy);
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
        else
        {
            printf("Penghapusan data dibatalkan.\n");
            n = 1;
            Sleep(2000);
        }
    }

    if (!found)
    {
        fclose(file);
        fclose(temp);
        remove("tempDataPenduduk.txt");
        printf("Data tidak ditemukan!!!");
        Sleep(2000);
        return;
    }

    if (n == 1)
    {
        fclose(file);
        fclose(temp);
        remove("tempDataPenduduk.txt");
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
    system("cls"); // Clear screen
    char NIK[50];
    char userChoice;

    displayDecryptedNikList();
    printf("Masukkan NIK penduduk yang akan diedit: ");
    scanf("%s", NIK);
    fflush(stdin);
    enkripsiInteger(NIK, keyInt);

    FILE *file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return;
    }

    DataPenduduk data;
    int found = 0;

    // Membaca dan mencari data berdasarkan NIK
    FILE *tempFile = fopen("tempDataPenduduk.txt", "w");
    if (tempFile == NULL)
    {
        printf("File sementara tidak dapat dibuat\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
    {
        if (strcmp(data.NIK, NIK) == 0)
        {
            printf("Data ditemukan. Silakan masukkan data yang baru.\n");

            // Input data baru
            printf("Nama Lengkap: ");
            fgets(data.nama, sizeof(data.nama), stdin);
            data.nama[strcspn(data.nama, "\n")] = '\0'; // Remove newline character if any
            for (int i = 0; data.nama[i]; i++)
            { // Replace spaces with underscores
                if (data.nama[i] == ' ')
                {
                    data.nama[i] = '_';
                }
            }
            fflush(stdin);
            printf("Tanggal Lahir(dd/mm/yyyy): ");
            scanf("%s", data.tanggalLahir);
            fflush(stdin);
            printf("Jenis Kelamin (L/P): ");
            scanf(" %c", &data.jk);
            fflush(stdin);
            printf("Alamat: ");
            fgets(data.alamat, sizeof(data.alamat), stdin);
            data.alamat[strcspn(data.alamat, "\n")] = '\0'; // Remove newline character if any
            enkripsiHuruf(data.alamat, keyInt);             // Encrypting the address
            fflush(stdin);
            printf("Tempat Lahir: ");
            fgets(data.tempat_lahir, sizeof(data.tempat_lahir), stdin);
            data.tempat_lahir[strcspn(data.tempat_lahir, "\n")] = '\0'; // Remove newline character if any
            for (int i = 0; data.tempat_lahir[i]; i++)
            { // Replace spaces with underscores
                if (data.tempat_lahir[i] == ' ')
                {
                    data.tempat_lahir[i] = '_';
                }
            }
            fflush(stdin);
            printf("Agama: ");
            fgets(data.agama, sizeof(data.agama), stdin);
            data.agama[strcspn(data.agama, "\n")] = '\0'; // Remove newline character if any
            for (int i = 0; data.agama[i]; i++)
            { // Replace spaces with underscores
                if (data.agama[i] == ' ')
                {
                    data.agama[i] = '_';
                }
            }
            fflush(stdin);
            printf("Status: ");
            fgets(data.status, sizeof(data.status), stdin);
            data.status[strcspn(data.status, "\n")] = '\0'; // Remove newline character if any
            for (int i = 0; data.status[i]; i++)
            { // Replace spaces with underscores
                if (data.status[i] == ' ')
                {
                    data.status[i] = '_';
                }
            }
            fflush(stdin);

            fprintf(tempFile, "%d %s %s %s %s %c %s %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota);
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%d %s %s %s %s %c %s %s %s %s %s\n", data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, data.jk, data.alamat, data.tempat_lahir, data.agama, data.status,data.namaKota);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove("dataPenduduk.txt");
    rename("tempDataPenduduk.txt", "dataPenduduk.txt");

    if (!found)
    {
        printf("Data dengan NIK tersebut tidak ditemukan.\n");
    }
    else
    {
        printf("Data berhasil diubah\n"); // Pesan ketika berhasil mengedit data

        // Catat aktivitas pengguna
        catatAktivitas("Mengedit data penduduk", data.NIK);
    }

    printf("\nApakah Anda ingin mengedit data lagi? (Y/N): ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y')
    {
        editPenduduk(); // Rekursif untuk mengedit data lagi jika dipilih
    }
}

void showPenduduk()
{
    system("cls"); // Clear screen

    FILE *file;
    DataPenduduk data;
    DataPenduduk penduduk[100]; // Assuming a maximum of 100 records

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return;
    }

    int count = 0;
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF)
    {
        dekripsiHuruf(data.alamat, keyStr);
        dekripsiInteger(data.NIK, keyInt);
        dekripsiInteger(data.noKK, keyInt);
        penduduk[count++] = data;
    }

    fclose(file);

    if (count == 0)
    {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }

    // Sorting
    bubbleSort(penduduk, count);

    printf("=============================================================================================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status", "No. KK", "Tanggal Lahir");
    printf("=============================================================================================================================================================================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", penduduk[i].id, penduduk[i].NIK, penduduk[i].nama, penduduk[i].jk, penduduk[i].alamat, penduduk[i].tempat_lahir, penduduk[i].agama, penduduk[i].status, penduduk[i].noKK, penduduk[i].tanggalLahir);
    }

    printf("=============================================================================================================================================================================================\n");

    // Meminta pengguna untuk mencari data berdasarkan nama atau kembali ke menu
    char userChoice;
    printf("\nApakah Anda ingin mencari data berdasarkan nama? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        searchByName(penduduk, count);
    } else {
        printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
        scanf(" %c", &userChoice);
        if (userChoice == 'Y' || userChoice == 'y') {
            menuAwal();
        } else {
            showPenduduk();
        }
    }
}

void searchByName(DataPenduduk penduduk[], int count)
{
    char searchName[50];
    printf("Masukkan nama (huruf yang diinginkan): ");
    scanf("%s", searchName);

    printf("=============================================================================================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-3s | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "NIK", "Nama Lengkap", "JK", "Alamat", "Tempat Lahir", "Agama", "Status", "No. KK", "Tanggal Lahir");
    printf("=============================================================================================================================================================================================\n");

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        char result[100];                                        // Menyimpan hasil pencarian nama
        strcasestr_custom(penduduk[i].nama, searchName, result); // Pencarian tanpa case sensitive
        if (result[0] != '\0')
        {
            printf("| %-5d | %-15s | %-20s | %-3c | %-30s | %-20s | %-15s | %-15s | %-15s | %-15s |\n", penduduk[i].id, penduduk[i].NIK, penduduk[i].nama, penduduk[i].jk, penduduk[i].alamat, penduduk[i].tempat_lahir, penduduk[i].agama, penduduk[i].status, penduduk[i].noKK, penduduk[i].tanggalLahir);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Data dengan nama yang mengandung \"%s\" tidak ditemukan.\n", searchName);
    }

    // Meminta pengguna untuk kembali ke menu atau ke pencarian nama
    char userChoice;
    printf("\nApakah Anda ingin mencari data lagi? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        searchByName(penduduk, count);
    } else {
        printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
        scanf(" %c", &userChoice);
        if (userChoice == 'Y' || userChoice == 'y') {
            menuAwal();
        } else {
            showPenduduk();
        }
    }
}

// Prosedur pencarian yang tidak case-sensitive
void strcasestr_custom(const char *haystack, const char *needle, char *result)
{
    if (*needle == '\0')
    {
        strcpy(result, haystack);
        return;
    }

    const char *p1 = haystack;
    while (*p1 != '\0')
    {
        const char *p1_copy = p1;
        const char *p2 = needle;

        while (tolower((unsigned char)*p1_copy) == tolower((unsigned char)*p2))
        {
            ++p1_copy;
            ++p2;
            if (*p2 == '\0')
            {
                strcpy(result, p1);
                return;
            }
        }
        ++p1;
    }
    strcpy(result, "");
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

void tampilkanHistory()
{
    system("cls"); // Clear screen

    FILE *file = fopen("history.txt", "r");
    if (file == NULL)
    {
        printf("File tidak dapat dibuka\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    printf("=================================================\n");
    printf("\tHISTORY AKTIVITAS\n");
    printf("=================================================\n");

    // Membaca dan menampilkan setiap baris dari file history.txt
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    printf("=================================================\n");

    fclose(file);

    // Meminta pengguna untuk kembali ke menu
    char userChoice;
    printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        menuAwal();
    } else {
        tampilkanHistory();
    }
}

void bubbleSort(DataPenduduk arr[], int n)
{
    int i, j;
    DataPenduduk temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j].nama, arr[j + 1].nama) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}