//
// Created by Roberto Sala on 28/10/2026.
//

#ifndef ASSIGNMENT2_GROUPBOOKING_H
#define ASSIGNMENT2_GROUPBOOKING_H

#include "Booking.h"

class GroupBooking : public Booking {
private:
    const unsigned number_of_passengers;

public:
    GroupBooking(BookingID ID, PassengerID passenger_id,
                 const std::map<FlightID, std::vector<SeatID>>& flights, unsigned number_of_passengers):
                    Booking(ID, passenger_id, flights), number_of_passengers(number_of_passengers)  {}

    unsigned get_number_of_passengers() const override { return number_of_passengers; }
};


#endif //ASSIGNMENT2_GROUPBOOKING_H
