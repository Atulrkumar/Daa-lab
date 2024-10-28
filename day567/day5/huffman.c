#include <stdio.h>
#include <stdlib.h>

typedef struct SYM {
    char ch;
    int freq;
    struct SYM *l, *r;
} SYM;

typedef struct Heap {
    int size;
    int cap;
    SYM **arr;
} Heap;

SYM *newNode(char ch, int freq) {
    SYM *temp = (SYM *)malloc(sizeof(SYM));
    temp->ch = ch;
    temp->freq = freq;
    temp->l = temp->r = NULL;
    return temp;
}

Heap *createHeap(int cap) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;
    heap->cap = cap;
    heap->arr = (SYM **)malloc(heap->cap * sizeof(SYM *));
    return heap;
}

void swapNode(SYM **a, SYM **b) {
    SYM *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left]->freq < heap->arr[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->arr[right]->freq < heap->arr[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&heap->arr[smallest], &heap->arr[idx]);
        heapify(heap, smallest);
    }
}

int isSizeOne(Heap *heap) {
    return (heap->size == 1);
}

SYM *extractMin(Heap *heap) {
    SYM *temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    --heap->size;
    heapify(heap, 0);
    return temp;
}

void insertHeap(Heap *heap, SYM *node) {
    ++heap->size;
    int i = heap->size - 1;
    while (i && node->freq < heap->arr[(i - 1) / 2]->freq) {
        heap->arr[i] = heap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->arr[i] = node;
}

Heap *buildHeap(char ch[], int freq[], int size) {
    Heap *heap = createHeap(size);
    for (int i = 0; i < size; ++i)
        heap->arr[i] = newNode(ch[i], freq[i]);
    heap->size = size;
    for (int i = (heap->size - 1) / 2; i >= 0; --i)
        heapify(heap, i);
    return heap;
}

SYM *buildHuffTree(char ch[], int freq[], int size) {
    SYM *l, *r, *top;
    Heap *heap = buildHeap(ch, freq, size);
    while (!isSizeOne(heap)) {
        l = extractMin(heap);
        r = extractMin(heap);
        top = newNode('$', l->freq + r->freq);
        top->l = l;
        top->r = r;
        insertHeap(heap, top);
    }
    return extractMin(heap);
}

void inOrder(SYM *root) {
    if (root) {
        inOrder(root->l);
        if (root->ch != '$') {
            printf("%c ", root->ch);
        }
        inOrder(root->r);
    }
}

int main() {
    int n;
    printf("Enter number of alphabets: ");
    scanf("%d", &n);

    char ch[n];
    int freq[n];

    printf("Enter alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &ch[i]);
    }

    printf("Enter frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);
    }

    SYM *root = buildHuffTree(ch, freq, n);
    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    return 0;
}
