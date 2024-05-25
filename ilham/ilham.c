#include "../disdukcapil.h"

typedef struct Node {
   DataPenduduk data;
   struct Node *parent;
   struct Node *child;
   struct Node *sibling;
} Node;

extern int keyStr;
extern int keyInt;

// Fungsi rekursif untuk menambahkan penduduk ke struktur tree
Node* tambahPenduduk(Node *root, DataPenduduk data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = root;

    if (root == NULL) {
        return newNode;
    }

    Node *curr = root;
    while (curr->sibling != NULL) {
        curr = curr->sibling;
    }
    curr->sibling = newNode;
    return root;
}

// Fungsi rekursif untuk mencetak pohon secara terstruktur
void printTree(Node *node, int level, char *lastPrintedKota, char *lastPrintedNoKK) {
    if (node == NULL) {
        return;
    }

    // Print nama kota jika node adalah node Kota dan berbeda dengan yang terakhir dicetak
    if (node->data.namaKota != NULL && strcmp(node->data.namaKota, lastPrintedKota) != 0) {
        char decryptedKota[50];
        strcpy(decryptedKota, node->data.namaKota);
        dekripsiHuruf(decryptedKota, keyStr); // Dekripsi nama kota
        printf("|- Kota: %s\n", decryptedKota);
        strcpy(lastPrintedKota, node->data.namaKota); // Update nama kota terakhir yang dicetak
    }

    // Print nomor KK jika node adalah node KK dan berbeda dengan yang terakhir dicetak
    if (node->data.noKK != NULL && strcmp(node->data.noKK, lastPrintedNoKK) != 0) {
        char decryptedNoKK[20];
        strcpy(decryptedNoKK, node->data.noKK);
        dekripsiInteger(decryptedNoKK, keyInt); // Dekripsi nomor KK
        printf("|   |- %s\n", decryptedNoKK);
        strcpy(lastPrintedNoKK, node->data.noKK); // Update nomor KK terakhir yang dicetak
    }

    // Print NIK dan nama penduduk jika node adalah node Penduduk
    if (node->data.NIK != NULL && node->data.nama != NULL) {
        char decryptedNIK[50];
        strcpy(decryptedNIK, node->data.NIK);
        dekripsiInteger(decryptedNIK, 0); // Dekripsi NIK
        printf("|       |- NIK_%s\n", decryptedNIK);
        printf("|          |- %s\n", node->data.nama);
    }

    // Print children recursively
    if (node->child != NULL) {
        printTree(node->child, level + 1, lastPrintedKota, lastPrintedNoKK);
    }

    // Move to the next sibling
    printTree(node->sibling, level, lastPrintedKota, lastPrintedNoKK);
}

// Fungsi utama untuk menampilkan struktur pohon
void tampilkanTree() {
    system("cls"); // Clear screen

    FILE *file;
    DataPenduduk data;
    Node *rootProvinsi = NULL;

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }
    
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s %s", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status, data.namaKota) != EOF) {
        dekripsiHuruf(data.alamat, keyStr);
        dekripsiInteger(data.NIK, keyInt);
        dekripsiInteger(data.noKK, keyInt);
        // Mencetak data penduduk ke dalam struktur pohon dengan hierarki provinsi, kota, dan keluarga
        rootProvinsi = tambahPenduduk(rootProvinsi, data);
    }

    fclose(file);

    if (rootProvinsi == NULL) {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }

    printf("Struktur Pohon Kartu Keluarga dan Penduduk Provinsi Jawa Barat:\n");
    char lastPrintedKota[50] = ""; // Variabel untuk menyimpan nama kota terakhir yang dicetak
    char lastPrintedNoKK[20] = ""; // Variabel untuk menyimpan nomor KK terakhir yang dicetak
    printTree(rootProvinsi, 0, lastPrintedKota, lastPrintedNoKK);

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
