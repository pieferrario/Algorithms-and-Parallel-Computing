//
// Created by Roberto Sala on 26/10/2026.
//

#include "Airport.h"

void Airport::add_departure(const std::shared_ptr<Flight>& flight) {
    departures.insert({flight -> get_timestamp(), flight});
}

void Airport::add_arrival(const std::shared_ptr<Flight>& flight) {
    arrivals.insert({flight -> get_arrival_time(), flight});
}

std::vector<std::shared_ptr<Flight>> Airport::next_departures(unsigned num_departures) const {
    if (num_departures == 0)
    {
        // std::cout << "Invalid number of requested next departures" << std::endl;
        return {};
    }
    std::vector<std::shared_ptr<Flight>> result;
    for (const auto & [time, flight] : departures)
    {
        if (flight -> get_status() == FlightStatus::Scheduled)
        {
            result.push_back(flight);
        }
        if (result.size() == num_departures)
        {
            break;
        }
    }
    return result;
}


std::vector<std::shared_ptr<Flight>> Airport::next_arrivals(unsigned num_arrivals) const {
        if (num_arrivals == 0)
        {
            // std::cout << "Invalid number of requested next arrivals" << std::endl;
            return {};
        }
        std::vector<std::shared_ptr<Flight>> result;
        for (const auto & [time, flight] : arrivals)
        {
            if (flight -> get_status() == FlightStatus::Departed or flight -> get_status() == FlightStatus::Scheduled)
            {
                result.push_back(flight);
            }
            if (result.size() == num_arrivals)
            {
                break;
            }
        }
        return result;
}


