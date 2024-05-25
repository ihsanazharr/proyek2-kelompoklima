#include "../disdukcapil.h"

typedef struct KeluargaTreeNode {
    char noKK[20];
    struct KeluargaTreeNode *nextSibling;
    struct PendudukTreeNode *firstChild;
} DataKeluarga;

typedef struct PendudukTreeNode {
    DataPenduduk data;
    struct PendudukTreeNode *nextSibling;
} DataPendudukNode;

extern int keyStr;
extern int keyInt;

// Fungsi untuk membuat node baru
DataPendudukNode* createPendudukNode(DataPenduduk data) {
    DataPendudukNode *newNode = (DataPendudukNode*)malloc(sizeof(DataPendudukNode));
    newNode->data = data;
    newNode->nextSibling = NULL;
    return newNode;
}

DataKeluarga* createKeluargaNode(char *noKK) {
    DataKeluarga *newNode = (DataKeluarga*)malloc(sizeof(DataKeluarga));
    strcpy(newNode->noKK, noKK);
    newNode->nextSibling = NULL;
    newNode->firstChild = NULL;
    return newNode;
}

DataKota* createKotaNode(char *namaKota) {
    DataKota *newNode = (DataKota*)malloc(sizeof(DataKota));
    strcpy(newNode->namaKota, namaKota);
    newNode->nextSibling = NULL;
    newNode->firstChild = NULL;
    return newNode;
}

// Fungsi untuk menambahkan kota ke dalam tree
DataKota* addKota(DataKota *root, char *namaKota) {
    DataKota *newNode = createKotaNode(namaKota);

    if (root == NULL) {
        return newNode;
    }

    DataKota *curr = root;
    while (curr->nextSibling != NULL) {
        curr = curr->nextSibling;
    }
    curr->nextSibling = newNode;
    return root;
}

// Fungsi untuk menambahkan KK ke dalam node kota
DataKeluarga* addKK(DataKota *kotaNode, char *noKK) {
    DataKeluarga *newNode = createKeluargaNode(noKK);

    if (kotaNode->firstChild == NULL) {
        kotaNode->firstChild = newNode;
    } else {
        DataKeluarga *curr = kotaNode->firstChild;
        while (curr->nextSibling != NULL) {
            curr = curr->nextSibling;
        }
        curr->nextSibling = newNode;
    }
    return newNode;
}

// Fungsi untuk menambahkan penduduk ke node KK
void tambahPenduduk(DataKeluarga *kkNode, DataPenduduk data) {
    DataPendudukNode *newNode = createPendudukNode(data);

    if (kkNode->firstChild == NULL) {
        kkNode->firstChild = newNode;
    } else {
        DataPendudukNode *curr = kkNode->firstChild;
        while (curr->nextSibling != NULL) {
            curr = curr->nextSibling;
        }
        curr->nextSibling = newNode;
    }
}

// Fungsi untuk menampilkan tree dengan hierarki yang benar
void printTree(DataProvinsi *root, int level) {
    if (root == NULL) {
        return;
    }

    printf("|- Provinsi: %s\n", root->namaProvinsi);

    DataKota *kotaNode = root->firstChild;
    while (kotaNode != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("|- Kota: %s\n", kotaNode->namaKota);

        DataKeluarga *kkNode = kotaNode->firstChild;
        while (kkNode != NULL) {
            for (int i = 0; i < level + 1; i++) {
                printf("  ");
            }
            printf("|- KK: %s\n", kkNode->noKK);

            DataPendudukNode *pendudukNode = kkNode->firstChild;
            while (pendudukNode != NULL) {
                for (int i = 0; i < level + 2; i++) {
                    printf("  ");
                }
                printf("|- NIK: %s, Nama: %s\n", pendudukNode->data.NIK, pendudukNode->data.nama);
                pendudukNode = pendudukNode->nextSibling;
            }
            kkNode = kkNode->nextSibling;
        }
        kotaNode = kotaNode->nextSibling;
    }
}

// Fungsi utama untuk menampilkan struktur pohon
void tampilkanTree() {
    system("cls"); // Clear screen

    FILE *file;
    DataPenduduk data;
    DataProvinsi *root = (DataProvinsi*)malloc(sizeof(DataProvinsi));
    strcpy(root->namaProvinsi, "Jawa Barat");
    root->firstChild = NULL;

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }
    
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF) {
        // Dekripsi data
        dekripsiHuruf(data.alamat, keyStr);
        dekripsiInteger(data.NIK, keyInt);
        dekripsiInteger(data.noKK, 0);
        dekripsiHuruf(data.namaKota, keyStr);

        // Cari atau tambah node kota
        DataKota *kotaNode = root->firstChild;
        while (kotaNode != NULL && strcmp(kotaNode->namaKota, data.namaKota) != 0) {
            kotaNode = kotaNode->nextSibling;
        }
        if (kotaNode == NULL) {
            kotaNode = addKota(root->firstChild, data.namaKota);
            if (root->firstChild == NULL) {
                root->firstChild = kotaNode;
            }
        }

        // Cari atau tambah node KK
        DataKeluarga *kkNode = kotaNode->firstChild;
        while (kkNode != NULL && strcmp(kkNode->noKK, data.noKK) != 0) {
            kkNode = kkNode->nextSibling;
        }
        if (kkNode == NULL) {
            kkNode = addKK(kotaNode, data.noKK);
        }

        // Tambah penduduk ke node KK
        tambahPenduduk(kkNode, data);
    }

    fclose(file);

    if (root == NULL) {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }

    printf("Struktur Pohon Kartu Keluarga dan Penduduk Provinsi Jawa Barat:\n");
    printTree(root, 1);

    // Hapus bagian ini jika tidak ingin menunggu input dari pengguna
    char userChoice;
    printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        menuAwal();
    } else {
        tampilkanTree();
    }
}
