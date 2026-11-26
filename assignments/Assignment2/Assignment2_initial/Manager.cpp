//
// Created by Roberto Sala on 27/10/2026.
//

#include "Manager.h"
#include "SingleBooking.h"
#include "GroupBooking.h"
#include <set>
#include <queue>

AirportID Manager::add_airport(const std::string& name, const std::string& location) {
    airports[next_airport_id] = std::make_shared<Airport>(next_airport_id, name, location);
    return next_airport_id++;
}

PassengerID Manager::add_passenger(const std::string& name) {
    passengers[next_passenger_id] = std::make_shared<Passenger>(next_passenger_id, name);
    return next_passenger_id++;
}

FlightID Manager::add_flight(AirportID origin, AirportID destination, Timestamp timestamp, Duration duration, unsigned capacity) {
    if (airports.find(origin) == airports.end() or airports.find(destination) == airports.end())
    {
        // std::cout << "At least one of the two airports does not exist" << std::endl;
        return -1;
    }
    if (origin == destination)
    {
        // std::cout << "The origin airport and the destination airport cannot be the same" << std::endl;
        return -1;
    }
    if (duration <= 0)
    {
        // std::cout << "The duration cannot be non positive" << std::endl;
        return -1;
    }
    if (capacity == 0)
    {
        // std::cout << "The plane cannot have null capacity" << std::endl;
        return -1;
    }


    auto flight = std::make_shared<Flight>(next_flight_id, origin, destination, timestamp, duration, capacity);
    flights[next_flight_id] = flight;
    airports[origin] -> add_departure(flight);
    airports[destination] -> add_arrival(flight);

    return next_flight_id++;
}

bool Manager::check_booking_request(PassengerID passenger_id, const std::vector<FlightID>& flights_to_book, unsigned number_of_passengers) const {
    if (passengers.find(passenger_id) == passengers.cend())
    {
        // std::cout << "The passenger ID is not registered" << std::endl;
        return false;
    }
    if (flights_to_book.empty())
    {
        // std::cout << "The flight list is empty" << std::endl;
        return false;
    }
    if (number_of_passengers == 0)
    {
        // std::cout << "Number of passengers must be positive" << std::endl;
        return false;
    }

    std::set<FlightID> distinct_ids;
    for (auto flight_id : flights_to_book)
    {
        distinct_ids.insert(flight_id);
    }
    if (distinct_ids.size() != flights_to_book.size())
    {
        // std::cout << "There are multiple flights with the same id" << std::endl;
        return false;
    }

    for (auto flight_id : flights_to_book)
    {
        auto iterator = flights.find(flight_id);
        if (iterator == flights.cend())
        {
            // std::cout << "The provided flight does not exist" << std::endl;
            return false;
        }
        if (!(iterator -> second) -> is_bookable())
        {
            // std::cout << "The flight " << flight_id << " cannot be booked" << std::endl;
            return false;
        }
        if (! (iterator -> second) -> check_availability(number_of_passengers))
        {
            // std::cout << "There are not enough seats for the requested flight" << std::endl;
            return false;
        }
    }

    for (std::size_t idx = 0; idx < flights_to_book.size() - 1; ++idx)
    {
        const auto & first_flight = flights.at(flights_to_book[idx]);
        const auto & second_flight = flights.at(flights_to_book[idx + 1]);
        if (first_flight -> get_destination() != second_flight -> get_origin())
        {
            // std::cout << "The arrival airport does not coincide with the second origin airport" << std::endl;
            return false;
        }
        if (first_flight -> get_arrival_time() > second_flight -> get_timestamp())
        {
            // std::cout << "The first flight arrives later than the second flight's departure" << std::endl;
            return false;
        }
    }
    return true;
}

BookingID Manager::add_booking(PassengerID passenger_id, const std::vector<FlightID>& flights_to_book, unsigned number_of_passengers) {
    if (! check_booking_request(passenger_id, flights_to_book, number_of_passengers))
    {
        return -1;
    }
    BookingID id = next_booking_id;
    std::map<FlightID, std::vector<SeatID>> reserved_seats;
    for (auto flight_id : flights_to_book)
    {
        const auto & flight = flights.at(flight_id);
        reserved_seats[flight_id] = flight -> book(number_of_passengers, passenger_id);
    }
    std::shared_ptr<Booking> booking;
    if (number_of_passengers == 1)
    {
        booking = std::make_shared<SingleBooking>(id, passenger_id, reserved_seats);
    }
    else
    {
        booking = std::make_shared<GroupBooking>(id, passenger_id, reserved_seats, number_of_passengers);
    }
    bookings[id] = booking;
    passengers.at(passenger_id) -> add_booking(booking);

    return next_booking_id ++;
}

