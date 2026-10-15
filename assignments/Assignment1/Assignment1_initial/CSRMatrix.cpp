#include "CSRMatrix.hpp"


CSRMatrix::CSRMatrix( const Rnmatrix &A )
    : n( A.size() ), row_ptr( A.size() + 1, 0 )
{
    // Constructor: builds the CSR representation of the dense matrix A,
    // storing only its non-zero entries
    for (std::size_t row = 0; row < n; ++row)
    {
        for (std::size_t col = 0; col < n; ++col)
        {
            if (A[row][col] != 0.0)
            {
                values.push_back(A[row][col]);
                col_idx.push_back(col);
            }
        }
        row_ptr[row + 1] = values.size();
    }
}

double CSRMatrix::get( std::size_t i, std::size_t j ) const
{
    for( std::size_t k = row_ptr[i]; k < row_ptr[i + 1]; k++ )
        if( col_idx[k] == j )
            return values[k];
    return 0.0;
}

Rnvector CSRMatrix::diagonal() const
{
    Rnvector d( n );
    for( std::size_t i = 0; i < n; i++ )
        d[i] = get( i, i );
    return d;
}

bool CSRMatrix::is_symmetric() const
{
    for( std::size_t i = 0; i < n; i++ )
        for( std::size_t k = row_ptr[i]; k < row_ptr[i + 1]; k++ )
            if( values[k] != get( col_idx[k], i ) )
                return false;
    return true;
}

Rnvector CSRMatrix::multiply( const Rnvector &x ) const
{
    Rnvector y( n, 0.0 );
    if( x.size() != n )
    {
        std::cerr << "Error: dimensions don't agree!" << std::endl;
        return y;
    }

    // Matrix-vector product: returns y = A x
    for (std::size_t idx = 0; idx < n; idx++)
    {
        for (std::size_t k = row_ptr[idx]; k < row_ptr[idx + 1]; ++k)
        {
            y[idx] += values[k] * x[col_idx[k]];
        }
    }

    return y;
}
