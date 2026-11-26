//
// Created by Roberto Sala on 26/10/2026.
//

#ifndef ASSIGNMENT2_FLIGHT_H
#define ASSIGNMENT2_FLIGHT_H

#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <cstdint>
#include <memory>
#include <string>

enum class FlightStatus { Scheduled, Departed, Arrived, Canceled };

inline std::ostream& operator<<(std::ostream& out, FlightStatus status) {
    switch (status) {
        case FlightStatus::Scheduled: return out << "Scheduled";
        case FlightStatus::Departed:  return out << "Departed";
        case FlightStatus::Arrived:   return out << "Arrived";
        case FlightStatus::Canceled:  return out << "Canceled";
    }
    return out << "Unknown";
}

using FlightID = int;
using AirportID = int;
using BookingID = int;
using SeatID = unsigned;
using PassengerID = unsigned;
using Duration = std::int64_t;
using Timestamp = std::int64_t;

class Flight {
private:
    const FlightID ID;
    FlightStatus status = FlightStatus::Scheduled;
    const AirportID origin;
    const AirportID destination;
    const Timestamp timestamp;
    const Duration duration;
    const unsigned capacity;

    std::set<SeatID> free_seats;
    std::map<SeatID, PassengerID> occupied;     // seat -> passenger

public:
    Flight(FlightID ID, AirportID origin, AirportID destination,
           Timestamp timestamp, Duration duration, unsigned capacity);

    // State transitions: return true only if the transition happened.
    bool depart();
    bool arrive();
    bool cancel();

    FlightID get_ID() const { return ID; }
    FlightStatus get_status() const { return status; }
    AirportID get_origin() const { return origin; }
    AirportID get_destination() const { return destination; }
    Timestamp get_timestamp() const { return timestamp; }
    Duration get_duration() const { return duration; }
    Timestamp get_arrival_time() const { return timestamp + duration; }
    const std::map<SeatID, PassengerID> & get_occupied() const { return occupied; }

    bool is_bookable() const { return status == FlightStatus::Scheduled; }
    unsigned available_seats() const { return free_seats.size(); }
    bool check_availability(unsigned num_seats) const { return num_seats <= available_seats(); }

    // Returns the reserved seats, or an empty vector if the flight cannot be booked.
    std::vector<SeatID> book(unsigned num_seats, PassengerID passenger);
    void release(const std::vector<SeatID>& seats);

    void print() const;
};

#endif //ASSIGNMENT2_FLIGHT_H
