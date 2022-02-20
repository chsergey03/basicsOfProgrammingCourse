#ifndef INC_ALGORITHM_H
#define INC_ALGORITHM_H

#include <stddef.h>

// применяется в качестве функции-компаратора
// целочисленных значений типа int для быстрой
// сортировки массива qsort.
int compare_ints(const void *a, const void *b);

// возвращает минимальное из двух значений a и b
// типа size_t.
size_t min2_size_t(size_t a, size_t b);

// обменивает два значения произвольного типа (baseTypeSize
// - размер этого произвольного типа).
void void_swap(void *a, void *b, size_t baseTypeSize);

// возвращает максимальное из двух значений a и b
// типа int.
int max2_int(int a, int b);

#endif