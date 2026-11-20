#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* массивы делаем глобальными, чтобы не возиться с malloc */
int a[100000];    /* исходный массив */
int b[100000];    /* копия, которую сортируем */
int tmp[100000];  /* вспомогательный массив для слияния */

/* копируем массив a в массив b */
void copyArray(int n) {
    int i;
    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

/* сортировка пузырьком */
void bubbleSort(int n) {
    int i, j, t;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (b[j] > b[j + 1]) {
                t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
            }
        }
    }
}

/* сортировка вставками */
void insertionSort(int n) {
    int i, j, x;
    for (i = 1; i < n; i++) {
        x = b[i];
        j = i - 1;
        while (j >= 0 && b[j] > x) {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = x;
    }
}

/* слияние двух отсортированных частей: [left..mid] и [mid+1..right] */
void merge(int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (b[i] <= b[j]) {
            tmp[k] = b[i];
            i++;
        } else {
            tmp[k] = b[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        tmp[k] = b[i];
        i++;
        k++;
    }
    while (j <= right) {
        tmp[k] = b[j];
        j++;
        k++;
    }
    for (i = left; i <= right; i++) {
        b[i] = tmp[i];
    }
}

/* сортировка слиянием (рекурсия) */
void mergeSort(int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main() {
    int sizes[4] = {10, 1000, 10000, 100000};
    int s, i, n;
    clock_t start, end;
    double t1, t2, t3;

    srand(time(NULL));

    printf("Размер массива | Пузырек | Вставки | Слияние\n");

    for (s = 0; s < 4; s++) {
        n = sizes[s];

        /* заполняем массив случайными числами */
        for (i = 0; i < n; i++) {
            a[i] = rand();
        }

        /* пузырёк */
        copyArray(n);
        start = clock();
        bubbleSort(n);
        end = clock();
        t1 = (double)(end - start) / CLOCKS_PER_SEC;

        /* вставки */
        copyArray(n);
        start = clock();
        insertionSort(n);
        end = clock();
        t2 = (double)(end - start) / CLOCKS_PER_SEC;

        /* слияние */
        copyArray(n);
        start = clock();
        mergeSort(0, n - 1);
        end = clock();
        t3 = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%14d | %7.4f | %7.4f | %7.4f\n", n, t1, t2, t3);
    }

    return 0;
}
