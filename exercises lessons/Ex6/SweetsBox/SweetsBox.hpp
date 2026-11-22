//
// Created by abednego on 23/10/25.
//

#ifndef SWEETSBOX_SWEETSBOX_HPP
#define SWEETSBOX_SWEETSBOX_HPP


#include <iostream>
class SweetsBox {
private:
    unsigned cookies = 0;
protected:
    unsigned const capacity;
    unsigned candies = 0;
public:
    SweetsBox(unsigned c);
    virtual unsigned eatContent(int t);
    void refill();
    void print() const;
    virtual ~SweetsBox(){};
};



#endif //SWEETSBOX_SWEETSBOX_HPP