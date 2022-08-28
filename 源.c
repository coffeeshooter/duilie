
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HeapStruct
{
    int Capacity;
    int Size;
    int* Elements;
};

typedef struct HeapStruct* pri_queue;

pri_queue pri_queue_init(int MaxElements);
void destroy_queue(pri_queue H);
void make_prique_empty(pri_queue H);
void push_pri_queue(int X, pri_queue H);
int pop_pri_queue(pri_queue H);
int find_que_min(pri_queue H);
int is_queue_empty(pri_queue H);
int is_queue_full(pri_queue H);
void printf_pri_queue(pri_queue H);

#define MinPQSize (10)
#define MinData (-32767)

pri_queue pri_queue_init(int MaxElements)
{
    pri_queue H;

    if (MaxElements < MinPQSize)
        printf("\nPriority queue size is too small!\n");

    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        printf("\nOut of space!!!\n");
    H->Elements = malloc((MaxElements + 1) * sizeof(int));
    if (H->Elements == NULL)
        printf("Out of space!!!\n");

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}
void push_pri_queue(int X, pri_queue H)
{
    int i;

    if (is_queue_full(H))
    {
        printf("Priority queue is full\n");
        return;
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2) 
        H->Elements[i] = H->Elements[i / 2];            
    H->Elements[i] = X;
}

int pop_pri_queue(pri_queue H)
{
    int i, Child;
    int MinElement, LastElement;

    if (is_queue_empty(H))
    {
        printf("Priority queue is empty!\n");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i * 2 <= H->Size; i = Child)
    {

        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;

        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

void make_prique_empty(pri_queue H)
{
    H->Size = 0;
}

int find_que_min(pri_queue H)
{
    if (!is_queue_empty(H))
        return H->Elements[1];
    printf("Priority Queue is Empty");
    return H->Elements[0];
}

int is_queue_empty(pri_queue H)
{
    return H->Size == 0;
}

int is_queue_full(pri_queue H)
{
    return H->Size == H->Capacity;
}

void destroy_queue(pri_queue H)
{
    free(H->Elements);
    free(H);
}

int main(int argc, char** argv)
{
    pri_queue H = pri_queue_init(50);
    int ar[] = { 32, 21, 16, 24, 31, 19, 68, 65, 26, 13 };
    int i;

    for (i = 0; i < 11; i++)
        push_pri_queue(ar[i], H);

    printf_pri_queue(H);

    printf("\n测试pop_pri_queue():\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", pop_pri_queue(H));
    }
    printf("\n\n");

    return 0;
}

void printf_pri_queue(pri_queue H)
{
    int i = 0;

    printf("\n直接输出优先队列的内容：\n");

    for (i = 1; i < H->Size; i++)
        printf("%d ", H->Elements[i]);

    printf("\n\n");
}
