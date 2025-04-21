#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTS 6
#define MAX_PROTOTYPES 8

char* queue[MAX_PARTS];
int front = -1, rear = -1;

char* stack[MAX_PARTS];
int top = -1;

void enqueue(char* part)
{
    if (rear == MAX_PARTS - 1)
    {
        printf("Conveyor belt (queue) is full!\n");
        return;
    }
    if (front == -1)
    {
    front = 0;
    }
    rear++;
    queue[rear] = part;
}

char* dequeue()
{
    if (front == -1 || front > rear)
    {
        return NULL;
    }
    return queue[front++];
}

void push(char* part)
{
    if (top == MAX_PARTS - 1) 
    {
        printf("Stack overflow! Robot arm can't hold more.\n");
        return;
    }
    stack[++top] = part;
}

char* pop() 
{
    if (top == -1)
    {
        return NULL;
    }
    return stack[top--];
}

void simulateassembly()
{
    printf("Enqueuing parts on the conveyor belt:\n");
    char* parts[] = {"Engine", "Chassis", "Wheels", "Doors", "Battery", "Hood"};
    
    for (int i = 0; i < MAX_PARTS; i++)
    {
        enqueue(parts[i]);
        printf("%s added\n", parts[i]);
    }

    printf("\nRobot arm picking and stacking parts:\n");
    while (front <= rear) 
    {
        char* part = dequeue();
        push(part);
        printf("%s stacked\n", part);
    }

    printf("\nAssembling prototype in order:\n");
    while (top != -1)
    {
        printf( "%s attached\n", pop());
    }
}

char* garage[MAX_PROTOTYPES];
int garageStart = 0, garageEnd = 0, garageCount = 0;

void addToGarage(int carNumber)
{
    if (garageCount == MAX_PROTOTYPES)
    {
        printf("Garage full! Shipping out: Car%s\n", garage[garageStart]);
        free(garage[garageStart]);
        garageStart = (garageStart + 1) % MAX_PROTOTYPES;
        garageCount--;
    }

    garage[garageEnd] = (char*)malloc(10 * sizeof(char));
    int num = carNumber, i = 0;

    if (num == 0) 
    {
        garage[garageEnd][i++] = '0';
    } else 
    {
        int temp = num, digits = 0;
        while (temp) 
        { temp /= 10; digits++; 
        }

        for (int j = digits - 1; j >= 0; j--)
            {
            garage[garageEnd][j] = (num % 10) + '0';
            num /= 10;
            }
        i = digits;
    }

    garage[garageEnd][i] = '\0';

    garageEnd = (garageEnd + 1) % MAX_PROTOTYPES;
    garageCount++;
    printf("Car%d stored in garage\n", carNumber);
}

void simulateGarage() 
{
    printf("\nStoring car prototypes in the garage:\n");
    for (int i = 1; i <= 10; i++) 
    {
        addToGarage(i);
    }
    printf("\nThe oldest prototype is shipped out first so that old ones dont go unsold\n");
}

// Singly linked list for defective cars
typedef struct Node
{
    char* carName;
    struct Node* next;
} Node;

Node* defectiveHead = NULL;

// Doubly linked list for repaired cars
typedef struct DNode
{
    char* carName;
    struct DNode* next;
    struct DNode* prev;
} DNode;

DNode* repairedHead = NULL;
DNode* repairedTail = NULL;

void addDefective(char* carName)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->carName = carName;
    newNode->next = defectiveHead;
    defectiveHead = newNode;
}

void moveToRepaired(char* carName)
{
    Node* curr = defectiveHead, *prev = NULL;
    while (curr)
    {
        if (strcmp(curr->carName, carName) == 0) 
        {
            if (prev) prev->next = curr->next;
            else defectiveHead = curr->next;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (curr) 
    {
        DNode* newDNode = (DNode*)malloc(sizeof(DNode));
        newDNode->carName = carName;
        newDNode->next = NULL;
        newDNode->prev = repairedTail;
        if (repairedTail) repairedTail->next = newDNode;
        else repairedHead = newDNode;
        repairedTail = newDNode;
    }
}

void traverseRepaired() 
{
    printf("\nTraversing repaired list forward:\n");
    DNode* curr = repairedHead;
    while (curr)
    {
        printf("%s\n", curr->carName);
        curr = curr->next;
    }

    printf("Traversing repaired list backward:\n");
    curr = repairedTail;
    while (curr) 
    {
        printf("%s\n", curr->carName);
        curr = curr->prev;
    }
}

void simulateDefectTracking()
{
    printf("\nTracking defective cars:\n");
    addDefective("Car3");
    addDefective("Car6");

    printf("Car3 and Car6 marked defective.\n");

    moveToRepaired("Car3");

    printf("\nCar3 repaired and moved for inspection.\n");
    traverseRepaired();

 printf("\nThere was brake oil leak in car3 and it was repaired by replacing brake hoses and applying sealants\n");
}

typedef struct CNode
{
    char* carName;
    struct CNode* next;
} CNode;

CNode* vipHead = NULL;

void addVIP(char* carName)
{
    CNode* newNode = (CNode*)malloc(sizeof(CNode));
    newNode->carName = carName;
    if (!vipHead)
    {
        vipHead = newNode;
        newNode->next = newNode;
    }
    else 
    {
        newNode->next = vipHead->next;
        vipHead->next = newNode;
        vipHead = newNode;
    }
}

void traverseVIP(int rounds)
{
    printf("\nVIP Upgrade Checks:\n");
    if (!vipHead) return;
    CNode* temp = vipHead->next;
    for (int i = 0; i < rounds * 2; i++)
    {
        printf("Checking %s\n", temp->carName);
        temp = temp->next;
    }

    printf("\nCar5 gets privacy glass to ensure insides are not exposed to general people.\n");
}

void simulateVIPUpgrades()
{
    addVIP("Car1");
    addVIP("Car5");
    traverseVIP(2);
}

void main()
{
    simulateassembly();
    simulateGarage();
    simulateDefectTracking();
    simulateVIPUpgrades();
}
