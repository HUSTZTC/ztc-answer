#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace std;

int shared_mem[100000008];

#define BASE 10
void optimized_pre_phase1(size_t) {}

void optimized_post_phase1() {}

void optimized_pre_phase2(size_t) {}

void optimized_post_phase2() {}

//比大小
inline int cmp(const void* a, const void* b) {
    return (*(float*)a > *(float*)b) - (*(float*)a < *(float*)b);
}

//交换
inline void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

inline void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//二分法快排
inline void optimized_qsort(float*data, size_t size) {
    if (size <= 1) return;

    int* stack; 
    stack=(int*)malloc(size*sizeof(float));
    int top = -1;
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        int pivot_index = low;
        float pivot = data[pivot_index];
        int i = low;
        int j = high;

        while (i <= j) {
            while (cmp(&data[i], &pivot) < 0) i++;
            while (cmp(&data[j], &pivot) > 0) j--;
            if (i <= j) {
                swap(&data[i], &data[j]);
                i++;
                j--;
            }
        }

        if (low < j) {
            stack[++top] = low;
            stack[++top] = j;
        }
        if (i < high) {
            stack[++top] = i;
            stack[++top] = high;
        }
    }
    free(stack);
}

//同理，但是此快排适用于query，并且将query原有顺序写进index
inline void optimized_qsort_for_phase2(float*data, int*index, size_t size) {
    if (size <= 1) return;

    int* stack; 
    stack=(int*)malloc(size*sizeof(float));
    int top = -1;
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        int pivot_index = low;
        float pivot = data[pivot_index];
        int i = low;
        int j = high;

        while (i <= j) {
            while (cmp(&data[i], &pivot) < 0) i++;
            while (cmp(&data[j], &pivot) > 0) j--;
            if (i <= j) {
                swap(&data[i], &data[j]);
                swap_int(&index[i], &index[j]);
                i++;
                j--;
            }
        }

        if (low < j) {
            stack[++top] = low;
            stack[++top] = j;
        }
        if (i < high) {
            stack[++top] = i;
            stack[++top] = high;
        }
    }
    free(stack);
}


void optimized_do_phase1(float* data, size_t size) {
    optimized_qsort(data, size);
}

void optimized_do_phase2(size_t* result, float* data, float* query, size_t size) {
    
    int*index = (int*)malloc(sizeof(int)*size);
    for(size_t i = 0; i < size; ++i) {
        index[i] = i;
        
    }
//第一次依旧使用二分法，但是在第二次以后，由于query中递增，因此l并不需归零，
//只需要继续进行query的下一个数扫描，并且从小到大遍历而非二分。
   optimized_qsort_for_phase2(query, index, size);
    size_t l = 0;
    size_t  r = size;

    while (l < r) {
        size_t m = (l + r) / 2;
        if (data[m] < query[0]) {
            l = m + 1;
        } else {
               r = m;
        }
    }
        result[index[0]] = l;

    for (size_t i = 1; i < size; ++i) {
        size_t  r = size;
        while (l < r) {
            size_t m = l;
            if (data[m] < query[i]) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        result[index[i]] = l;
    }
    free(index);
}
