#include <limits>
#include <iostream>

#include "block_matrix.hpp"

BlockMatrix::BlockMatrix(): Matrix (0, 0)
{}

void BlockMatrix::add_block(const Block & block)
{
    blocks.push_back(block);
    // Since Block_Matrix inherits from Matrix, we have to modify n_rows and n_cols;
    n_rows = std::max(n_rows, block.get_bottom_right_row() + 1);
    n_cols = std::max(n_cols, block.get_bottom_right_col() + 1);
}

double BlockMatrix::operator () (std::size_t i, std::size_t j) const
{
    // Check if the element i, j is inside the matrix
    if (i >= n_rows or j >= n_cols)
    {
        std::cout << "The element is not in the matrix";
        return std::numeric_limits<double>::quiet_NaN();
    }
    for (const Block & block: blocks)
    {
        // equivalent to
        // for (std::size_t idx = 0; idx < blocks.size(); ++idx){
        //              const Block & block = blocks[idx];}
        if (i >= block.get_top_left_row()
            and i <= block.get_bottom_right_row()
            and j>= block.get_top_left_col()
            and j <= block.get_bottom_right_col())
        {
            return block(i - block.get_top_left_row(), j - block.get_top_left_col());
        }
    }
    return 0;
}

double & BlockMatrix::operator () (std::size_t i, std::size_t j)
{
    for (Block & block : blocks)
    {
        if (i >= block.get_top_left_row()
            and i <= block.get_bottom_right_row()
            and j>= block.get_top_left_col()
            and j <= block.get_bottom_right_col())
        {
            return block(i - block.get_top_left_row(), j - block.get_top_left_col());
        }
    }
    Block new_block(i, j, i, j,{0});
    add_block(new_block);
    return blocks.back()(0,0);
}