bool Manager::cancel_booking(BookingID id) {
    auto iterator = bookings.find(id);
    if (iterator == bookings.end())
    {
        // std::cout << "There exists no booking with the provided id" << std::endl;
        return false;
    }
    const auto & booking = iterator -> second;
    if (!booking -> cancel_booking())
    {
        return false;
    }

    const auto & booked_flights = booking -> get_flights();
    for (const auto & [flight_id, seats] :  booked_flights)
    {
        const auto & flight = flights.at(flight_id);
        if (flight -> is_bookable())
        {
            flight -> release(seats);
        }
    }
    return true;
}

bool Manager::take_off_plane(FlightID id) {
    auto iterator = flights.find(id);
    if (iterator == flights.end())
    {
        // std::cout << "The provided flight was not found" << std::endl;
        return false;
    }
    return iterator -> second -> depart();
}

bool Manager::land_plane(FlightID id) {
    auto iterator = flights.find(id);
    if (iterator == flights.end())
    {
        // std::cout << "The provided flight was not found" << std::endl;
        return false;
    }
    return iterator -> second -> arrive();
}


bool Manager::cancel_plane(FlightID id) {
    auto iterator = flights.find(id);
    if (iterator == flights.end())
    {
        // std::cout << "The provided flight was not found" << std::endl;
        return false;
    }
    auto flight = iterator -> second;
    if (! flight -> cancel())
    {
        return false;
    }

    for (const auto & [booking_id, booking] : bookings)
    {
        if (booking -> get_status() == BookingStatus::Confirmed and booking-> get_flights().find(id) != booking -> get_flights().end())
        {
            cancel_booking(booking_id);
        }
    }
    return true;
}

std::vector<BookingID> Manager::get_passenger_bookings(PassengerID passenger_id) const {
    auto iterator = passengers.find(passenger_id);
    if (iterator == passengers.end())
    {
        return {};
    }
    std::vector<BookingID> booking_ids;
    auto passenger = iterator -> second;
    for (const auto & booking : passenger -> get_bookings())
    {
        booking_ids.push_back(booking -> get_ID());
    }
    return booking_ids;
}

std::vector<FlightID> Manager::find_flights(AirportID origin, AirportID destination) const {
    auto first_iterator = airports.find(origin);
    auto second_iterator = airports.find(destination);
    if (first_iterator == airports.cend() or second_iterator == airports.cend())
    {
        return {};
    }
    std::vector<FlightID> found_flights;
    for (const auto & [flight_id, flight] : flights)
    {
        if (flight -> get_origin() == origin and flight -> get_destination() == destination and flight -> is_bookable())
            found_flights.push_back(flight_id);
    }
    return found_flights;
}

std::vector<std::vector<FlightID>>
Manager::find_paths(AirportID origin, AirportID destination,
                    unsigned number_of_passengers, unsigned max_flights) const {
    auto first_iterator = airports.find(origin);
    auto second_iterator = airports.find(destination);
    if (first_iterator == airports.cend() or second_iterator == airports.cend() or origin == destination)
    {
        return {};
    }
    std::queue<std::vector<FlightID>> flights_to_be_explored;
    std::vector<std::vector<FlightID>> result;

    for (const auto & [flight_id, flight] : flights)
    {
        if (flight -> get_origin() == origin and flight -> is_bookable() and flight -> check_availability(number_of_passengers))
        {
            flights_to_be_explored.push({flight_id});
        }
    }

    while (! flights_to_be_explored.empty())
    {
        std::vector <FlightID> path = flights_to_be_explored.front();
        flights_to_be_explored.pop();
        const auto & last = flights.at(path.back());

        if (last -> get_destination() == destination)
        {
            result.push_back(path);
            continue;
        }
        if (path.size() == max_flights)
        {
            continue;
        }

        std::set<AirportID> visited_airports = {origin};
        for (FlightID id : path)
        {
            visited_airports.insert(flights.at(id) -> get_destination());
        }
        for (const auto & [next_id, next_flight] : flights)
        {
            if (next_flight -> get_origin() == last -> get_destination()
                and next_flight -> is_bookable()
                and next_flight -> check_availability(number_of_passengers)
                and next_flight -> get_timestamp() >= last -> get_arrival_time()
                and visited_airports.find(next_flight -> get_destination()) == visited_airports.end())
            {
                std::vector<FlightID> new_path = path;
                new_path.push_back(next_id);
                flights_to_be_explored.push(new_path);
            }
        }
    }
    return result;
}

