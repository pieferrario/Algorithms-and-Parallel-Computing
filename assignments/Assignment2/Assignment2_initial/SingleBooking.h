//
// Created by Roberto Sala on 28/10/2026.
//

#ifndef ASSIGNMENT2_SINGLEBOOKING_H
#define ASSIGNMENT2_SINGLEBOOKING_H

#include "Booking.h"

class SingleBooking : public Booking {
public:
    SingleBooking(BookingID ID, PassengerID passenger_ID, const std::map<FlightID, std::vector<SeatID>>& flights)
        : Booking(ID, passenger_ID, flights)  {}

    unsigned get_number_of_passengers() const override { return 1; }
};


#endif //ASSIGNMENT2_SINGLEBOOKING_H
