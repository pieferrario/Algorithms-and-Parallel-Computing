//
// Created by Roberto Sala on 29/10/2026.
//

#ifndef ASSIGNMENT2_PASSENGER_H
#define ASSIGNMENT2_PASSENGER_H

#include "Booking.h"

class Passenger {
private:
    const PassengerID ID;
    const std::string name;
    std::vector<std::shared_ptr<Booking>> bookings;

public:
    Passenger(PassengerID id, const std::string& name) : ID(id), name(name) {}

    PassengerID get_ID() const { return ID; }
    const std::string& get_name() const { return name; }
    const std::vector<std::shared_ptr<Booking>>& get_bookings() const { return bookings; }

    void add_booking(std::shared_ptr<Booking> booking) { bookings.push_back(booking); }

    void print() const {
        std::cout << "ID: " << ID << ", Name: " << name << std::endl;
    };
};

#endif //ASSIGNMENT2_PASSENGER_H
