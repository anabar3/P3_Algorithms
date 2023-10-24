#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

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




//CHECK IF create heap IS O(n)





//ARRAYS FOR TESTS AND FUNCTIONS FOR MEASUREMENTS
void init_seed() {
    srand(time(NULL));
/* set the seed of a new sequence of pseudo-random integers */
}

void print_array(int v[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%3d ", v[i]);
    }
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void copyArray(int source[], int dest[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

bool is_sorted (int v[], int n){
    int i;
    for (i=0; i<n-1;i++){
        if (v[i]>v[i+1]) return false;
    }
    return true;
}


//HEAP SORT IMPLEMENTATION
void Heapsort (int a[], int n){
    int i;
    pheap h;
    create_heap (a, n, h);
    for (i=0; i<n; i++) a[i] = remove_min (h);
}

//RANDOM INITIALIZATIONS
void random_init(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
    /* generate pseudo-random numbers between -n and +n */
}

void sorted_init(int v[], int n){
    random_init(v, n);
    Heapsort(v, n);
}

void inverse_init(int v[], int n){
    sorted_init(v, n);
    int i, j, temp;
    for (i = 0, j = n-1; i < j; i++, j--) {
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

//TEST HEAPSORT
void test_heapsort(){
    int size= 10;
    int v[size], w[size];
    printf("\n===============================\n");
    printf("\n\nCheck algorithm:\n");

    printf("\n\nRandom initialization:\n");
    random_init(v, size);
    copyArray(v, w, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nHeap Sort\n");
    Heapsort(w, size);
    print_array(w, size);
    printf("\nIs sorted? %d\n", is_sorted(w, size));
    
}




int main(){
    test_heap();
    test_heapsort();
    return 0;
}

