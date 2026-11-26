//
// Created by Roberto Sala on 26/10/2026.
//


#include "Flight.h"

Flight::Flight(FlightID ID, AirportID origin, AirportID destination, Timestamp timestamp, Duration duration, unsigned capacity):
    ID(ID), origin(origin), destination(destination), timestamp(timestamp), duration(duration), capacity(capacity)
{
    for (SeatID idx = 0; idx < capacity; ++idx)
    {
        free_seats.insert(idx);
    }

    // std::cout << "There are " << capacity << " free seats" << std::endl;

}

bool Flight::depart() {
    if (status == FlightStatus::Scheduled)
    {
    //    std::cout << "The transition '" << status << " -> Departed' is allowed and performed correctly" << std::endl;
        status = FlightStatus::Departed;
        return true;
    }
    // std::cout << "The transition '" << status << " -> Departed' is not allowed and was not performed" << std::endl;
    return false;
}

bool Flight::arrive() {
    if (status == FlightStatus::Departed)
    {
    //    std::cout << "The transition '" << status << " -> Arrived' is allowed and performed correctly" << std::endl;
        status = FlightStatus::Arrived;
        return true;
    }
    // std::cout << "The transition '" << status << " -> Arrived' is not allowed and was not performed" << std::endl;
    return false;
}

bool Flight::cancel() {
    if (status == FlightStatus::Scheduled)
    {
    //    std::cout << "The transition '" << status << " -> Canceled' is allowed and performed correctly" << std::endl;
        status = FlightStatus::Canceled;
        return true;
    }
    // std::cout << "The transition '" << status << " -> Canceled' is not allowed and was not performed" << std::endl;
    return false;
}

std::vector<SeatID> Flight::book(unsigned num_seats, PassengerID passenger)
{
    if (! is_bookable())
    {
    //    std::cout << "The flight is not bookable" << std::endl;
        return {};
    }
    if (num_seats == 0)
    {
    //    std::cout << "Invalid number of requested seats" << std::endl;
        return {};
    }
    if (! check_availability(num_seats))
    {
    //    std::cout << "There are not enough seats available on this flight" << std::endl;
        return {};
    }
    std::vector<SeatID> booked_seats = {};
    SeatID first_free_seat;

    for (unsigned idx = 0; idx < num_seats; ++idx)
    {
        first_free_seat = *free_seats.begin();
        occupied[first_free_seat] = passenger;
        booked_seats.push_back(first_free_seat);
        free_seats.erase(first_free_seat);
    }
    return booked_seats;
}

void Flight::release(const std::vector<SeatID>& seats) {
    for (SeatID seat : seats)
    {
        if (occupied.erase(seat))
        {
            // std::cout << "Seat " << seat << " was once occupied and now released" << std::endl;
            free_seats.insert(seat);
        }
    }
}

void Flight::print() const {
    std::cout << "ID: " << ID << ", status: " << status
              << ", departure time: " << timestamp
              << ", arrival time: " << get_arrival_time()
              << ", available seats: " << available_seats() << std::endl;
}
