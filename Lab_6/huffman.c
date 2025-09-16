#include <stdio.h>
#include <stdlib.h>

// Structure for a node
typedef struct Node {
    char alphabet;
    int freq;
    struct Node *left, *right;
} Node;

// Create a new node
Node* newNode(char alphabet, int freq) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->alphabet = alphabet;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to swap nodes
void swap(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Simple function to sort array of nodes (by frequency)
void sort(Node* arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i]->freq > arr[j]->freq) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

// Build Huffman Tree
Node* buildHuffman(Node* arr[], int n) {
    while (n > 1) {
        sort(arr, n);
        Node* left = arr[0];
        Node* right = arr[1];

        Node* parent = newNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // Shift array left
        for (int i = 2; i < n; i++) {
            arr[i-2] = arr[i];
        }
        arr[n-2] = parent;
        n--;
    }
    return arr[0]; // Root
}

// In-order traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        if (root->alphabet != '$') // skip internal nodes
            printf("%c ", root->alphabet);
        inorder(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int freq[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
        scanf(" %c", &alphabets[i]);

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    Node* arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = newNode(alphabets[i], freq[i]);
    }

    Node* root = buildHuffman(arr, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorder(root);
    printf("\n");

    return 0;
}
