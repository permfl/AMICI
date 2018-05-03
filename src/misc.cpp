#include "amici/misc.h"
#include "amici/amici.h"
#include "amici/symbolic_functions.h"

#include <cstdio>
#include <cstring>
#include <stdarg.h>

namespace amici {

void fillArray(double *destination, int count, double value) {
    for (int i = 0; i < count; ++i)
        destination[i] = value;
}

void zeros(double *destination, int count) {
    memset(destination, 0, sizeof(double) * count);
}

void printArray(double const *array, int numElements) {
    printfArray(array, numElements, "%e\t");
}

void printfArray(double const *array, int numElements, char const *format) {
    for (int i = 0; i < numElements; ++i) {
        printf(format, array[i]);
    }
}

/** Checks the values in an array for NaNs and Infs
 *
 * @param N number of elements in array
 * @param array array
 * @param fun name of calling function
 * @return AMICI_RECOVERABLE_ERROR if a NaN/Inf value was found, AMICI_SUCCESS otherwise
 */
int checkFinite(const int N,const realtype *array, const char* fun){
    for(int idx = 0; idx < N; idx++) {
        if(isNaN(array[idx])) {
            warnMsgIdAndTxt("AMICI:mex:NaN","AMICI encountered a NaN value at index %i of %i in %s! Trying to recover ... ",idx,N,fun);
            return(AMICI_RECOVERABLE_ERROR);
        }
        if(isInf(array[idx])) {
            warnMsgIdAndTxt("AMICI:mex:Inf","AMICI encountered an Inf value at index %i of %i in %s! Trying to recover ... ",idx,N,fun);
            return(AMICI_RECOVERABLE_ERROR);
        }
    }
    return(AMICI_SUCCESS);
}

/**
 * Compute the product over the array entries.
 * T must be numeric.
 */
template <typename T>
T arr_prod(T* arr, int dim) {
	T result = 1;
	for (int j = 0; j < dim; j++) {
		result *= arr[j];
	}
}

/**
 * Compute 1d index for 1d view on nd array.
 *
 * Parameters:
 * @param n   : dimension
 * @param ... : i0, n0, i1, n1, ..., in,
 * 			    where ij denotes index in dim j and nj the size of dim j,
 * 			    must be 2*n-1 additional arguments in total.
 */
int ix_(int n, ...) {
	// initialize variables
	int n_dims = n;
	int n_args = n_dims * 2 - 1;
	int arr_dims[n_dims-1];
	int arr_ixs[n_dims];
	va_list valist;
	n = n_args; // va_start needs n
	va_start(valist, n);

	// process arguments
	for (int j = 0; j  < n_dims - 1; j++) {
		arr_ixs[j] = va_arg(valist, int);
		arr_dims[j] = va_arg(valist, int);
	}
	arr_ixs[n_dims - 1] = va_arg(valist, int);

	// compute result ix
	int ix = 0;
	for (int j = 0; j < n_dims; j++) {
		ix += arr_prod(arr_dims, j) * arr_ixs[j];
	}

	return ix;
}

} // namespace amici
