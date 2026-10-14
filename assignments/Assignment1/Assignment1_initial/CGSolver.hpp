#ifndef CGSOLVER_HPP
#define CGSOLVER_HPP

#include <fstream>
#include <string>

#include "JacobiPreconditioner.hpp"


// Conjugate Gradient solver for A x = b, with A symmetric positive definite
class CGSolver
{
    private:
        // System matrix (n-by-n, symmetric positive definite, CSR format)
        CSRMatrix A;

        // Right-hand side
        Rnvector b;

        // Initial guess x_0
        Rnvector x0;

        // Jacobi preconditioner M = diag(A), built by the constructor
        JacobiPreconditioner preconditioner;

        // Tolerance on the relative residual ||r_k|| / ||b||
        double tol;

        // Maximum number of iterations
        unsigned max_it;

        // x_k -- approximate solution (to be filled by solve())
        Rnvector solution;

        // {||r_k||}_k -- residual norms, k = 0, 1, ... (to be filled by solve())
        std::vector<double> residuals;

        // Number of iterations performed (to be set by solve())
        unsigned iterations;

        // True if the last call to solve() used the preconditioner
        bool preconditioned;

    public:
        // Constructor
        CGSolver( const CSRMatrix &matrix, const Rnvector &rhs,
                  const Rnvector &initial_guess,
                  double tolerance, unsigned max_iterations );

        // Solves A x = b with CG (use_preconditioner == false)
        // or with Jacobi-preconditioned CG (use_preconditioner == true)
        void solve( bool use_preconditioner );

        // Getters
        Rnvector get_solution() const { return solution; }
        std::vector<double> get_residuals() const { return residuals; }
        unsigned get_iterations() const { return iterations; }

        // Prints a summary of the last solve on screen
        void print() const;

        // Saves method, iterations, solution and residual norms in a .txt file
        void save_sol_to_file( const std::string &file_name ) const;
};


#endif // CGSOLVER_HPP
