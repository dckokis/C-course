#include <stdio.h>
#include <stdlib.h>

#define N 12

// написать свой memcpy и вызывать его в swap. Корректно обрабатывать ситуацию когда одна часть памяти нахлестывается на другую
// ситуации когда dest раньше source и наоборот
// создать структуру с множеством полей и сортировать ее по конкретному полю(написать разные компараторы int/double лексикографический), читать данные из файла в структуру
// сделать функцию которая из FILE * прочитает структуру
int int_cmp(void *x, void *y){
    return *(int*)x - *(int*) y;
}

int double_cmp(void *x, void *y) {
    return *(double*)x - *(double*)y;
}

void swap(void *a, void *b, const size_t size) { // сделать с memcpy
    for (size_t i = 0; i < size; i++) {
        char *i1 = (char *) a + i;
        char *i2 = (char *) b + i;
        char tmp = *i1;
        *i1 = *i2;
        *i2 = tmp;
    }
}

void quick_sort(void *arr, unsigned int len_arr,
                size_t size_elem, int (*cmp)(void *, void *)) { // в конце медиана должна менять место
    if (len_arr == 1) {
        return;
    }
    unsigned int i = 0; // индексы левой половины
    unsigned int j = len_arr - 1; // индексы правой половины
    int median = (len_arr / 2);
    do {
        while (cmp((char *) arr + i * size_elem, (char *) arr + median * size_elem) < 0) { //left < median
            i++;
        }
        while (cmp((char *) arr + j * size_elem, (char *) arr + median * size_elem) > 0) { //right > median
            j--;
        }
        if (i <= j) {  // after while i <= j thereat we must swap left and right
            swap((char *) arr + i * size_elem, (char *) arr + j * size_elem, size_elem);
            i++;
            j--;
        }

    } while (i <= j);
    // recursion
    if (len_arr > i) quick_sort((char *) arr + i * size_elem, median, size_elem, cmp); //right
    if (j > 0) quick_sort((char *) arr, median + 1, size_elem, cmp); // left

}

int main() {
    int A[N] = {0};
    FILE *stream;
    stream = fopen("C:\\C_class\\quick_sort\\cmake-build-debug\\CMakeFiles\\Input.txt", "r");
    if (stream == 0) {
        printf("File is not found");
        exit(1);
    }
    int i;
    size_t length;
    fscanf_s(stream, "%d", &length); // read length of array from file
    unsigned int amount = 0;
    for (i = 0; i < length; i++) { // read array from file
        fscanf_s(stream, "%d", &A[i]);
        printf("%d ", A[i]);
        amount++;
    }
    printf("\n"); // print array
    if (amount != length) {
        exit(1);
    }
    size_t size_elem = sizeof(int);
    quick_sort(A, length, size_elem, int_cmp); // sorting array
    printf("Sorted array: ");
    for (i = 0; i < length; i++) { // printing sorted array
        printf("%d ", A[i]);
    }
    return 0;
}