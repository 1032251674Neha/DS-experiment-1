
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int state[MAX];
int stack[MAX];
int top = -1;
int vertices;

// DFS function for Topological Sort
int DFS(int u)
{
    state[u] = 1;

    for (int v = 0; v < vertices; v++)
    {
        if (graph[u][v] == 1)
        {
            if (state[v] == 1)
            {
                return 0;  // Cycle detected
            }

            if (state[v] == 0)
            {
                if (DFS(v) == 0)
                {
                    return 0;
                }
            }
        }
    }

    state[u] = 2;
    stack[++top] = u;

    return 1;
}

// Topological Sort function
void topologicalSort()
{
    top = -1;

    for (int i = 0; i < vertices; i++)
    {
        state[i] = 0;
    }

    for (int i = 0; i < vertices; i++)
    {
        if (state[i] == 0)
        {
            if (DFS(i) == 0)
            {
                printf("\nCycle detected!\n");
                printf("Topological sorting is not possible.\n");
                return;
            }
        }
    }

    printf("\nTopological Sort: ");

    while (top >= 0)
    {
        printf("%d ", stack[top--]);
    }

    printf("\n");
}

// Add a directed edge
void addEdge()
{
    int src, dest;

    printf("Enter source vertex (0 to %d): ", vertices - 1);
    scanf("%d", &src);

    printf("Enter destination vertex (0 to %d): ", vertices - 1);
    scanf("%d", &dest);

    if (src < 0 || src >= vertices ||
        dest < 0 || dest >= vertices)
    {
        printf("Invalid vertex!\n");
        return;
    }

    graph[src][dest] = 1;

    printf("Edge %d -> %d added successfully.\n",
           src, dest);
}

// Display adjacency matrix
void displayGraph()
{
    printf("\nAdjacency Matrix:\n");

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    int choice;

    printf("Enter number of vertices (1 to %d): ", MAX);
    scanf("%d", &vertices);

    if (vertices < 1 || vertices > MAX)
    {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph[i][j] = 0;
        }
    }

    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Add Edge\n");
        printf("2. Display Graph\n");
        printf("3. Topological Sort using DFS\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addEdge();
                break;

            case 2:
                displayGraph();
                break;

            case 3:
                topologicalSort();
                break;

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
