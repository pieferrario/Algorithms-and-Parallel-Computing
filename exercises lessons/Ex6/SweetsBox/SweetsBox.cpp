//
// Created by abednego on 23/10/25.
//

#include "SweetsBox.hpp"
SweetsBox::SweetsBox(unsigned c) : capacity(c) {}
unsigned SweetsBox::eatContent(int t) {
    int i = 0;
    while (i < t && candies > 0 && cookies > 1) {
        ++i;
        --candies;
        cookies = cookies - 2;
    }
    return candies + cookies;
}
void SweetsBox::refill() {
    candies = capacity/2;
    cookies = capacity - candies;
    std::cout << "Box gets " << candies + cookies << " items" << std::endl;
}
void SweetsBox::print() const {
    std::cout << "Box: " << candies << " - " << cookies << std::endl;
}