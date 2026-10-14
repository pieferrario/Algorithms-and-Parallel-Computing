#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std::chrono;


typedef std::vector<double> Rnvector;

// Dense matrix: A[i][j] is the entry in row i and column j
typedef std::vector<Rnvector> Rnmatrix;


// Vector operations (component-wise)
// Computes the sum of two vectors
Rnvector operator+( const Rnvector &x, const Rnvector &y );

// Computes the difference of two vectors
Rnvector operator-( const Rnvector &x, const Rnvector &y );

// Computes the product of a scalar and a vector
Rnvector operator*( const double lambda, const Rnvector &x );

// Computes the scalar product x^T y
double dot( const Rnvector &x, const Rnvector &y );

// Computes the Euclidean norm ||x||_2 = sqrt(x^T x)
double norm( const Rnvector &x );


#endif //UTILS_HPP
