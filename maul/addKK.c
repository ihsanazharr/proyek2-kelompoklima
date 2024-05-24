#include "../disdukcapil.h"

// Fungsi untuk memilih kota dan menambahkan keluarga baru (KK)
void tambahKK(DataProvinsi* provinsi) {
    int idKota;
    DataKota* selectedKota = NULL;

    printf("Masukkan ID Kota: ");
    scanf("%d", &idKota);

    selectedKota = cariKotaById(provinsi, idKota);
    if (selectedKota == NULL) {
        printf("Kota tidak ditemukan!\n");
        return;
    }

    // Buat node keluarga baru
    DataPenduduk* newKK = (DataPenduduk*)malloc(sizeof(DataPenduduk));

    printf("Masukkan No KK: ");
    scanf("%s", newKK->noKK);

    newKK->firstChild = NULL;
    newKK->nextSibling = NULL;
    newKK->parent = selectedKota;

    // Tambahkan anggota ke keluarga baru
    tambahAnggotaKK(newKK);

    // Hubungkan keluarga baru ke daftar keluarga di kota
    newKK->nextSibling = selectedKota->firstChild;
    selectedKota->firstChild = newKK;

    // Simpan data keluarga ke file
    simpanKKkeFile(newKK);

    printf("Kartu Keluarga berhasil ditambahkan.\n");
}

// Fungsi untuk menambahkan anggota ke keluarga (KK)
void tambahAnggotaKK(DataPenduduk* kk) {
    int jumlahAnggota;
    printf("Masukkan jumlah anggota keluarga: ");
    scanf("%d", &jumlahAnggota);

    DataPenduduk* lastMember = NULL;

    for (int i = 0; i < jumlahAnggota; i++) {
        DataPenduduk* anggotaBaru = (DataPenduduk*)malloc(sizeof(DataPenduduk));

        printf("Masukkan NIK: ");
        scanf("%s", anggotaBaru->NIK);

        printf("Masukkan Nama: ");
        scanf("%s", anggotaBaru->nama);

        printf("Masukkan Jenis Kelamin (L/P): ");
        scanf(" %c", &anggotaBaru->jk);

        printf("Masukkan Alamat: ");
        scanf("%s", anggotaBaru->alamat);

        printf("Masukkan Tempat Lahir: ");
        scanf("%s", anggotaBaru->tempat_lahir);

        printf("Masukkan Agama: ");
        scanf("%s", anggotaBaru->agama);

        printf("Masukkan Status: ");
        scanf("%s", anggotaBaru->status);

        printf("Masukkan Tanggal Lahir (DD/MM/YYYY): ");
        scanf("%s", anggotaBaru->tanggalLahir);

        anggotaBaru->parent = kk;
        anggotaBaru->firstChild = NULL;
        anggotaBaru->nextSibling = NULL;

        if (kk->firstChild == NULL) {
            kk->firstChild = anggotaBaru;
        } else {
            lastMember->nextSibling = anggotaBaru;
        }
        lastMember = anggotaBaru;

        // Enkripsi data sensitif
        enkripsiHuruf(anggotaBaru->NIK, 5);
        enkripsiHuruf(anggotaBaru->nama, 5);
        enkripsiHuruf(anggotaBaru->alamat, 5);
        enkripsiHuruf(anggotaBaru->tempat_lahir, 5);
        enkripsiHuruf(anggotaBaru->agama, 5);
        enkripsiHuruf(anggotaBaru->status, 5);
        enkripsiHuruf(anggotaBaru->tanggalLahir, 5);
    }

    printf("Anggota keluarga berhasil ditambahkan.\n");
}

// Fungsi untuk menyimpan data KK ke file
void simpanKKkeFile(DataPenduduk* kk) {
    FILE* file = fopen("dataKK.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "No KK: %s\n", kk->noKK);
    fprintf(file, "Anggota Keluarga:\n");
    simpanAnggotakeFile(kk->firstChild, file);
    fprintf(file, "\n");

    fclose(file);
}

// Fungsi untuk menyimpan data anggota keluarga ke file
void simpanAnggotakeFile(DataPenduduk* anggota, FILE* file) {
    while (anggota != NULL) {
        fprintf(file, "NIK: %s, Nama: %s, JK: %c, Alamat: %s, Tempat Lahir: %s, Agama: %s, Status: %s, Tanggal Lahir: %s\n",
                anggota->NIK, anggota->nama, anggota->jk, anggota->alamat, anggota->tempat_lahir, anggota->agama, anggota->status, anggota->tanggalLahir);
        anggota = anggota->nextSibling;
    }
}

// Fungsi bantu untuk menemukan node kota berdasarkan ID
DataKota* cariKotaById(DataProvinsi* root, int id) {
    DataProvinsi* currentProvinsi = root;
    while (currentProvinsi != NULL) {
        DataKota* currentKota = currentProvinsi->firstChild;
        while (currentKota != NULL) {
            if (currentKota->id == id) {
                return currentKota;
            }
            currentKota = currentKota->nextSibling;
        }
        currentProvinsi = currentProvinsi->nextSibling;
    }
    return NULL;
}
