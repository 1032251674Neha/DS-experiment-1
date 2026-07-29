#include <stdio.h>
#define MAX 5

int cq[MAX];
int front = -1, rear = -1;

void insert(int item)
{
    if ((rear + 1) % MAX == front)
    {
        printf("\nQueue Overflow\n");
        return;
    }

    if (front == -1)
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    cq[rear] = item;
    
}

int dequeue()
{
    int data;

    if (front == -1)
    {
        printf("\nQueue Underflow\n");
        return -1;
    }

    data = cq[front];

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }

    return data;
}

void display()
{
    int i;

    if (front == -1)
    {
        printf("\nQueue is Empty\n");
        return;
    }

    printf("\nQueue Elements:\n");

    if (front <= rear)
    {
        for (i = front; i <= rear; i++)
        {
            printf("%d ", cq[i]);
        }
    }
    else
    {
        for (i = front; i < MAX; i++)
        {
            printf("%d ", cq[i]);
        }

        for (i = 0; i <= rear; i++)
        {
            printf("%d ", cq[i]);
        }
    }

    printf("\n");
}

int main()
{
    int choice, item, value;

    while (1)
    {
        printf("\n         Circular Queue Menu          \n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter element: ");
                scanf("%d", &item);
                insert(item);
                break;

            case 2:
                value = dequeue();
                if (value != -1)
                    printf("Deleted element = %d\n", value);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program ended.\n");
                return 0;

            default:
                printf("Invalid Choice.\n");
        }
    }

    return 0;
}
