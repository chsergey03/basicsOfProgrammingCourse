#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "tasks_matrix.h"

void swapRowsWithMaxAndMinValuesOfSquareMatrix(matrix *m) {
    matrix m2 = *m;
    assert(isSquareMatrix(m2));

    position minValuePos = getMinValuePos(m2);
    position maxValuePos = getMaxValuePos(m2);

    swapRows(m, minValuePos.rowIndex, maxValuePos.rowIndex);
}

void sortRowsByMaxElements(matrix *m) {
    selectionSortRowsMatrixByRowCriteria(m,
                                         (int (*)(int *, size_t)) getMax_);
}

void sortColsByMinElements(matrix *m) {
    selectionSortColsMatrixByColCriteria(m,
                                         (int (*)(int *, size_t)) getMin_);
}

matrix mulMatrices(const matrix m1, const matrix m2) {
    assert(m1.nCols == m2.nRows);

    matrix mulMatrix = getMemMatrix(m1.nRows, m2.nCols);
    for (size_t i = 0; i < m1.nRows; i++)
        for (size_t j = 0; j < m2.nCols; j++) {
            int matrixElement = 0;
            for (size_t k = 0; k < m1.nCols; k++)
                matrixElement += m1.values[i][k] * m2.values[k][j];
            mulMatrix.values[i][j] = matrixElement;
        }

    return mulMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    assert(isSymmetricMatrix(*m));

    *m = mulMatrices(*m, *m);
}

void transposeIfMatrixHasNotEqualSumsOfRows(matrix *m) {
    assert(isSquareMatrix(*m));

    long long *sumsOfRowsArray = (long long *) malloc(m->nRows *
                                                      sizeof(long long));
    for (size_t i = 0; i < m->nRows; i++) {
        sumsOfRowsArray[i] = getSum_(m->values[i], m->nCols);
    }

    if (isUnique_longLong_(sumsOfRowsArray, m->nRows))
        transposeSquareMatrix(m);
}

bool areMutuallyInverseMatrices(const matrix m1, const matrix m2) {
    matrix mulMatrix = mulMatrices(m1, m2);

    return isEMatrix(mulMatrix);
}

bool isSquareMatrixOfFirstOrder(const matrix m) {
    return m.nRows * m.nCols == 1;
}

long long findSumOfMaxesOfPseudoDiagonals(const matrix m) {
    if (isSquareMatrixOfFirstOrder(m))
        return 0;

    size_t nOfMaxes = m.nRows + m.nCols - 2;
    int *arrayOfMaxes = (int *) malloc(nOfMaxes * sizeof(int));

    size_t iWrite = 0;
    for (size_t i = m.nRows - 1; i > 0; i--) {
        arrayOfMaxes[iWrite] = m.values[i][0];
        iWrite += 1;
    }

    for (size_t j = 1; j < m.nCols; j++) {
        arrayOfMaxes[iWrite] = m.values[0][j];
        iWrite += 1;
    }

    iWrite = nOfMaxes - 2;
    for (size_t i = 1; i < m.nRows; i++) {
        for (size_t j = m.nCols - 1; j > 0; j--) {
            if (i != j) {
                arrayOfMaxes[iWrite] = max2_int(arrayOfMaxes[iWrite],
                                                m.values[i][j]);
                iWrite -= 1;
            }
        }
        iWrite += 1;
    }

    return getSum_(arrayOfMaxes, nOfMaxes);
}

int getMinInArea(matrix m) {
    position maxPos = getMaxValuePos(m);

    int min = m.values[maxPos.rowIndex][maxPos.colIndex];
    size_t i = maxPos.rowIndex - 1;
    size_t j = maxPos.colIndex - 1;
    size_t currentRowLen = 1;
    while (i < m.nRows && j < m.nRows) {
        if (m.nCols - currentRowLen >= 2)
            currentRowLen += 2;
        else if (m.nCols - currentRowLen == 1)
            currentRowLen += 1;

        for (size_t k = j; k < currentRowLen; k++)
            if (m.values[i][k] < min)
                min = m.values[i][k];

        if (i > 0)
            i -= 1;
        else
            i = m.nRows;

        if (j > 0)
            j -= 1;
        else
            j = m.nCols;
    }

    return min;
}

