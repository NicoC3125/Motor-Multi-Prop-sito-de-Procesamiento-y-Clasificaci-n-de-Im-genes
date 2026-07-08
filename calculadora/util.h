#ifndef __UTIL_H__
#define __UTIL_H__

#include "types.h"

const T2 PI = 3.14159265358979;

template <typename T>
bool Mayor(T a, T b) { return a > b; }

template <typename T>
bool Menor(T a, T b) { return a < b; }

template <typename T>
T Max(T a, T b) { return a > b ? a : b; }

template <typename T>
bool Igual(T a, T b) { return a == b; }

#endif