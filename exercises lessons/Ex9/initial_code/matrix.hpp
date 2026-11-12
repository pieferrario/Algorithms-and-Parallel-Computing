#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

using Dimension = std::size_t;

class Matrix
{
protected:
        Dimension n_rows; // Equivalent to "std::size_t n_rows"
        Dimension n_cols;

    public:
        Matrix (Dimension rows, Dimension cols);
        virtual ~Matrix() = default;

        virtual double operator () (std::size_t i, std::size_t j) const = 0; // get-like implementation. matrix is a virtual class
        virtual double & operator () (std::size_t i, std::size_t j) = 0; // set-like implementation. it returns a reference to an element of the matrix. it is an abstract function.

        const Dimension get_n_cols() const;
        const Dimension get_n_rows() const;


};

#endif /* MATRIX_H_ */