float getDistance(const int *const a,
                  const size_t n) {
    int sumOfSquares = 0;
    for (size_t i = 0; i < n; i++)
        sumOfSquares += a[i] * a[i];

    return sqrtf((float) sumOfSquares);
}

float getArithmeticMean(const int *const a,
                        const size_t n) {
    long long sum = getSum_(a, n);

    return (float) sum / (float) n;
}

void selectionSortRowsMatrixByRowCriteriaF(matrix *m,
                                           float (*criteria)(int *, size_t)) {
    float *criteriaValueArray = (float *) malloc(m->nRows *
                                                 sizeof(float));

    for (size_t i = 0; i < m->nRows; i++) {
        criteriaValueArray[i] = criteria(m->values[i], m->nCols);
    }

    for (size_t i = 0; i < m->nRows; i++) {
        size_t minPos = getMinPos_float_(criteriaValueArray, m->nRows, i);
        void_swap(&criteriaValueArray[i],
                  &criteriaValueArray[minPos],
                  sizeof(float));
        swapRows(m, i, minPos);
    }

    free(criteriaValueArray);
}

void sortByDistances(matrix *m) {
    selectionSortRowsMatrixByRowCriteriaF(m,
                                          (float (*)(int *, size_t)) getDistance);
}

int countOfRowsWithUniqueSumOfElements(const long long *const a,
                                       const size_t n) {
    int count = 0;
    long long currentSum = a[0];
    int basicLen = 1;
    int lenOfEqualValuesSequence = basicLen;
    int lenOfRowsWithUniqueRowSumSequence = 1;
    for (size_t i = 1; i < n; i++) {
        if (a[i] != currentSum) {
            currentSum = a[i];
            count += lenOfEqualValuesSequence == basicLen;
            lenOfEqualValuesSequence = basicLen;
            lenOfRowsWithUniqueRowSumSequence += 1;
        } else {
            lenOfEqualValuesSequence += 1;
            lenOfRowsWithUniqueRowSumSequence -= lenOfRowsWithUniqueRowSumSequence > 0;
        }

    }

    return lenOfRowsWithUniqueRowSumSequence == n ? (int) n : count;
}

int countOfClassesOfEqRowsByRowSum(const matrix m) {
    long long *arrayOfRowsSum = (long long *) malloc(m.nRows *
                                                     sizeof(long long));

    for (size_t i = 0; i < m.nRows; i++)
        arrayOfRowsSum[i] = getSum_(m.values[i], m.nCols);

    qsort(arrayOfRowsSum, m.nRows,
          sizeof(long long), compare_longLong);

    int nRowsWithUniqueSumOfElements = countOfRowsWithUniqueSumOfElements(arrayOfRowsSum,
                                                                          m.nRows);

    long long currentRowSum = arrayOfRowsSum[0];
    int nClasses = 1;
    for (size_t i = 1; i < m.nRows; i++) {
        if (arrayOfRowsSum[i] > currentRowSum) {
            currentRowSum = arrayOfRowsSum[i];
            nClasses += 1;
        }
    }

    return nClasses - nRowsWithUniqueSumOfElements;
}

int getCountOfSpecialElements(const matrix m) {
    long long *arrayOfColsSum = (long long *) malloc(m.nRows *
                                                     sizeof(long long));
    int *currentCol = (int *) malloc(m.nRows * sizeof(int));

    for (size_t j = 0; j < m.nCols; j++) {
        copyElementsOfColToArray(currentCol, &m, j);
        arrayOfColsSum[j] = getSum_(currentCol, m.nRows);
    }

    int count = 0;
    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = 0; j < m.nCols; j++)
            if (2 * m.values[i][j] > arrayOfColsSum[j])
                count += 1;

    return count;
}