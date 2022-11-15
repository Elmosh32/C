/** imports **/
#include <stdio.h>
#include <time.h>

#include "ADTDefs.h"
#include "vector.h"
#include "sorting.h"

int main()
{
        int i;
        Vector *vec1b, *vec2b, *vec3b;
        Vector *vec1s, *vec2s, *vec3s;
        Vector *vec1i, *vec2i, *vec3i;
        Vector *vec1q, *vec2q, *vec3q;
        Vector *vec1sel, *vec2sel, *vec3sel;
        Vector *vec1shell, *vec2shell, *vec3shell;
        Vector *vec1m, *vec2m, *vec3m;
        Vector *vec1c, *vec2c, *vec3c;

        int num;
        clock_t start_t, end_t;
        double totalBubble, totalShake, totalInsertion, totalQuick;
        double totalSelection, totalShell, totalMerge, totalCount, dif;

        vec1b = VectorCreate(20000,20000);
        vec1s = VectorCreate(20000,20000);
        vec1i = VectorCreate(20000,20000);
        vec1q = VectorCreate(20000,20000);
        vec1sel = VectorCreate(20000,20000);
        vec1shell = VectorCreate(20000,20000);
        vec1m = VectorCreate(20000,20000);
        vec1c = VectorCreate(20000,20000);

        vec2b = VectorCreate(40000,40000);
        vec2s = VectorCreate(40000,40000);
        vec2i = VectorCreate(40000,40000);
        vec2q = VectorCreate(40000,40000);
        vec2sel = VectorCreate(40000,40000);
        vec2shell = VectorCreate(40000,40000);
        vec2m = VectorCreate(40000,40000);
        vec2c = VectorCreate(40000,40000);

        vec3b = VectorCreate(60000,60000);
        vec3s = VectorCreate(60000,60000);
        vec3i = VectorCreate(60000,60000);
        vec3q = VectorCreate(60000,60000);
        vec3sel = VectorCreate(60000,60000);
        vec3shell = VectorCreate(60000,60000);
        vec3m = VectorCreate(60000,60000);
        vec3c = VectorCreate(60000,60000);

        for (i = 0; i < 20000; i++) {
                num = rand() % 18000;
                VectorAdd(vec1q,num);
                VectorAdd(vec1i,num);
                VectorAdd(vec1s,num);
                VectorAdd(vec1b,num);
                VectorAdd(vec1sel,num);
                VectorAdd(vec1shell, num);
                VectorAdd(vec1m, num);
                VectorAdd(vec1c, num);
        }

        for (i = 0; i < 40000; i++) {
                num = rand() % 36000;
                VectorAdd(vec2q,num);
                VectorAdd(vec2i,num);
                VectorAdd(vec2s,num);
                VectorAdd(vec2b,num);
                VectorAdd(vec2sel,num);
                VectorAdd(vec2shell,num);
                VectorAdd(vec2m, num);
                VectorAdd(vec2c, num);
        }

        for (i = 0; i < 60000; i++) {
                num = rand() % 54000;
                VectorAdd(vec3q,num);
                VectorAdd(vec3i,num);
                VectorAdd(vec3s,num);
                VectorAdd(vec3b,num);
                VectorAdd(vec3sel,num);
                VectorAdd(vec3shell,num);
                VectorAdd(vec3m, num);
                VectorAdd(vec3c, num);
        }

        printf("\n***************************************************************\n"
               "                         20K items                               \n"
               "***************************************************************\n");
        start_t = clock();
        CountingSort(vec1c);
        end_t = clock();
        totalCount = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Counting Sort total time: %f\n", totalCount);

        start_t = clock();
        MergeSort(vec1m);
        end_t = clock();
        totalMerge = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Merge Sort total time: %.3f\n", totalMerge);

        start_t = clock();
        shellSort(vec1shell);
        end_t = clock();
        totalShell = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shell Sort total time: %.3f\n", totalShell);

        start_t = clock();
        selectionSort(vec1sel);
        end_t = clock();
        totalSelection = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Selection Sort total time: %.2f\n", totalSelection);

        start_t = clock();
        QuickSort(vec1q);
        end_t = clock();
        totalQuick = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Quick sort total time: %.3f\n", totalQuick);

        start_t = clock();
        InsertionSort(vec1i);
        end_t = clock();
        totalInsertion = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Insertion sort total time: %.2f\n", totalInsertion);

        start_t = clock();
        shakeSort(vec1s);
        end_t = clock();
        totalShake = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shake sort total time: %.2f\n", totalShake);

        start_t = clock();
        bubbleSort(vec1b);
        end_t = clock();
        totalBubble = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Bubble sort total time: %.2f\n", totalBubble);

        dif = ((totalCount - totalBubble) / totalBubble) * -100;
        printf("\nCounting sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalMerge - totalBubble) / totalBubble) * -100;
        printf("Merge sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShell - totalBubble) / totalBubble) * -100;
        printf("Shell sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalSelection - totalBubble) / totalBubble) * -100;
        printf("Selection sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalQuick - totalBubble) / totalBubble) * -100;
        printf("Quick sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalInsertion - totalBubble) / totalBubble) * -100;
        printf("Insertion sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShake - totalBubble) / totalBubble) * -100;
        printf("Shake sort took %.2f%% less time than bubble sort.\n", dif);



        printf("\n***************************************************************\n"
               "                         40K items                               \n"
               "***************************************************************\n");
        start_t = clock();
        CountingSort(vec2c);
        end_t = clock();
        totalCount = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Counting Sort total time: %f\n", totalCount);

        start_t = clock();
        MergeSort(vec2m);
        end_t = clock();
        totalMerge = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Merge Sort total time: %.3f\n", totalMerge);

        start_t = clock();
        shellSort(vec2shell);
        end_t = clock();
        totalShell = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shell Sort total time: %.3f\n", totalShell);

        start_t = clock();
        selectionSort(vec2sel);
        end_t = clock();
        totalSelection = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Selection Sort total time: %.2f\n", totalSelection);

        start_t = clock();
        QuickSort(vec2q);
        end_t = clock();
        totalQuick = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Quick sort total time: %.2f\n", totalQuick);

        start_t = clock();
        InsertionSort(vec2i);
        end_t = clock();
        totalInsertion = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Insertion sort total time: %.2f\n", totalInsertion);

        start_t = clock();
        shakeSort(vec2s);
        end_t = clock();
        totalShake = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shake sort total time: %.2f\n", totalShake);

        start_t = clock();
        bubbleSort(vec2b);
        end_t = clock();
        totalBubble = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Bubble sort total time: %.2f\n", totalBubble);

        dif = ((totalCount - totalBubble) / totalBubble) * -100;
        printf("\nCounting sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalMerge - totalBubble) / totalBubble) * -100;
        printf("Merge sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShell - totalBubble) / totalBubble) * -100;
        printf("Shell sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalSelection - totalBubble) / totalBubble) * -100;
        printf("Selection sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalQuick - totalBubble) / totalBubble) * -100;
        printf("Quick sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalInsertion - totalBubble) / totalBubble) * -100;
        printf("Insertion sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShake - totalBubble) / totalBubble) * -100;
        printf("Shake sort took %.2f%% less time than bubble sort.\n", dif);


        printf("\n***************************************************************\n"
               "                         60K items                               \n"
               "***************************************************************\n");
        start_t = clock();
        CountingSort(vec3c);
        end_t = clock();
        totalCount = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Counting Sort total time: %f\n", totalCount);

        start_t = clock();
        MergeSort(vec3m);
        end_t = clock();
        totalMerge = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Merge Sort total time: %.3f\n", totalMerge);

        start_t = clock();
        shellSort(vec3shell);
        end_t = clock();
        totalShell = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shell Sort total time: %.3f\n", totalShell);

        start_t = clock();
        selectionSort(vec3sel);
        end_t = clock();
        totalSelection = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Selection Sort total time: %.2f\n", totalSelection);

        start_t = clock();
        QuickSort(vec3q);
        end_t = clock();
        totalQuick = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Quick sort total time: %.2f\n", totalQuick);


        start_t = clock();
        InsertionSort(vec3i);
        end_t = clock();
        totalInsertion = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Insertion sort total time: %.2f\n", totalInsertion);

        start_t = clock();
        shakeSort(vec3s);
        end_t = clock();
        totalShake = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Shake sort total time: %.2f\n", totalShake);

        start_t = clock();
        bubbleSort(vec3b);
        end_t = clock();
        totalBubble = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Bubble sort total time: %.2f\n", totalBubble);

        dif = ((totalCount - totalBubble) / totalBubble) * -100;
        printf("\nCounting sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalMerge - totalBubble) / totalBubble) * -100;
        printf("Merge sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShell - totalBubble) / totalBubble) * -100;
        printf("Shell sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalSelection - totalBubble) / totalBubble) * -100;
        printf("Selection sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalQuick - totalBubble) / totalBubble) * -100;
        printf("Quick sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalInsertion - totalBubble) / totalBubble) * -100;
        printf("Insertion sort took %.2f%% less time than bubble sort.\n", dif);

        dif = ((totalShake - totalBubble) / totalBubble) * -100;
        printf("Shake sort took %.2f%% less time than bubble sort.\n", dif);

        return 0;
}
