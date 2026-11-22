//
// Created by Danilo Ardagna on 02/06/22.
//

#ifndef TENSORS_TENSOR_H
#define TENSORS_TENSOR_H

#include <vector>
#include <map>
#include <string>

class Tensor {
public:

    typedef std::vector<unsigned> index_type; // Each element of the tensor is accessed through indices (one for each dimension of the tensor).

private:
    std::vector<unsigned> dimensions;
    std::map<index_type, double> values;

    bool check_indices (unsigned i, int j, int k) const;
    bool check_index_coherence(int j, int k) const;
    bool check_size(unsigned i, int j, int k) const;
    bool check_admissibility(unsigned i, int j, int k) const;
    index_type make_indices(unsigned i, int j, int k) const;
    double compute_infinity_norm() const;
    double compute_euclidean_norm() const;

public:

    Tensor(const index_type &dimensions);

    void reshape(index_type new_shape);

    double get(unsigned i, int j=-1, int k= -1) const;

    void set(double value, unsigned i, int j=-1, int k= -1);

    Tensor operator*(double alpha) const;

    /* compute tensor norm.
     * norm_type can be "inf", "euclidean", "2" (same as euclidean), "fro"
     * Note that "fro" can be applied only if the tensor is a bi-dimensional matrix
     * */
    double norm(const std::string& norm_type) const;

    void print() const;

};


#endif //TENSORS_TENSOR_H
