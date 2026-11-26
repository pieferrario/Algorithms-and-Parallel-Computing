//
// Created by Roberto Sala on 27/10/2026.
//

#ifndef ASSIGNMENT2_MANAGER_H
#define ASSIGNMENT2_MANAGER_H

#include <utility>

#include "Airport.h"
#include "Passenger.h"

class Manager {
private:
    FlightID next_flight_id = 0;
    AirportID next_airport_id = 0;
    BookingID next_booking_id = 0;
    PassengerID next_passenger_id = 0;

    std::map<FlightID, std::shared_ptr<Flight>> flights;
    std::map<AirportID, std::shared_ptr<Airport>> airports;
    std::map<BookingID, std::shared_ptr<Booking>> bookings;
    std::map<PassengerID, std::shared_ptr<Passenger>> passengers;

public:
    Manager() = default;

    AirportID add_airport(const std::string& name, const std::string& location);
    PassengerID add_passenger(const std::string& name);

    // Bookings management
    BookingID add_booking(PassengerID passenger_id, const std::vector<FlightID>& flights_to_book, unsigned number_of_passengers);
    bool cancel_booking(BookingID id);

    // Planes management
    FlightID add_flight(AirportID origin, AirportID destination, Timestamp timestamp, Duration duration, unsigned capacity);
    bool take_off_plane(FlightID id);
    bool land_plane(FlightID id);
    bool cancel_plane(FlightID id);

    // Queries
    bool check_booking_request(PassengerID passenger_id, const std::vector<FlightID>& flights_to_book, unsigned number_of_passengers) const;
    std::vector<BookingID> get_passenger_bookings(PassengerID passenger_id) const;
    std::vector<FlightID> find_flights(AirportID origin, AirportID destination) const;
    std::vector<std::vector<FlightID>> find_paths(AirportID origin, AirportID destination, unsigned number_of_passengers, unsigned max_flights = 2) const;

    // Prints
    void print_next_departure_from(AirportID id, unsigned num_departures) const;
    void print_next_arrivals_to(AirportID id, unsigned num_arrivals) const;
    void print_flight(FlightID id) const;
    void print_booking(BookingID id) const;
    void print_passenger(PassengerID id) const;

    void print_report() const;
};


#endif //ASSIGNMENT2_MANAGER_H
