#include "matrix.hpp"

Matrix::Matrix (Dimension rows, Dimension cols): n_rows (rows), n_cols (cols){}

// We don't have to implement the virtual = 0 methods.

const Dimension Matrix::get_n_cols() const
{
    return n_cols;
}
const Dimension Matrix::get_n_rows() const
{
    return n_rows;
}