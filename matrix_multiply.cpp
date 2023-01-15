#include <iostream>
#include <numpy/arrayobject.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

void matrix_multiply(double *A, double *B, double *C, int rows, int cols) {
    using namespace boost::numeric::ublas;
    matrix<double> matA(rows, cols);
    matrix<double> matB(rows, cols);
    matrix<double> matC(rows, cols);
    for (unsigned i = 0; i < rows; ++ i)
        for (unsigned j = 0; j < cols; ++ j)
            matA(i, j) = A[i*cols + j];
    for (unsigned i = 0; i < rows; ++ i)
        for (unsigned j = 0; j < cols; ++ j)
            matB(i, j) = B[i*cols + j];
    matC = prod(matA, matB);
    for (unsigned i = 0; i < rows; ++ i)
        for (unsigned j = 0; j < cols; ++ j)
            C[i*cols + j] = matC(i, j);
}

int main () {
    // Declare matrix dimensions
    int rows, cols;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    Py_Initialize();
    import_array();
    npy_intp dims[2] = {rows,cols};
    PyObject *A_obj = PyArray_SimpleNew(2, dims, NPY_DOUBLE);
    double *A = (double *) PyArray_DATA(A_obj);

    PyObject *B_obj = PyArray_SimpleNew(2, dims, NPY_DOUBLE);
    double *B = (double *) PyArray_DATA(B_obj);

    // Fill in matrix A and B
    for (unsigned i = 0; i < rows; ++ i)
        for (unsigned j = 0; j < cols; ++ j)
            A[i*cols + j] = 3 * i + j;
    for (unsigned i = 0; i < rows; ++ i)
        for (unsigned j = 0; j < cols; ++ j)
            B[i*cols + j] = 3 * i + j;

    // Perform matrix multiplication
    PyObject *C_obj = PyArray_SimpleNew(2, dims, NPY_DOUBLE);
    double *C = (double *) PyArray_DATA(C_obj);
    matrix_multiply(A, B, C, rows, cols);

    // Print the result
    for (unsigned i = 0; i < rows; ++ i) {
        for (unsigned j = 0; j < cols; ++ j)
            std::cout << C[i*cols + j]
