#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1

// Node structure for Separate Chaining
struct Node {
    int data;
    struct Node *next;
};

// Hash table for Separate Chaining
struct Node *chain[SIZE];

// Hash tables for open addressing
int linear[SIZE];
int quadratic[SIZE];
int doubleHash[SIZE];

// Initialize all hash tables
void initialize() {
    for (int i = 0; i < SIZE; i++) {
        chain[i] = NULL;
        linear[i] = EMPTY;
        quadratic[i] = EMPTY;
        doubleHash[i] = EMPTY;
    }
}

// Primary hash function
int hash1(int key) {
    return key % SIZE;
}

// Secondary hash function for Double Hashing
int hash2(int key) {
    return 7 - (key % 7);
}

// 1. Separate Chaining
void insertChaining(int key) {
    int index = hash1(key);

    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

void displayChaining() {
    printf("\nSeparate Chaining:\n");

    for (int i = 0; i < SIZE; i++) {
        struct Node *temp = chain[i];

        printf("[%d]", i);

        while (temp != NULL) {
            printf(" -> %d", temp->data);
            temp = temp->next;
        }

        printf(" -> NULL\n");
    }
}

// 2. Linear Probing
void insertLinear(int key) {
    int index = hash1(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (linear[pos] == EMPTY) {
            linear[pos] = key;
            return;
        }
    }

    printf("Linear Probing: Hash table is full!\n");
}

void displayLinear() {
    printf("\nLinear Probing:\n");

    for (int i = 0; i < SIZE; i++) {
        if (linear[i] == EMPTY)
            printf("[%d] = EMPTY\n", i);
        else
            printf("[%d] = %d\n", i, linear[i]);
    }
}

// 3. Quadratic Probing
void insertQuadratic(int key) {
    int index = hash1(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i * i) % SIZE;

        if (quadratic[pos] == EMPTY) {
            quadratic[pos] = key;
            return;
        }
    }

    printf("Quadratic Probing: No empty slot found!\n");
}

void displayQuadratic() {
    printf("\nQuadratic Probing:\n");

    for (int i = 0; i < SIZE; i++) {
        if (quadratic[i] == EMPTY)
            printf("[%d] = EMPTY\n", i);
        else
            printf("[%d] = %d\n", i, quadratic[i]);
    }
}

// 4. Double Hashing
void insertDoubleHash(int key) {
    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i * step) % SIZE;

        if (doubleHash[pos] == EMPTY) {
            doubleHash[pos] = key;
            return;
        }
    }

    printf("Double Hashing: Hash table is full!\n");
}

void displayDoubleHash() {
    printf("\nDouble Hashing:\n");

    for (int i = 0; i < SIZE; i++) {
        if (doubleHash[i] == EMPTY)
            printf("[%d] = EMPTY\n", i);
        else
            printf("[%d] = %d\n", i, doubleHash[i]);
    }
}

// Main function
int main() {
    int n, key;

    initialize();

    printf("Enter number of keys (maximum %d): ", SIZE);
    scanf("%d", &n);

    if (n < 1 || n > SIZE) {
        printf("Please enter between 1 and %d keys.\n", SIZE);
        return 1;
    }

    printf("Enter %d integer keys:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &key);

        if (key < 0 || key == EMPTY) {
            printf("Please enter non-negative keys other than -1.\n");
            return 1;
        }

        insertChaining(key);
        insertLinear(key);
        insertQuadratic(key);
        insertDoubleHash(key);
    }

    displayChaining();
    displayLinear();
    displayQuadratic();
    displayDoubleHash();

    // Free memory used by Separate Chaining
    for (int i = 0; i < SIZE; i++) {
        struct Node *temp = chain[i];

        while (temp != NULL) {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    return 0;
}
