//
// Created by Roberto Sala on 28/10/2026.
//

#include "Booking.h"

bool Booking::cancel_booking() {
    if (status == BookingStatus::Confirmed)
    {
        // std::cout << "The booking was canceled properly" << std::endl;
        status = BookingStatus::Canceled;
        return true;
    }
    // std::cout << "The booking cannot be canceled" <<std::endl;
    return false;
}

void Booking::print() const {
    std::cout << "Booking ID: " << ID << ", status: " << status
              << ", passengers: " << get_number_of_passengers() << std::endl;
    for (const auto& [flight_id, seats] : flights) {
        std::cout << "\t\tflight " << flight_id << ", seats:";
        for (SeatID s : seats) std::cout << " " << s;
        std::cout << std::endl;
    }
}