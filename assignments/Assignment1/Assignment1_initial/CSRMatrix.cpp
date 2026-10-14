#include "CSRMatrix.hpp"


CSRMatrix::CSRMatrix( const Rnmatrix &A )
    : n( A.size() ), row_ptr( A.size() + 1, 0 )
{
    // Your code goes here
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

    // Your code goes here

    return y;
}
