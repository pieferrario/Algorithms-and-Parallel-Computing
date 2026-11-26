//
// Created by Roberto Sala on 26/10/2026.
//

#ifndef ASSIGNMENT2_AIRPORT_H
#define ASSIGNMENT2_AIRPORT_H

#include <string>
#include <map>
#include "Flight.h"

class Airport {
private:
    const AirportID ID;
    const std::string name;
    const std::string location;

    std::multimap <Timestamp, std::shared_ptr<Flight>> arrivals; // arrival_time -> flight
    std::multimap <Timestamp, std::shared_ptr<Flight>> departures; // departure_time -> flight

public:
    Airport(AirportID ID, const std::string& name, const std::string& location)
        : ID(ID), name(name), location(location) {}

    AirportID get_ID() const { return ID; }
    const std::string& get_name() const { return name; }
    const std::string& get_location() const { return location; }

    void add_departure(const std::shared_ptr<Flight>& flight);
    void add_arrival(const std::shared_ptr<Flight>& flight);
    std::vector<std::shared_ptr<Flight>> next_departures(unsigned num_departures) const;
    std::vector<std::shared_ptr<Flight>> next_arrivals(unsigned num_arrivals) const;
};

#endif //ASSIGNMENT2_AIRPORT_H
