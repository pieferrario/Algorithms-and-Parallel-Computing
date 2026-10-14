#include "utils.hpp"


// Vector sum
Rnvector operator+( const Rnvector &x, const Rnvector &y )
{
    Rnvector z( x.size() );
    if( x.size() != y.size() )
    {
        std::cerr << "Error: vectors must have the same dimension!" << std::endl;
        return z;
    }
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = x[i] + y[i];
    return z;
}


// Vector difference
Rnvector operator-( const Rnvector &x, const Rnvector &y )
{
    Rnvector z( x.size() );
    if( x.size() != y.size() )
    {
        std::cerr << "Error: vectors must have the same dimension!" << std::endl;
        return z;
    }
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = x[i] - y[i];
    return z;
}


// Product by scalar
Rnvector operator*( const double lambda, const Rnvector &x )
{
    Rnvector z( x.size() );
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = lambda * x[i];
    return z;
}


// Scalar product
double dot( const Rnvector &x, const Rnvector &y )
{
    double s = 0.0;
    if( x.size() != y.size() )
    {
        std::cerr << "Error: vectors must have the same dimension!" << std::endl;
        return s;
    }
    for( std::size_t i = 0; i < x.size(); i++ )
        s += x[i] * y[i];
    return s;
}


// Euclidean norm
double norm( const Rnvector &x )
{
    return std::sqrt( dot( x, x ) );
}
