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

void initialize_heap (pheap *h){
    *h = malloc(sizeof(struct heap));
    if(*h == NULL){
        printf("Error: Not enough space in memory\n");
        return;
    }
    (*h)->last = 0;
}

void delete_heap(pheap *h){
    free(*h);
}

bool is_empty_heap (pheap h){
    return h->last==0;
}

void percolate_up(pheap h, int i) {
    while (i > 1 && h->vector[i/2 -1] > h->vector[i-1]) {  
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
        if (right_child <= h->last && h->vector[right_child-1] < h->vector[i-1]) {
            i = right_child;
        }
        if (left_child <= h->last && h->vector[left_child-1] < h->vector[i-1]) {
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
    h->last = 0;
    int i;
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

void print_heap(struct heap h) {
    int i, level = 0, levelCount = 1;
    for (i = 0; i < h.last; i++) {
        printf("%2d ", h.vector[i]);
        if (i == levelCount - 1) {
            printf("\n");
            level++;
            levelCount += pow(2, level);
        }
    }
    printf("\n");
}

bool check_heap(struct heap h){
    int i;
    for(i = 0; i < h.last; i++){
        if(2*i+1 < h.last && h.vector[i] > h.vector[2*i+1]) return false;

        if(2*i+2 < h.last && h.vector[i] > h.vector[2*i+2]) return false;
    }
    return true;
}

void test_heap(){
    pheap h;

    int testvec1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int testvec2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int testvec3[10] = {8, 2, 3, 9, 1, 4, 10, 5, 6, 7};

    printf("=============================\n\n1. HEAP STRUCTURE TEST:\n\n");

    printf("Create heap with ascending vector:\n");
    initialize_heap(&h);
    create_heap(testvec1, 10, h);
    print_heap(*h);
    printf("Is OK? %d\n\n",check_heap(*h));

    printf("Create heap with descending vector:\n");
    initialize_heap(&h);
    create_heap(testvec2, 10, h);
    print_heap(*h);
    printf("Is OK? %d\n\n",check_heap(*h));

    printf("Create heap with random vector:\n");
    initialize_heap(&h);
    create_heap(testvec3, 10, h);
    print_heap(*h);
    printf("Is OK? %d\n\n",check_heap(*h));

    printf("Remove min:\n");
    remove_min(h);
    print_heap(*h);
    printf("Is OK? %d\n\n",check_heap(*h));

    printf("Remove min (x3):\n");
    for(int i = 0; i < 3; i++){
        remove_min(h);
    }
    print_heap(*h);
    printf("Is OK? %d\n\n",check_heap(*h));

    printf("Remove min (x7):\n");
    for(int i = 0; i < 7; i++){
        remove_min(h);
    }
    printf("Is OK? %d\n\n",check_heap(*h));
}


//HEAP SORT IMPLEMENTATION
void Heapsort (int a[], int n){
    int i;
    pheap h;
    initialize_heap(&h);
    create_heap (a, n, h);
    for (i=0; i<n; i++) a[i] = remove_min(h);
    delete_heap(&h);
}


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


double calculateTime(int testArray[], int size, void (*sortingAlg)(int v[], int n)){
    double t1, t2, difference;
    int copyofTest[size];
    copyArray(testArray, copyofTest, size);

    t1 = microseconds(); //start measure
    sortingAlg(testArray, size);
    t2 = microseconds(); //stop measure
    
    difference = t2 - t1;;
    if(difference >= 500){ //big times
        return difference;
    }
    else{ //small times
        double copyTime;
        int k;

        //measure copy time
        t1 = microseconds();
        for(k = 0; k < 1000; k++){ //repeat 1000 times
            copyArray(copyofTest, testArray, size);
        }
        t2 = microseconds();
        copyTime = t2 - t1;

        //measure sorting and substracting copy time
        t1 = microseconds(); //start measure
        for(k = 0; k < 1000; k++){ //repeat 1000 times
            copyArray(copyofTest, testArray, size);
            sortingAlg(testArray, size);
        }
        t2 = microseconds(); //stop measure

        return (t2-t1-copyTime)/1000;
    }
}

//CHECK IF create heap IS O(n)
void heapCreationTime(int rep) {
    printf("=============================\n\n1. HEAP CREATION COMPLEXITY TEST:\n\n");
    printf("Execution times in microseconds\nRepetitions: %d\n", rep);

    int sizes[10] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
    double totalTime, meandivdiff = 0, t1, t2;
    int i, j, k, n;
    char asterisk;
    pheap h;
    initialize_heap(&h);
    
    //PRINT HEADER
    printf("\nHEAP CREATION:\n");
    printf("%7s%17s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
        
    //MAKE MEASUREMENTS
    for (i=0; i<10; i++) { //iterate through the different sizes
        n = sizes[i];
        int testArray[n];
        totalTime = 0;

        for(j = 0; j < rep; j++){ //make the given repetitions
            random_init(testArray, n);

            t1 = microseconds(); //start measure
            create_heap(testArray, n, h);
            t2 = microseconds(); //stop measure
            
            if(t2 - t1 >= 500){ //big times
                totalTime += t2 - t1;
            }
            else{ //small times
                t1 = microseconds(); //start measure
                for(k = 0; k < 500; k++){ //repeat 1000 times
                    create_heap(testArray, n, h);
                }
                t2 = microseconds(); //stop measure

                totalTime += (t2-t1)/500;
            }
        }
        totalTime /= rep;

        //PRINT ROW
        if(totalTime < 500){
            asterisk = '*';
        }else{
            asterisk = ' ';
        }
        printf("%c  %-6d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/(pow(n,0.8)), totalTime/n, totalTime/(pow(n,1.2)));
        meandivdiff += totalTime/n;
    }
    //Print average
    printf("%59.6lf\n", meandivdiff/10);
}


//TEST HEAPSORT
void test_heapsort(){
    int size= 10;
    int v[size];
    printf("===============================\n\n");
    printf("2. HEAPSORT TEST:\n");

    printf("\nRandom initialization:\n");
    random_init(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nHeap Sort\n");
    Heapsort(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nAscending order initialization:\n");
    sorted_init(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nHeap Sort\n");
    Heapsort(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nDescending order initialization:\n");
    inverse_init(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nHeap Sort\n");
    Heapsort(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));
}

void print_header(int a){
    switch(a){
        case 0:
            printf("\nRANDOM INITALIZATION:\n");
            printf("%8s%16s%20s%17s%13s\n", "Size", "t(n)", "t(n)/n", "t(n)/n*log(n)", "t(n)/n^2");
        break;
        case 1:
            printf("\nASCENDING ORDER INITIALIZATION\n");
            printf("%8s%16s%20s%17s%13s\n", "Size", "t(n)", "t(n)/n", "t(n)/n*log(n)", "t(n)/n^2");
        break;
        case 2:
            printf("\nDESCENDING ORDER INITIALIZATION:\n");
            printf("%8s%16s%20s%17s%13s\n", "Size", "t(n)", "t(n)/n", "t(n)/n*log(n)", "t(n)/n^2");
        break;
    }
}

void print_row(int a, double totalTime, int n, double *meandivdiff){
    char asterisk;
    if(totalTime >= 500){
        asterisk = ' ';
    }
    else{
        asterisk = '*';
    }
    
    if(a == 0){
        //nlog(n)
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/n, totalTime/(n*log(n)), totalTime/(pow(n,2)));
        *meandivdiff += totalTime/(n*log(n));
    }else if(a == 1){
        //nlog(n)
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/n, totalTime/(n*log(n)), totalTime/(pow(n,2)));
        *meandivdiff += totalTime/(n*log(n));
    }else{
        //nlog(n)
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/n, totalTime/(n*log(n)), totalTime/(pow(n,2)));
        *meandivdiff += totalTime/(n*log(n));
    }
}


void test_complexity_heapsort(int rep) {
    int sizes[10] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
    printf("===============================\n\n");
    printf("Execution times in microseconds\nRepetitions: %d\n", rep);

    double totalTime, meandivdiff;
    int a, i, j, n;

    //3 DIFFERENT TABLES
    for(a = 0; a < 3; a++){
        meandivdiff = 0;
        
        //PRINT HEADER
        print_header(a);
            
        //MAKE MEASUREMENTS
        for (i=0; i<10; i++) { //iterate through the different sizes
            n = sizes[i];
            int testArray[n];
            totalTime = 0;

            for(j = 0; j < rep; j++){ //make the given repetitions
                
                if(a == 0){
                    random_init(testArray, n);
                }
                else if(a == 1){
                    sorted_init(testArray, n);
                }
                else{
                    inverse_init(testArray, n);
                }
                totalTime += calculateTime(testArray, n, Heapsort);
            }
            totalTime /= rep;

            //PRINT ROW
            print_row(a, totalTime, n, &meandivdiff);
        }
        //Print average
        printf("%59.6lf\n", meandivdiff/10);
    }
}



int main(){
    test_heap();
    //heapCreationTime(100);
    test_heapsort();
    test_complexity_heapsort(100);
    return 0;
}

