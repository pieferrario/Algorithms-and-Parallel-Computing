#ifndef BLOCKMATRIX_H_
#define BLOCKMATRIX_H_

#include <vector>

#include "block.hpp"

class BlockMatrix: public Matrix
{
    private:
        std::vector<Block> blocks = {};

        // helper functions

public:
        BlockMatrix();

        void add_block(const Block & block);

        double & operator () (std::size_t i, std::size_t j) override;

        double operator () (std::size_t i, std::size_t j) const override;
};

#endif /* BLOCKMATRIX_H_ */
