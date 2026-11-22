//
// Created by Danilo Ardagna on 02/06/22.
//

#include "Tensor.h"
#include <iostream>
#include <cmath>
#include <limits>

Tensor::Tensor(const index_type& dim) : dimensions(dim) {
    if (dim.empty())
    {
        std::cout << "You cannot initialise an empty tensor" << std::endl;
    }
    if (dim.size() > 3)
    {
        std::cout << "The tensor has 3 dimensions at most" << std::endl;
    }
}

bool Tensor::check_index_coherence(int j, int k) const
{
    // This auxiliary function helps us check whether the indices are coherent
    if (j == -1 and k >= 0)
    {
        return false; // we can't have a tensor with a 3rd dimension and no 2nd dimension
    }

    if (j < -1 or k < -1)
    {
        return false; // -1 is a control value. the tensor is not supposed to have negative indices.
    }
    return true;
}

bool Tensor::check_size(unsigned i, int j, int k) const
    {
        // we have to check that we are not trying to access an element that is not in the tensor.
        index_type idx = make_indices(i,j,k);
        if (idx.size() != dimensions.size())
        {
            return false;
        }
    return true;
    }
bool Tensor::check_admissibility(unsigned i, int j, int k) const
{
    index_type idx = make_indices(i, j, k);
    for (std::size_t d = 0; d < idx.size(); ++d)
        if (idx[d] >= dimensions[d])
            return false;
    return true;
}

bool Tensor::check_indices (unsigned i, int j, int k) const
{
    if (!check_index_coherence(j,k))
        return false;
    if (!check_size(i, j,k))
        return false;
    if (!check_admissibility(i,j,k))
        return false;
    return true;
}

Tensor::index_type Tensor::make_indices(unsigned i, int j, int k) const
{
    // This auxiliary function is used only after the check_indices and creates a proper index_type vector containing the indices
    unsigned j_unsigned = 0;
    unsigned k_unsigned = 0;
    if (j == -1 and k == -1)
    {
        return {i};
    }

    if(k == -1)
        {
            j_unsigned = j;
            return {i,j_unsigned};
        }
    j_unsigned = j;
    k_unsigned = k;
    return {i,j_unsigned,k_unsigned};
}

double Tensor::get(unsigned int i, int j, int k) const {
    // Once again, we check the correctness of the indices first
    if (! check_indices(i, j,k))
    {
        std::cout << "The provided indices are not valid" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    index_type idx = make_indices(i,j,k);
    auto it = values.find(idx);
    if (it == values.cend())
    {
        std::cout << "The desired value was not previously set" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    return it->second;
}

void Tensor::set(double value, unsigned int i, int j, int k)
{
    if (! check_indices(i, j,k))
    {
        std::cout << "The provided indices are not valid" << std::endl;
        return;
    }

    index_type idx = make_indices(i,j,k);
    values[idx] = value;
}

Tensor Tensor::operator*(double alpha) const {
    Tensor result(dimensions);

    // the result of alpha * Tensor is Tensor with each element multiplied by alpha
    for (auto iterator = values.cbegin(); iterator != values.cend(); ++iterator)
    {
        result.values[iterator -> first] = alpha * iterator -> second;
    }
    return result;
}
    /* compute tensor norm.
     * norm_type can be "inf", "euclidean", "2" (same as euclidean), "fro"
     * Note that "fro" can be applied only if the tensor is a bi-dimensional matrix
     * */


double Tensor::compute_infinity_norm() const{
    // the infinity norm for a tensor is the max of the abs values of the tensor's entries
    double norm = 0.0;
    for (auto iterator = values.cbegin(); iterator != values.cend(); ++iterator)
    {
        if (std::abs(iterator -> second) > norm)
        {
            norm = std::abs(iterator -> second);
        }
    }
    return norm;
}

double Tensor::compute_euclidean_norm() const
{
    double sum = 0.0;

    for (auto iterator = values.cbegin(); iterator != values.cend(); ++iterator)
    {
        sum += (iterator -> second) * (iterator -> second);
    }
    return std::sqrt(sum);
}

double Tensor::norm(const std::string& norm_type) const {
    if (norm_type == "inf")
        return compute_infinity_norm();

    if (norm_type == "euclidean" or norm_type == "2") // the euclidean norm for a tensor is the sqrt(sum(entries^2))
        return compute_euclidean_norm();

    if (norm_type == "fro")
    {
        if (dimensions.size() == 2)
        {
            return compute_euclidean_norm();
        }
        else
        {
            std::cout << "Frobenius norm can be computed only on 2 dimensional tensors" << std::endl;
            return std::numeric_limits<double>::quiet_NaN();
        }
    }
    std::cout << "The input type of norm is not valid" << std::endl;
    return std::numeric_limits<double>::quiet_NaN();
}


void Tensor::print() const
{
    for (auto it = values.cbegin(); it != values.cend(); ++it)
        {
            for (auto index : it->first)
                std::cout << index << " ";
            std::cout << ": " << it->second << std::endl;
        }
}


