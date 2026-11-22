//
// Created by abednego on 23/10/25.
//

#ifndef SWEETSBOX_SWEETSOCK_HPP
#define SWEETSBOX_SWEETSOCK_HPP


#include "SweetsBox.hpp"
class SweetsSock : public SweetsBox {
private:
    unsigned coal = 0;
public:
    SweetsSock(unsigned c);
    unsigned eatContent(int t) override;
    void refill();
    void print() const;
    virtual ~SweetsSock(){};
};

#endif //SWEETSBOX_SWEETSOCK_HPP