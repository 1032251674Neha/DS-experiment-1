#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define NAME_LEN 50

typedef struct FriendNode {
    int userID;
    struct FriendNode *next;
} FriendNode;

typedef struct {
    int id;
    char name[NAME_LEN];
    FriendNode *friends;
} User;

typedef struct {
    User users[MAX_USERS];
    int userCount;
} Graph;

/* Find user by ID */
int findUser(Graph *g, int id) {
    int i;

    for (i = 0; i < g->userCount; i++) {
        if (g->users[i].id == id)
            return i;
    }

    return -1;
}

/* Check whether two users are friends */
int areFriends(Graph *g, int id1, int id2) {
    int index = findUser(g, id1);
    FriendNode *temp;

    if (index == -1)
        return 0;

    temp = g->users[index].friends;

    while (temp != NULL) {
        if (temp->userID == id2)
            return 1;

        temp = temp->next;
    }

    return 0;
}

/* Add a node to a friend's list */
int addFriendNode(User *user, int friendID) {
    FriendNode *newNode = malloc(sizeof(FriendNode));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    newNode->userID = friendID;
    newNode->next = user->friends;
    user->friends = newNode;

    return 1;
}

/* Initialize graph */
void initializeGraph(Graph *g) {
    g->userCount = 0;
}

/* Add a new user */
void addUser(Graph *g) {
    int id;
    char name[NAME_LEN];

    if (g->userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }

    printf("Enter User ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid User ID!\n");
        while (getchar() != '\n');
        return;
    }

    if (findUser(g, id) != -1) {
        printf("User ID already exists!\n");
        return;
    }

    printf("Enter User Name: ");
    scanf(" %49[^\n]", name);

    g->users[g->userCount].id = id;
    strcpy(g->users[g->userCount].name, name);
    g->users[g->userCount].friends = NULL;
    g->userCount++;

    printf("User added successfully.\n");
}

/* Add friendship */
void addFriend(Graph *g) {
    int id1, id2;
    int index1, index2;

    printf("Enter first User ID: ");
    scanf("%d", &id1);

    printf("Enter second User ID: ");
    scanf("%d", &id2);

    index1 = findUser(g, id1);
    index2 = findUser(g, id2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both users do not exist.\n");
        return;
    }

    if (id1 == id2) {
        printf("A user cannot be their own friend.\n");
        return;
    }

    if (areFriends(g, id1, id2)) {
        printf("Users are already friends.\n");
        return;
    }

    if (!addFriendNode(&g->users[index1], id2))
        return;

    if (!addFriendNode(&g->users[index2], id1)) {
        /* Roll back the first insertion */
        FriendNode *temp = g->users[index1].friends;
        g->users[index1].friends = temp->next;
        free(temp);
        return;
    }

    printf("Friendship added successfully.\n");
}

