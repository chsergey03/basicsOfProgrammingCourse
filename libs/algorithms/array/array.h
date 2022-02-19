#ifndef INC_ARRAY_H
#define INC_ARRAY_H

#include <stddef.h>

// вводит массив a размера n.
void inputArray_(int *a, size_t n);

// выводит массив a размера n.
void outputArray_(const int *a, size_t n);

// возвращает значение первого вхождения элемента x
// в массиве a размера n при его наличии, иначе - n.
size_t linearSearch_(const int *a, size_t n, int x);

// возвращает позицию вхождения элемента x в отсортированном
// массиве a размера n при его наличии, иначе - возвращает n.
size_t binarySearch_(const int *a, size_t n, int x);

// возвращает позицию вхождения элемента x в отсортированном
// массиве a размера n (массив хранит значения упорядоченного
// множества) при наличии этого элемента, иначе - возвращает n.
size_t binarySearchOrderedSet_(const int *a, size_t n, int x);

// возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n при отсутствии такого
// элемента возвращает n.
size_t binarySearchMoreOrEqual_(const int *a, size_t n, int x);

// вставляет элемент со значением value в массив a размера
// n на позицию pos.
void insert_(int *a, size_t *n, size_t pos, int value);

// добавляет элемент value в конец массива a размера n.
void append_(int *a, size_t *n, int value);

// удаляет из массива a размера n элемент, находящийся на
// позиции pos, с сохранением порядка оставшихся элементов,
// при этом размер массива уменьшается на единицу.
void deleteByPosSaveOrder_(int *a, size_t *n, size_t pos);

// удаляет из массива a размера n элемент, находящийся на
// позиции pos, без сохранения порядка оставшихся элементов,
// при этом размер массива уменьшается на единицу.
void deleteByPosUnsaveOrder_(int *a, size_t *n, size_t pos);

// возвращает значение ’истина’, если все элементы массива a
// размера n соответствует функции-предикату predicate,
// иначе - ’ложь’.
int all_(const int *a, size_t n, int (*predicate)(int));

// возвращает значение ’истина’, если хотя бы один элемент
// массива a размера n соответствует функции-предикату
// predicate, иначе - ’ложь’.
int any_(const int *a, size_t n, int (*predicate)(int));

// применяет функцию predicate ко всем элементам массива source
// размера n и сохраняет результат в массиве dest размера n.
void forEach_(const int *source, int *dest,
              size_t n, const int (*predicate)(int));

// удаляет из массива a размера n все элементы, удовлетворяющие
// функции-предикату deletePredicate, записывает в n новый размер
// массива.
void deleteIf_(int *a, size_t *n, int(*deletePredicate)(int));

// возвращает количество элементов массива a размера n
// удовлетворяющих функции-предикату predicate.
int countIf_(const int *a, size_t n, int (*predicate)(int));

// возвращает сумму элементов массива a размера n.
int getSum_(const int *a, size_t n);

// возвращает позицию минимального элемента массива
// a размера n в области, начинающейся с позиции pos.
size_t getMinPos_(const int *a, size_t n, size_t pos);

#endif