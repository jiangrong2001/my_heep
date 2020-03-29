#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_NUM 111

typedef long Node;

typedef struct {
    int maxSize;
    int size;
    Node *heap;
} TreeHeap;

bool g_visited[MAX_NUM * MAX_NUM] = {false};
int g_dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void InitHeap(TreeHeap *heap, int maxSize)
{
    heap->size = 0;
    heap->maxSize = maxSize;
    heap->heap = (Node *)malloc(sizeof(Node) * maxSize);
}

void FreeHeap(TreeHeap *heap)
{
    heap->size = 0;
    heap->maxSize = 0;
    if (heap->heap != NULL) {
        free(heap->heap);
    }
}

void ShiftUp(TreeHeap *heap, int pos)
{
    int father = 0;
    int currentPos = pos;
    Node tempValue;

    if (pos <= 0) {
        return;
    }

    do {
        father = (currentPos - 1) / 2;
        // compare father and currentPos
        if ((heap->heap[father]) > (heap->heap[currentPos])) {
            tempValue = heap->heap[father];
            heap->heap[father] = heap->heap[currentPos];
            heap->heap[currentPos] = tempValue;
            currentPos = father;
        } else {
            break;
        }        
    } while(currentPos > 0);    
}

void ShiftDown(TreeHeap *heap, int pos)
{
    int leftChild = 0;
    int rightChild = 0;
    int switchPos = 0;
    int currentPos = pos;
    Node tempValue;

    if (pos >= heap->size) {
        return;
    }

    do {
        switchPos = currentPos;
        leftChild = currentPos * 2 + 1;
        if (leftChild >= heap->size) {
            break;
        }
        // compare left child and currentPos
        if ((heap->heap[leftChild]) < (heap->heap[switchPos])) {
            switchPos = leftChild;
        }
        
        rightChild = (currentPos + 1) * 2;
        if (rightChild < heap->size) {
            // compare left child and switchPos
            if ((heap->heap[rightChild]) < (heap->heap[switchPos])) {
                switchPos = rightChild;
            }
        }

        if (switchPos != currentPos) {
            tempValue = heap->heap[switchPos];
            heap->heap[switchPos] = heap->heap[currentPos];
            heap->heap[currentPos] = tempValue;
            currentPos = switchPos;
        } else {
            break;
        }
    } while(currentPos < heap->size);    
}

int getSize(TreeHeap *heap)
{
    return heap->size;
}

void PushHeap(TreeHeap *heap, Node value)
{
    if (heap->size >= heap->maxSize) {
        return;
    }
    heap->heap[heap->size] = value;
    heap->size++;
    ShiftUp(heap, heap->size - 1);
}

Node PopHeap(TreeHeap *heap)
{
    Node value = heap->heap[0];
    heap->size--;
    if (heap->size > 0) {
        heap->heap[0] = heap->heap[heap->size];
        ShiftDown(heap, 0);
    }

    return value;
}

Node GetMinNode(TreeHeap *heap)
{
    return heap->heap[0];
}

void PrintfHeap(TreeHeap *heap)
{
    /*for (int i = 0; i < heap->size; i++) {
        printf("heap[%d] = %ld ", i, heap->heap[i]);
    }*/
    for (int i = heap->size - 1; i >= 0 ; i--) {
        printf("heap[%d] = %ld ", i, heap->heap[i]);
    }    
    printf("GetMinNode = %ld \n", GetMinNode(heap));
}
int main()
{    

    TreeHeap heap;
    InitHeap(&heap, MAX_NUM * MAX_NUM);
    for (int i = 0 ; i < MAX_NUM; i++) {
        PushHeap(&heap, i);
    }
    for (int i = MAX_NUM - 1; i >= 0 ; i--) {
        PushHeap(&heap, i);
    }    
    PrintfHeap(&heap);
    FreeHeap(&heap);   
}

