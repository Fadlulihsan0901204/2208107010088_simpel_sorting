#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void quickShuffle(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        int r = rand() % n;
        int temp = array[i];
        array[i] = array[r];
        array[r] = temp;
    }
}

void bubbleSort(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    int min_idx, temp;
    for (int i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n)
{
    int key, j;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printNumbers(int numbers[], int n, int pilih)
{
    FILE *fptr;
    fptr = fopen("numbers.txt", "a");

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        free(numbers);
        exit(1);
    }

    switch (pilih)
    {
    case 1:
        fprintf(fptr, "SEBELUM DIURUTKAN\n");
        break;
    case 2:
        fprintf(fptr, "\n\nBUBBLE SORT\n");
        break;
    case 3:
        fprintf(fptr, "\n\nSELECTION SORT\n");
        break;
    case 4:
        fprintf(fptr, "\n\nINSERTION SORT\n");
        break;
    default:
        break;
    }

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        free(numbers);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && i % 10 == 0)
        {
            fprintf(fptr, "\n");
        }
        fprintf(fptr, "%d\t", numbers[i]);
    }
    fclose(fptr);
}

int main()
{
    int n = 100000;

    int *numbers = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        numbers[i] = i + 1;
    }

    srand(time(NULL));
    quickShuffle(numbers, n);
    printNumbers(numbers, n, 1);

    int *numbers_copy = malloc(n * sizeof(int));
    memcpy(numbers_copy, numbers, n * sizeof(int));

    clock_t start_bubbleSort = clock();
    bubbleSort(numbers_copy, n);
    clock_t end_bubbleSort = clock();
    printNumbers(numbers_copy, n, 2);

    memcpy(numbers_copy, numbers, n * sizeof(int));
    clock_t start_selectionSort = clock();
    selectionSort(numbers_copy, n);
    clock_t end_selectionSort = clock();
    printNumbers(numbers_copy, n, 3);

    memcpy(numbers_copy, numbers, n * sizeof(int));
    clock_t start_insertionSort = clock();
    insertionSort(numbers_copy, n);
    clock_t end_insertionSort = clock();
    printNumbers(numbers_copy, n, 4);

    double time_taken_bubbleSort = ((double)(end_bubbleSort - start_bubbleSort)) / (CLOCKS_PER_SEC * 60);
    double time_taken_selectionSort = ((double)(end_selectionSort - start_selectionSort)) / (CLOCKS_PER_SEC * 60);
    double time_taken_insertionSort = ((double)(end_insertionSort - start_insertionSort)) / (CLOCKS_PER_SEC * 60);

    printf("+-----------------------+---------------------------+----------------------+\n");
    printf("| Algoritma Pengurutan  | Jumlah Bilangan (n)       | Waktu Eksekusi(detik)|\n");
    printf("+-----------------------+---------------------------+----------------------+\n");
    printf("| Bubble Sort           | %-25d | %-20.6f |\n", n, time_taken_bubbleSort);
    printf("| Selection Sort        | %-25d | %-20.6f |\n", n, time_taken_selectionSort);
    printf("| Insertion Sort        | %-25d | %-20.6f |\n", n, time_taken_insertionSort);
    printf("+-----------------------+---------------------------+----------------------+\n");

    free(numbers);
    free(numbers_copy);

    return 0;
}