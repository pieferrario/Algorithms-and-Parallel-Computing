#ifndef JACOBIPRECONDITIONER_HPP
#define JACOBIPRECONDITIONER_HPP

#include "CSRMatrix.hpp"


// Jacobi (diagonal) preconditioner M = diag(A)
class JacobiPreconditioner
{
    private:
        // Inverse of the diagonal entries: inv_diag[i] = 1 / a_ii
        Rnvector inv_diag;

    public:
        // Constructor: extracts and inverts the diagonal of A
        // (a_ii > 0 holds for every SPD matrix)
        JacobiPreconditioner( const CSRMatrix &A );

        // Applies the preconditioner: returns z = M^{-1} r,
        // i.e., z_i = r_i / a_ii
        Rnvector apply( const Rnvector &r ) const;
};


#endif // JACOBIPRECONDITIONER_HPP
