#ifndef AMICI_MISC_H
#define AMICI_MISC_H

#include "amici/defines.h"

#include<algorithm>


namespace amici {

void zeros(double *destination, int count);

void fillArray(double *destination, int count, double value);

void printArray(double const *array, int numElements);

void printfArray(double const *array, int numElements, char const *format);

int checkFinite(const int N,const realtype *array, const char* fun);

template <typename T>
T product_of_arr(T* arr, int dim);

int ix_(int n, ...);

} // namespace amici
#endif // AMICI_MISC_H
