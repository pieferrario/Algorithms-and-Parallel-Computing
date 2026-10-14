#ifndef CSRMATRIX_HPP
#define CSRMATRIX_HPP

#include "utils.hpp"


// Sparse square matrix of size n-by-n, stored in Compressed Sparse Row format
class CSRMatrix
{
    private:
        // Number of rows (equal to the number of columns)
        std::size_t n;

        // Non-zero entries, stored row by row (and from left to right
        // within each row)
        std::vector<double> values;

        // Column indices: values[k] is the entry in column col_idx[k]
        std::vector<std::size_t> col_idx;

        // Row pointers (n + 1 elements): the entries of row i are
        // values[row_ptr[i]], ..., values[row_ptr[i + 1] - 1]
        std::vector<std::size_t> row_ptr;

    public:
        // Constructor: builds the CSR representation of the dense matrix A,
        // storing only its non-zero entries
        CSRMatrix( const Rnmatrix &A );

        // Number of rows (= number of columns)
        std::size_t size() const { return n; }

        // Number of stored (non-zero) entries
        std::size_t nnz() const { return values.size(); }

        // Returns a_ij (zero if the entry is not stored)
        double get( std::size_t i, std::size_t j ) const;

        // Returns the vector (a_00, a_11, ..., a_{n-1,n-1})
        Rnvector diagonal() const;

        // Returns true if a_ij == a_ji for all i, j
        bool is_symmetric() const;

        // Matrix-vector product: returns y = A x
        Rnvector multiply( const Rnvector &x ) const;
};


#endif // CSRMATRIX_HPP
