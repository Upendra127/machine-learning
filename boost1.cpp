#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> A (3, 3);
    matrix<double> B (3, 3);
    matrix<double> C (3, 3);

    // Fill in matrix A
    for (unsigned i = 0; i < A.size1 (); ++ i)
        for (unsigned j = 0; j < A.size2 (); ++ j)
            A (i, j) = 3 * i + j;

    // Fill in matrix B
    for (unsigned i = 0; i < B.size1 (); ++ i)
        for (unsigned j = 0; j < B.size2 (); ++ j)
            B (i, j) = 3 * i + j;

    // Perform matrix multiplication
    C = prod(A, B);

    // Print the result
    std::cout << C << std::endl;
    return 0;
}
