#include "../disdukcapil.h"

typedef struct Node {
    DataPenduduk data;
    struct Node *child;
    struct Node *sibling;
} Node;

extern int keyStr;
extern int keyInt;

// Fungsi rekursif untuk menambahkan penduduk ke pohon
Node* tambahPenduduk(Node *root, DataPenduduk data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->child = NULL;
    newNode->sibling = NULL;

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
void printTree(Node *node, int level, char *lastPrintedKK) {
    if (node == NULL) {
        return;
    }

    // Print the KK number if it is different from the last printed KK number
    if (strcmp(node->data.noKK, lastPrintedKK) != 0) {
        printf("|- Kartu Keluarga %s\n", node->data.noKK);
        strcpy(lastPrintedKK, node->data.noKK);
    }

    // Print the resident's name
    printf("|   |- %s\n", node->data.nama);

    // Recursively print children
    if (node->child != NULL) {
        printTree(node->child, level + 1, lastPrintedKK);
    }

    // Move to the next sibling
    if (node->sibling != NULL) {
        printTree(node->sibling, level, lastPrintedKK);
    }
}




// Fungsi utama untuk menampilkan struktur pohon
void tampilkanTree() {
    system("cls"); // Clear screen

    FILE *file;
    DataPenduduk data;
    Node *root = NULL;

    file = fopen("dataPenduduk.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %c %s %s %s %s", &data.id, data.NIK,data.noKK, data.nama, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF) {
        dekripsiHuruf(data.alamat, keyStr);
        dekripsiInteger(data.NIK, keyInt);
        dekripsiInteger(data.noKK, keyInt);
        root = tambahPenduduk(root, data);
    }

    fclose(file);

    if (root == NULL) {
        printf("Tidak ada data yang tersedia.\n");
        return;
    }

    printf("Struktur Pohon Kartu Keluarga dan Penduduk:\n");
    char lastPrintedKK[20] = ""; // Assuming KK number is at most 20 characters long
    printTree(root, 0, lastPrintedKK);

    char userChoice;
    printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        menuAwal();
    } else {
        printf("Terima kasih.\n");
    }
}
