
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int key, degree;
    struct Node *parent, *child, *sibling;
};

struct Node *createNode(int key) {
    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;

    return node;
}

struct Node *mergeRoots(struct Node *h1, struct Node *h2) {
    struct Node dummy;
    struct Node *tail = &dummy;

    dummy.sibling = NULL;

    while (h1 != NULL && h2 != NULL) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }

    tail->sibling = (h1 != NULL) ? h1 : h2;

    return dummy.sibling;
}

void linkTree(struct Node *child, struct Node *parent) {
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree++;
}

struct Node *unionHeap(struct Node *h1, struct Node *h2) {
    struct Node *head = mergeRoots(h1, h2);

    if (head == NULL)
        return NULL;

    struct Node *prev = NULL;
    struct Node *curr = head;
    struct Node *next = curr->sibling;

    while (next != NULL) {
        if (curr->degree != next->degree ||
            (next->sibling != NULL &&
             next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            curr->sibling = next->sibling;
            linkTree(next, curr);
        } else {
            if (prev == NULL)
                head = next;
            else
                prev->sibling = next;

            linkTree(curr, next);
            curr = next;
        }

        next = curr->sibling;
    }

    return head;
}

struct Node *insert(struct Node *heap, int key) {
    struct Node *node = createNode(key);
    return unionHeap(heap, node);
}

struct Node *findMin(struct Node *heap) {
    if (heap == NULL)
        return NULL;

    struct Node *minNode = heap;

    while (heap != NULL) {
        if (heap->key < minNode->key)
            minNode = heap;
        heap = heap->sibling;
    }

    return minNode;
}

struct Node *reverseChildren(struct Node *child) {
    struct Node *prev = NULL;
    struct Node *next;

    while (child != NULL) {
        next = child->sibling;
        child->sibling = prev;
        child->parent = NULL;
        prev = child;
        child = next;
    }

    return prev;
}

struct Node *extractMin(struct Node *heap, int *minKey) {
    if (heap == NULL) {
        printf("Heap is empty!\n");
        return heap;
    }

    struct Node *minNode = heap;
    struct Node *minPrev = NULL;
    struct Node *prev = NULL;
    struct Node *curr = heap;

    while (curr != NULL) {
        if (curr->key < minNode->key) {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (minPrev == NULL)
        heap = minNode->sibling;
    else
        minPrev->sibling = minNode->sibling;

    struct Node *children = reverseChildren(minNode->child);

    *minKey = minNode->key;
    free(minNode);

    return unionHeap(heap, children);
}

struct Node *searchNode(struct Node *heap, int key) {
    while (heap != NULL) {
        if (heap->key == key)
            return heap;

        struct Node *found = searchNode(heap->child, key);

        if (found != NULL)
            return found;

        heap = heap->sibling;
    }

    return NULL;
}

int decreaseKey(struct Node *heap, int oldKey, int newKey) {
    struct Node *node = searchNode(heap, oldKey);

    if (node == NULL) {
        printf("Key not found!\n");
        return 0;
    }

    if (newKey > oldKey) {
        printf("New key must be smaller than or equal to old key!\n");
        return 0;
    }

    node->key = newKey;

    while (node->parent != NULL &&
           node->key < node->parent->key) {
        int temp = node->key;
        node->key = node->parent->key;
        node->parent->key = temp;
        node = node->parent;
    }

    printf("Key decreased successfully.\n");
    return 1;
}

struct Node *deleteKey(struct Node *heap, int key) {
    struct Node *node = searchNode(heap, key);

    if (node == NULL) {
        printf("Key not found!\n");
        return heap;
    }

    if (key == INT_MIN) {
        printf("INT_MIN cannot be deleted by this method.\n");
        return heap;
    }

    decreaseKey(heap, key, INT_MIN);

    int removedKey;
    return extractMin(heap, &removedKey);
}

void display(struct Node *heap) {
    if (heap == NULL) {
        printf("Heap is empty!\n");
        return;
    }

    printf("Binomial Heap (root lists):\n");

    while (heap != NULL) {
        printf("Root: %d, Degree: %d\n",
               heap->key, heap->degree);
        heap = heap->sibling;
    }
}

void freeHeap(struct Node *heap) {
    while (heap != NULL) {
        struct Node *next = heap->sibling;
        freeHeap(heap->child);
        free(heap);
        heap = next;
    }
}

int main(void) {
    struct Node *heap = NULL;
    struct Node *heap2 = NULL;
    int choice, key, newKey, minKey;

    do {
        printf("\n--- BINOMIAL HEAP MENU ---\n");
        printf("1. Insert\n");
        printf("2. Find-Min\n");
        printf("3. Extract-Min\n");
        printf("4. Decrease-Key\n");
        printf("5. Delete\n");
        printf("6. Union with another heap\n");
        printf("7. Display root list\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            heap = insert(heap, key);
            printf("Key inserted successfully.\n");
            break;

        case 2: {
            struct Node *minNode = findMin(heap);

            if (minNode == NULL)
                printf("Heap is empty!\n");
            else
                printf("Minimum key: %d\n", minNode->key);
            break;
        }

        case 3:
            heap = extractMin(heap, &minKey);
            if (heap != NULL || minKey != INT_MIN)
                printf("Extracted minimum: %d\n", minKey);
            break;

        case 4:
            printf("Enter existing key: ");
            scanf("%d", &key);
            printf("Enter new smaller key: ");
            scanf("%d", &newKey);
            decreaseKey(heap, key, newKey);
            break;

        case 5:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            heap = deleteKey(heap, key);
            printf("Delete operation completed.\n");
            break;

        case 6:
            printf("Enter number of keys for second heap: ");
            scanf("%d", &choice);

            if (choice < 0) {
                printf("Invalid number of keys!\n");
                break;
            }

            freeHeap(heap2);
            heap2 = NULL;

            for (int i = 0; i < choice; i++) {
                printf("Enter key %d: ", i + 1);
                scanf("%d", &key);
                heap2 = insert(heap2, key);
            }

            heap = unionHeap(heap, heap2);
            heap2 = NULL;
            printf("Heaps united successfully.\n");
            break;

        case 7:
            display(heap);
            break;

        case 8:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 8);

    freeHeap(heap);
    freeHeap(heap2);

    return 0;
}
