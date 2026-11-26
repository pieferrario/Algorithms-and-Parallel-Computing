//
// Created by Roberto Sala on 28/10/2026.
//

#ifndef ASSIGNMENT2_BOOKING_H
#define ASSIGNMENT2_BOOKING_H

#include "Flight.h"
#include <map>

enum class BookingStatus { Confirmed, Canceled };

inline std::ostream& operator<<(std::ostream& out, BookingStatus status) {
    switch (status) {
        case BookingStatus::Confirmed: return out << "Confirmed";
        case BookingStatus::Canceled:  return out << "Canceled";
    }
    return out << "Unknown";
}

class Booking {
private:
    const BookingID ID;
    const PassengerID passenger_ID;
    BookingStatus status = BookingStatus::Confirmed;

    const std::map<FlightID, std::vector<SeatID>> flights;   // flight -> reserved seats

public:
    Booking(BookingID ID, PassengerID passenger_ID, const std::map<FlightID, std::vector<SeatID>>& flights)
        : ID(ID), passenger_ID(passenger_ID), flights(flights) {}
    virtual ~Booking() = default;

    BookingID get_ID() const { return ID; }
    PassengerID get_passenger_ID() const { return passenger_ID; }
    BookingStatus get_status() const { return status; }
    const std::map<FlightID, std::vector<SeatID>>& get_flights() const { return flights; }

    // Returns true only if the booking was Confirmed and is now Canceled.
    bool cancel_booking();

    void print() const;

    virtual unsigned get_number_of_passengers() const = 0;
};


#endif //ASSIGNMENT2_BOOKING_H
