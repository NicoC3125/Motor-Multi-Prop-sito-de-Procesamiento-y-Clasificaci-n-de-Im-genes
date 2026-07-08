#ifndef __SORTING_H__
#define __SORTING_H__
#include "util.h"

template <typename T, typename Func>
TI particionar(T* arr, TI first, TI last, Func func) {
    T pivote = arr[last];
    TI i = (first - 1);
    for (TI j = first; j <= last - 1; j++) {
        if (func(arr[j], pivote)) {
            ++i; swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[last]);
    return (i + 1);
}

template <typename T, typename Func>
void QuickSortR(T* arr, TI first, TI last, Func func) {
    if (first < last) {
        TI pi = particionar(arr, first, last, func);
        QuickSortR(arr, first, pi - 1, func);
        QuickSortR(arr, pi + 1, last, func);
    }
}

template <typename T, typename Func>
void quickSort(T* arr, TI n, Func func) {
    if (n <= 1) return;
    QuickSortR(arr, 0, n - 1, func);
}

#endif