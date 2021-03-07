#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int comp2 = 0, mov2 = 0;
int comp4 = 0, mov4 = 0;

int cmp1(const void *x1, const void *x2)
{
    return (abs(*(int *)x2) - abs(*(int *)x1));
}

int cmp2(const void *x1, const void *x2)
{
    return (abs(*(int *)x1) - abs(*(int *)x2));
}

void fill(int *a, int n, int p)
{
    srand(time(NULL));
    int i, d = RAND_MAX / 2;
    for (i = 0; i < n; i++)
    {
        a[i] = rand() - d;
    }
    if (p == 1)
    {
        qsort(a, n, sizeof(int), cmp1);
    }
    if (p == 2)
    {
        qsort(a, n, sizeof(int), cmp2);
    }
}

void sort2(int *a, int lng)
{
    int i, bgn = 0, t, imax;
    while (bgn < lng - 1)                               // пока номер сортируемого элемента меньше номера последнего
    {
        int max = bgn;
        for (i = bgn + 1; i < lng; i++)
        {
            if (abs(a[i]) > abs(a[max]))                  // ищем максимальный по модулю элемент
            {
                max = i;
            }
            comp2++;
        }
        if (max != bgn)
        {
            t = a[bgn];                                     // ставим его в конец отсортированной части массива
            a[bgn] = a[max];
            a[max] = t;
            mov2++;
        }
        bgn++;                                          // сдвигаем начало неотсортированной части массива на 1 элемент
    }
    return;
}

void sort4(int *a, int lng)
{
    int left = 0, right = lng - 1;                      // левый и правый указатели помогут отсортировать массив 
                                                        // по невозрастанию модулей относительно "главного" элемента

    int pivot = a[left + (right - left) / 2];           // делаем центральный элемент сортруемой части массива "главным"
    // "главный" элемент до рекурсивного вызова функции должен будет стоять на своём месте в отсортированном массиве
    int l = left;                                       // сохраняем начало сортируемой части массива
    int r = right;                                      // сохраняем конец сортируемой части массива
    int t;
    while (left <= right)                               // выполняем, пока левый и правый указатели не встретятся
    {
        while (abs(a[left]) > abs(pivot))               // ищем слева эл-т, к-рый меньше "главного"
        {
            left++;
            comp4++;
        }
        comp4++;
        while (abs(a[right]) < abs(pivot))              // ищем справа эл-т, к-рый больше "главного"
        {
            right--;
            comp4++;
        }
        comp4++;
        if (left <= right)                              // меняем их местами
        {
            t = a[right];
            a[right] = a[left];
            a[left] = t;
            mov4++;
            left++;
            right--;
        }
    }
    if (right > l) sort4((a + l), right - l + 1);       // когда левый и правый указатели встретились,
    if (r > left) sort4((a + left), r - left + 1);      // вызываем функцию рекурсивно для
                                                        // левой и правой частей массива относительно
                                                        // "главного" элемента
    return;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    int *A;
    A = (int *)calloc(N, sizeof(int));
    int *B;
    B = (int *)calloc(N, sizeof(int));
    int *Check;
    Check = (int *)calloc(N, sizeof(int));
    int i, P;
    scanf("%d", &P);
    fill(A, N, P);
    for (i = 0; i < N; i++)
    {
        //printf("%d\t", A[i]);
        B[i] = A[i];
        Check[i] = A[i];
    }
    //printf("\n"); 
    sort2(A, N);
    sort4(B, N);
    qsort(Check, N, sizeof(int), cmp1);
    for (i = 0; i < N; i++)
    {
        if (abs(A[i]) != abs(Check[i]))
        {
            printf("Неверный ответ\n");
            break;
        }
        //printf("%d\t", A[i]);
    }
    //printf("\n"); 
    printf("%d\t%d\n", comp2, mov2);
    for (i = 0; i < N; i++)
    {
        if (abs(B[i]) != abs(Check[i]))
        {
            printf("Неверный ответ\n");
            break;
        }
        //printf("%d\t", B[i]);
    }
    //printf("\n"); 
    printf("%d\t%d\n", comp4, mov4);
    free(A);
    free(B);
    return 0;
}
