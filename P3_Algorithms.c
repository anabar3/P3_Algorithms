#include <stdio.h>
#include <stdbool.h>

#define SZ 256000

struct heap {
    int last;
    int vector[SZ];
};

typedef struct heap* pheap;

//AUXILIARY FUNCTIONS

void initialize_heap (pheap h){
    h->last = 0;
}

bool is_empty_heap (pheap h){
    return h->last==0;
}

void percolate_up(pheap h, int i) {
    while (i > 1 && h->vector[i/2 -1] < h->vector[i-1]) {  
        int temp = h->vector[i/2 -1];
        h->vector[i/2 -1] = h->vector[i-1];
        h->vector[i-1] = temp;
        i /= 2;
    }
}

void insert(int x, pheap h) {
    if (h->last == SZ) {
        printf("Heap full\n");
        return;
    }
    h->last++;
    h->vector[h->last-1] = x; //-1 because index last in heap is one more than array
    percolate_up(h, h->last);
}

void percolate_down(pheap h, int i) {
    int left_child, right_child, j;
    do {
        left_child = 2*i;
        right_child = 2*i+1;
        j = i;
        if (right_child <= h->last && h->vector[right_child-1] > h->vector[i-1]) {
            i = right_child;
        }
        if (left_child <= h->last && h->vector[left_child-1] > h->vector[i-1]) {
            i = left_child;
        }
        int temp = h->vector[j-1];
        h->vector[j-1] = h->vector[i-1];
        h->vector[i-1] = temp;
    } while (j != i);
}

//PRACTICE FUNCTIONS

void create_heap(int a [], int n, pheap h){
    if(n > SZ){
        printf("Error: array size is too large\n");
        return;
    }

    int i;
    initialize_heap(h);
    for(i = 0; i < n; i++){
        insert(a[i], h);
    }
}

int remove_min(pheap h) {
    if (is_empty_heap(h)) {
        printf("Empty heap\n");
        return 0; //return a default value
    } else {
        int x = h->vector[0];
        h->vector[0] = h->vector[h->last-1];
        h->last--;
        percolate_down(h, 1);
        return x;
    }
}

//TEST HEAP

void print_heap(struct heap h){
    int i, levelpos = 0, levelend = 1;
    
    for(i = 0; i < h.last-1; i++, levelpos++){
        printf("%d  ", h.vector[i]);
        
        if(levelpos == levelend){
            printf("\n");
            levelend *= 2;
            levelpos = 0;
        }
    }
}

void test_heap(){
    pheap h;
    int testvec[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    create_heap(testvec, 10, h);
    print_heap(*h);
}

int main(){
    test_heap();
    return 0;
}

