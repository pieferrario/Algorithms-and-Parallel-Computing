#include <iostream>

#include "CGSolver.hpp"


CGSolver::CGSolver( const CSRMatrix &matrix, const Rnvector &rhs,
                    const Rnvector &initial_guess,
                    double tolerance, unsigned max_iterations )
    : A( matrix ), b( rhs ), x0( initial_guess ), preconditioner( matrix ),
      tol( tolerance ), max_it( max_iterations ), iterations( 0 ),
      preconditioned( false )
{
    if( A.size() != b.size() || b.size() != x0.size() )
    {
        std::cerr << "Error: dimensions don't agree!" << std::endl;
        exit(1);
    }
    if( !A.is_symmetric() )
    {
        std::cerr << "Error: the matrix A must be symmetric!" << std::endl;
        exit(1);
    }
}

void CGSolver::print() const
{
    std::cout << "Solved using: "
              << ( preconditioned ? "PCG (Jacobi)" : "CG" ) << std::endl;
    std::cout << "Size n              = " << A.size() << std::endl;
    std::cout << "Non-zero entries    = " << A.nnz() << std::endl;
    std::cout << "Tolerance           = " << tol << std::endl;
    std::cout << "Max iterations      = " << max_it << std::endl;
    std::cout << "Iterations          = " << iterations << std::endl;
    if( !residuals.empty() )
        std::cout << "Relative residual   = "
                  << residuals.back() / norm( b ) << std::endl;
}

void CGSolver::save_sol_to_file( const std::string &file_name ) const
{
    std::ofstream output_stream{ file_name };
    if( !output_stream )
    {
        std::cerr << "Cannot open output file: \"" << file_name << "\""
                  << std::endl;
        return;
    }

    output_stream << "Method: " << ( preconditioned ? "PCG" : "CG" )
                  << std::endl;
    output_stream << "Iterations: " << iterations << std::endl;

    // Save the computed solution
    output_stream << "Solution:" << std::endl;
    for( auto val : solution )
        output_stream << val << std::endl;

    // Save residual norms
    output_stream << "Residual norms:" << std::endl;
    for( auto res : residuals )
        output_stream << res << " ";
    output_stream << std::endl;
}

void CGSolver::solve( bool use_preconditioner )
{
    // N.B.: the output members are reset here, so that solve() can be
    // called more than once on the same object
    preconditioned = use_preconditioner;
    solution = x0;
    residuals.clear();
    iterations = 0;

    // Solves A x = b with CG (use_preconditioner == false)
    // or with Jacobi-preconditioned CG (use_preconditioner == true)
    Rnvector r = b - A.multiply(solution);
    Rnvector z, p, q;
    double rho_old, rho_new, alpha, beta;
    if (use_preconditioner)
    {
        z = preconditioner.apply(r);
    }
    else
    {
        z = r;
    }
    p = z;
    rho_old = dot(r, z);
    residuals.push_back(norm(r));

    while (residuals[iterations] > tol * norm(b) and iterations < max_it)
    {
        q = A.multiply(p);
        alpha = rho_old/(dot(p, q));
        solution = solution + alpha * p;
        r = r - alpha * q;
        residuals.push_back(norm(r));

        if (use_preconditioner)
        {
            z = preconditioner.apply(r);
        }
        else
        {
            z = r;
        }

        rho_new = dot(r, z);
        beta = rho_new / rho_old;
        rho_old = rho_new;
        p = z + beta * p;
        ++iterations;

    }
}
