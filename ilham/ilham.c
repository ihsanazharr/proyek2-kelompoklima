#include "../disdukcapil.h"

extern int keyStr;
extern int keyInt;

FamilyTree* rootFamilyTree = NULL; // Inisialisasi pointer ke pohon keluarga

// Fungsi rekursif untuk menambahkan penduduk ke struktur tree
FamilyTreeNode* createFamilyTreeNode(DataPenduduk data) {
    FamilyTreeNode* newNode = (FamilyTreeNode*)malloc(sizeof(FamilyTreeNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->parent = NULL;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}//Ide untuk serialization & deserialization

// Fungsi rekursif untuk mencetak pohon secara terstruktur
void addChildToFamilyTree(FamilyTreeNode* parent, FamilyTreeNode* child) {
    if (parent == NULL) {
        return;
    }
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        FamilyTreeNode* sibling = parent->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child;
    }
    child->parent = parent;
}

// Fungsi utama untuk menampilkan struktur pohon
void printFamilyTree(FamilyTreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("|   ");
    }
    printf("|- %s\n", root->data.nama);
    FamilyTreeNode* child = root->firstChild;
    while (child != NULL) {
        printFamilyTree(child, level + 1);
        child = child->nextSibling;
    }
}

void serializeFamilyTree(FamilyTreeNode* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    fprintf(file, "%d %s %s %s %s %c %s %s %s %s\n", root->data.id, root->data.NIK, root->data.noKK, root->data.nama, root->data.tanggalLahir, root->data.jk, root->data.alamat, root->data.tempat_lahir, root->data.agama, root->data.status);

    serializeFamilyTree(root->firstChild, file);
    serializeFamilyTree(root->nextSibling, file);
}

// Fungsi untuk melakukan deserialization dari file ke FamilyTree
FamilyTreeNode* deserializeFamilyTree(FILE* file) {
    FamilyTreeNode* root = NULL;
    while (!feof(file)) {
        DataPenduduk data;
        if (fscanf(file, "%d %s %s %s %s %c %s %s %s %s\n", &data.id, data.NIK, data.noKK, data.nama, data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) == EOF) {
            break;
        }
        FamilyTreeNode* newNode = createFamilyTreeNode(data);
        if (root == NULL) {
            root = newNode;
        } else {
            addChildToFamilyTree(root, newNode);
        }
    }
    return root;
}

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
void printTree(Node *node, int level, char *lastPrintedKK) {
    if (node == NULL) {
        return;
    }
    //print no KK jika berbeda dengan no KK terakhir
    if (strcmp(node->data.noKK, lastPrintedKK) != 0) {
        printf("|- Kartu Keluarga %s\n", node->data.noKK);
        strcpy(lastPrintedKK, node->data.noKK);
    }

    // Print nama penduduk
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
                                                        
    while (fscanf(file, "%d %s %s %s %s %c %s %s %s %s", &data.id, data.NIK,data.noKK, data.nama,data.tanggalLahir, &data.jk, data.alamat, data.tempat_lahir, data.agama, data.status) != EOF) {
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
    char lastPrintedKK[20] = "";
    printTree(root, 0, lastPrintedKK);

    // Hapus bagian ini jika tidak ingin menunggu input dari pengguna
    char userChoice;
    printf("Apakah Anda ingin kembali ke menu? [Y/N]: ");
    scanf(" %c", &userChoice);
    if (userChoice == 'Y' || userChoice == 'y') {
        menuAwal();
    } else {
        printf("Terima kasih.\n");
    }
}

void addNodeToFamilyTree(FamilyTree* tree, DataPenduduk* newNode) {
    if (tree->root == NULL) {
        tree->root = newNode;
    } else {
        DataPenduduk* current = tree->root;
        while (current != NULL) {
            if (strcmp(current->noKK, newNode->noKK) == 0) {
                DataPenduduk* sibling = current->firstChild;
                if (sibling == NULL) {
                    current->firstChild = newNode;
                } else {
                    while (sibling->nextSibling != NULL) {
                        sibling = sibling->nextSibling;
                    }
                    sibling->nextSibling = newNode;
                }
                newNode->parent = current;
                return;
            }
            current = current->nextSibling;
        }
        current = tree->root;
        while (current->nextSibling != NULL) {
            current = current->nextSibling;
        }
        current->nextSibling = newNode;
    }
}
