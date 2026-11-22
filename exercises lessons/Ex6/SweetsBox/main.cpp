#include <iostream>

#include "SweetsSock.hpp"

void changeAndPrint(SweetsBox &b);

int main() {

    SweetsBox box1(8);
    SweetsSock sock1(8);

    std::cout << "box1, sock1 output" << std::endl;

    box1.refill();
    box1.eatContent(3);
    box1.print();

    sock1.refill();
    sock1.eatContent(3);
    sock1.print();

    SweetsBox box2(32);
    SweetsSock sock2(32);

    std::cout << "box2, sock2 output" << std::endl;

    changeAndPrint(box2);
    changeAndPrint(sock2);

    }

void changeAndPrint(SweetsBox &b){
    b.refill();
    b.eatContent(1);
    b.print();
}