/* Remove a friend from adjacency list */
void removeFriendNode(User *user, int friendID) {
    FriendNode *temp = user->friends;
    FriendNode *prev = NULL;

    while (temp != NULL) {
        if (temp->userID == friendID) {
            if (prev == NULL)
                user->friends = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

/* Remove friendship */
void removeFriend(Graph *g) {
    int id1, id2;
    int index1, index2;

    printf("Enter first User ID: ");
    scanf("%d", &id1);

    printf("Enter second User ID: ");
    scanf("%d", &id2);

    index1 = findUser(g, id1);
    index2 = findUser(g, id2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both users do not exist.\n");
        return;
    }

    if (!areFriends(g, id1, id2)) {
        printf("Users are not friends.\n");
        return;
    }

    removeFriendNode(&g->users[index1], id2);
    removeFriendNode(&g->users[index2], id1);

    printf("Friendship removed successfully.\n");
}

/* Find mutual friends */
void mutualFriends(Graph *g) {
    int id1, id2, found = 0;
    int index1, index2, friendIndex;
    FriendNode *temp;

    printf("Enter first User ID: ");
    scanf("%d", &id1);

    printf("Enter second User ID: ");
    scanf("%d", &id2);

    index1 = findUser(g, id1);
    index2 = findUser(g, id2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both users do not exist.\n");
        return;
    }

    if (id1 == id2) {
        printf("Please enter two different users.\n");
        return;
    }

    printf("\nMutual Friends:\n");
    temp = g->users[index1].friends;

    while (temp != NULL) {
        if (areFriends(g, id2, temp->userID)) {
            friendIndex = findUser(g, temp->userID);

            if (friendIndex != -1) {
                printf("%d - %s\n",
                       g->users[friendIndex].id,
                       g->users[friendIndex].name);
                found = 1;
            }
        }

        temp = temp->next;
    }

    if (!found)
        printf("No mutual friends found.\n");
}

/* Suggest friends of friends */
void suggestConnections(Graph *g) {
    int id, index, friendIndex, candidateIndex;
    int suggested[MAX_USERS] = {0};
    int found = 0;
    FriendNode *friendPtr, *fof;

    printf("Enter User ID: ");
    scanf("%d", &id);

    index = findUser(g, id);

    if (index == -1) {
        printf("User does not exist.\n");
        return;
    }

    friendPtr = g->users[index].friends;

    while (friendPtr != NULL) {
        friendIndex = findUser(g, friendPtr->userID);

        if (friendIndex != -1) {
            fof = g->users[friendIndex].friends;

            while (fof != NULL) {
                candidateIndex = findUser(g, fof->userID);

                if (candidateIndex != -1 &&
                    fof->userID != id &&
                    !areFriends(g, id, fof->userID)) {
                    suggested[candidateIndex] = 1;
                }

                fof = fof->next;
            }
        }

        friendPtr = friendPtr->next;
    }

    printf("\nSuggested Connections:\n");

    for (int i = 0; i < g->userCount; i++) {
        if (suggested[i]) {
            printf("%d - %s\n",
                   g->users[i].id,
                   g->users[i].name);
            found = 1;
        }
    }

    if (!found)
        printf("No connection suggestions available.\n");
}

/* Display social network */
void displayGraph(Graph *g) {
    FriendNode *temp;
    int friendIndex;

    printf("\n--- Social Network ---\n");

    for (int i = 0; i < g->userCount; i++) {
        printf("%d (%s) -> ",
               g->users[i].id,
               g->users[i].name);

        temp = g->users[i].friends;

        if (temp == NULL)
            printf("No friends");

        while (temp != NULL) {
            friendIndex = findUser(g, temp->userID);

            if (friendIndex != -1)
                printf("%s", g->users[friendIndex].name);

            temp = temp->next;

            if (temp != NULL)
                printf(" -> ");
        }

        printf("\n");
    }
}

/* Find shortest relationship path using BFS */
void showRelationship(Graph *g) {
    int startID, endID;
    int start, end;
    int dist[MAX_USERS], parent[MAX_USERS];
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    int u, v, friendIndex;
    FriendNode *temp;

    printf("Enter starting User ID: ");
    scanf("%d", &startID);

    printf("Enter destination User ID: ");
    scanf("%d", &endID);

    start = findUser(g, startID);
    end = findUser(g, endID);

    if (start == -1 || end == -1) {
        printf("One or both users do not exist.\n");
        return;
    }

    if (start == end) {
        printf("Both IDs belong to the same user.\n");
        printf("Relationship path: %s\n", g->users[start].name);
        printf("Distance: 0\n");
        return;
    }

    for (int i = 0; i < g->userCount; i++) {
        dist[i] = -1;
        parent[i] = -1;
    }

    dist[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        u = queue[front++];

        temp = g->users[u].friends;

        while (temp != NULL) {
            friendIndex = findUser(g, temp->userID);

            if (friendIndex != -1 && dist[friendIndex] == -1) {
                v = friendIndex;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue[rear++] = v;
            }

            temp = temp->next;
        }
    }

    if (dist[end] == -1) {
        printf("Users are not connected.\n");
        return;
    }

    {
        int path[MAX_USERS];
        int count = 0;

        for (int current = end; current != -1;
             current = parent[current]) {
            path[count++] = current;
        }

        printf("\nShortest Relationship Path: ");

        for (int i = count - 1; i >= 0; i--) {
            printf("%s", g->users[path[i]].name);

            if (i > 0)
                printf(" -> ");
        }

        printf("\nDistance: %d\n", dist[end]);
    }
}

/* Free allocated memory */
void freeGraph(Graph *g) {
    FriendNode *temp, *next;

    for (int i = 0; i < g->userCount; i++) {
        temp = g->users[i].friends;

        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }

        g->users[i].friends = NULL;
    }
}

/* Main function */
int main(void) {
    Graph g;
    int choice;

    initializeGraph(&g);

    do {
        printf("\n==============================\n");
        printf("     SOCIAL NETWORK SYSTEM\n");
        printf("==============================\n");
        printf("1. Add New User\n");
        printf("2. Add Friend\n");
        printf("3. Remove Friend\n");
        printf("4. Find Mutual Friends\n");
        printf("5. Suggest Connections\n");
        printf("6. Display Social Network\n");
        printf("7. Show Relationship (BFS)\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addUser(&g);
                break;

            case 2:
                addFriend(&g);
                break;

            case 3:
                removeFriend(&g);
                break;

            case 4:
                mutualFriends(&g);
                break;

            case 5:
                suggestConnections(&g);
                break;

            case 6:
                displayGraph(&g);
                break;

            case 7:
                showRelationship(&g);
                break;

            case 8:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    freeGraph(&g);
    return 0;
}