void Manager::print_next_departure_from(AirportID id, unsigned num_departures) const {
    auto a = airports.find(id);
    if (a == airports.end()) {
        std::cout << "Airport " << id << " not found!" << std::endl;
        return;
    }

    std::cout << "\nNext Departures from " << a->second->get_name() << " (" << a->second->get_location() << "):\n";
    auto list = a->second->next_departures(num_departures);

    if (list.empty())
        std::cout << "\tNone" << std::endl;

    for (const auto& f : list) {
        std::cout << "\t";
        f->print();
    }
}

void Manager::print_next_arrivals_to(AirportID id, unsigned num_arrivals) const {
    auto a = airports.find(id);
    if (a == airports.end()) {
        std::cout << "Airport " << id << " not found!" << std::endl;
        return;
    }

    std::cout << "\nNext Arrivals to " << a->second->get_name() << " (" << a->second->get_location() << "):\n";
    auto list = a->second->next_arrivals(num_arrivals);

    if (list.empty())
        std::cout << "\tNone" << std::endl;

    for (const auto& f : list) {
        std::cout << "\t";
        f->print();
    }
}

void Manager::print_flight(FlightID id) const {
    auto it = flights.find(id);

    if (it != flights.end())
        it->second->print();
    else
        std::cout << "Flight " << id << " not found!" << std::endl;
}

void Manager::print_booking(BookingID id) const {
    auto it = bookings.find(id);

    if (it != bookings.end())
        it->second->print();
    else
        std::cout << "Booking " << id << " not found!" << std::endl;
}

void Manager::print_passenger(PassengerID id) const {
    auto it = passengers.find(id);

    if (it != passengers.end()) {
        it->second->print();

        const auto & bookings = it->second->get_bookings();

        if (bookings.empty())
            std::cout << "Passenger " << id << " has no bookings!" << std::endl;

        for (const auto& booking : it->second->get_bookings()) {
            std::cout << "\t";
            booking->print();
        }
    }
    else
        std::cout << "Passenger " << id << " not found!" << std::endl;
}

void Manager::print_report() const {
    const unsigned all = flights.size();   // "big enough" limit for the next_* queries

    std::cout << "\n--- Flights ---" << std::endl;
    for (const auto& [id, flight] : flights)
        print_flight(id);

    std::cout << "\n--- Airports ---" << std::endl;
    for (const auto& [id, airport] : airports) {
        print_next_departure_from(id, all);
        print_next_arrivals_to(id, all);
    }

    std::cout << "\n--- Direct bookable flights between airports ---" << std::endl;
    for (const auto& [from, from_airport] : airports) {
        for (const auto& [to, to_airport] : airports) {
            if (from != to) {
                const std::vector<FlightID> direct = find_flights(from, to);
                if (!direct.empty()) {
                    std::cout << "\t" << from_airport->get_name() << " -> " << to_airport->get_name() << ":";
                    for (FlightID f : direct)
                        std::cout << "\n\t\tflight " << f;
                    std::cout << std::endl;
                }
            }
        }
    }

    for (unsigned n = 1; n <= 3; ++n) {
        std::cout << "\n--- Available paths for " << n << " passenger" << (n > 1 ? "s" : "") << " ---" << std::endl;
        for (const auto& [from, from_airport] : airports) {
            for (const auto& [to, to_airport] : airports) {
                if (from != to) {
                    const auto paths = find_paths(from, to, n);
                    if (!paths.empty()) {
                        std::cout << "\t" << from_airport->get_name() << " -> " << to_airport->get_name() << ":" << std::endl;
                        for (const auto& path : paths) {
                            std::cout << "\t\t";
                            for (std::size_t i = 0; i < path.size(); ++i)
                                std::cout << (i ? " -> " : "") << "flight " << path[i];
                            std::cout << std::endl;
                        }
                    }
                }
            }
        }
    }

    std::cout << "\n--- Passengers ---" << std::endl;
    for (const auto& [id, passenger] : passengers) {
        print_passenger(id);
        std::cout << "\tBooking IDs:";
        for (BookingID b : get_passenger_bookings(id))
            std::cout << " " << b;
        std::cout << std::endl;
    }

    std::cout << "\n--- Bookings ---" << std::endl;
    for (const auto& [id, booking] : bookings)
        print_booking(id);
}