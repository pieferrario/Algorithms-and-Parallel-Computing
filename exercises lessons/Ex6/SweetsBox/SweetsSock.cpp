//
// Created by abednego on 23/10/25.
//

#include "SweetsSock.hpp"
SweetsSock::SweetsSock(unsigned c) : SweetsBox(c/2) {}
unsigned SweetsSock::eatContent(int t) {
    if (coal != 0) {
        --coal;
    }
    if (candies > t) {
        candies = candies - t;
    } else {
        candies = 0;
    }
    return coal;
}
void SweetsSock::refill() {
    candies = capacity;
    coal = capacity/2;
    std::cout << "Sock gets " << candies + coal << " items" << std::endl;
}
void SweetsSock::print() const {
    std::cout << "Sock: " << candies << " - " << coal << std::endl;
}