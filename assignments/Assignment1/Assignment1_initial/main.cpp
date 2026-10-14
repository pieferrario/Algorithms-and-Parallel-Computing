#include <iostream>
#include <string>

#include "CGSolver.hpp"


void run_test( std::string const & method_name, std::string const & test_number )
{
    // =========================================================================
    // INITIALIZATION OF TEST DEPENDENT DATA
    // =========================================================================

    std::size_t n = 50;
    Rnmatrix A( n, Rnvector( n, 0.0 ) );
    Rnvector b( n );
    Rnvector initial_guess( n, 0.0 );

    // Test 1: well-scaled system
    // A is tridiagonal with a_ii in {4, 4.5, 5} and a_i,i+1 = a_i+1,i = -1
    if ( test_number == "1" )
    {
        std::cout << std::endl << "Running Test 1" << std::endl << std::endl;
        for( std::size_t i = 0; i < n; i++ )
        {
            A[i][i] = 4.0 + 0.5 * static_cast<double>( i % 3 );
            if( i + 1 < n )
            {
                A[i][i + 1] = -1.0;
                A[i + 1][i] = -1.0;
            }
            b[i] = 1.0;
        }
    }

    // Test 2: badly scaled system
    // A = D T D, with T tridiagonal (4 on the diagonal, -1 off the diagonal)
    // and D diagonal with d_i = 3^(i/(n-1)), so that 1 <= d_i <= 3.
    // The right-hand side is chosen so that the exact solution is (1,...,1).
    else if ( test_number == "2" )
    {
        std::cout << std::endl << "Running Test 2" << std::endl << std::endl;
        Rnvector d( n );
        for( std::size_t i = 0; i < n; i++ )
            d[i] = std::pow( 3.0, static_cast<double>( i ) /
                                   static_cast<double>( n - 1 ) );
        for( std::size_t i = 0; i < n; i++ )
        {
            A[i][i] = 4.0 * d[i] * d[i];
            if( i + 1 < n )
            {
                A[i][i + 1] = -d[i] * d[i + 1];
                A[i + 1][i] = -d[i] * d[i + 1];
            }
        }
        for( std::size_t i = 0; i < n; i++ )
            for( std::size_t j = 0; j < n; j++ )
                b[i] += A[i][j];
    }

    else
    {
        std::cerr << "Unknown test. Aborting..." << std::endl;
        exit(1);
    }


    // =========================================================================
    // INITIALIZATION OF THE SOLVER
    // =========================================================================

    double tolerance = 1e-7;
    unsigned max_iterations = 500;
    bool use_preconditioner;

    if ( method_name == "CG" )
        use_preconditioner = false;
    else if ( method_name == "PCG" )
        use_preconditioner = true;
    else
    {
        std::cerr << "Unknown method. Aborting..." << std::endl;
        exit(1);
    }

    // The solver works on the CSR representation of A
    CSRMatrix A_csr( A );
    CGSolver solver( A_csr, b, initial_guess, tolerance, max_iterations );

    // =========================================================================
    // SOLUTION
    // =========================================================================

    // Chrono starts
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Solution
    solver.solve( use_preconditioner );

    // Chrono ends
    high_resolution_clock::time_point t2 = high_resolution_clock::now();


    // =========================================================================
    // POSTPROCESSING
    // =========================================================================

    // Compute duration of the solution process
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    // Prints solver summary on screen
    solver.print();

    // Prints duration of the solution process
    std::cout << "Solution time: " << duration << " μs" << std::endl;

    // Saves solution to file_name
    std::string file_name = "solution_" + test_number + "_"
                                        + method_name + ".txt";
    solver.save_sol_to_file( file_name );
    std::cout << "Saved solution to file " << file_name << std::endl
        << std::endl << std::endl;
}


int main()
{
    run_test( "CG", "1" );
    run_test( "PCG", "1" );
    run_test( "CG", "2" );
    run_test( "PCG", "2" );
    return 0;
}
