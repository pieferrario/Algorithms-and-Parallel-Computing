#include "JacobiPreconditioner.hpp"


JacobiPreconditioner::JacobiPreconditioner( const CSRMatrix &A )
    : inv_diag( A.diagonal() )
{
    for( std::size_t i = 0; i < inv_diag.size(); i++ )
    {
        if( inv_diag[i] <= 0.0 )
        {
            std::cerr << "Error: the diagonal entries of A must be positive!"
                      << std::endl;
            exit(1);
        }
        inv_diag[i] = 1.0 / inv_diag[i];
    }
}

Rnvector JacobiPreconditioner::apply( const Rnvector &r ) const
{
    Rnvector z( r.size() );
    if( r.size() != inv_diag.size() )
    {
        std::cerr << "Error: dimensions don't agree!" << std::endl;
        return z;
    }
    for( std::size_t i = 0; i < r.size(); i++ )
        z[i] = inv_diag[i] * r[i];
    return z;
}
