#include "Manager.h"

// Helpers used only to make the output readable.
void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void print_paths(const std::vector<std::vector<FlightID>>& paths) {
    if (paths.empty()) {
        std::cout << "\tNo path found" << std::endl;
        return;
    }
    for (const auto& path : paths) {
        std::cout << "\t";
        for (std::size_t i = 0; i < path.size(); ++i)
            std::cout << (i ? " -> " : "") << "flight " << path[i];
        std::cout << std::endl;
    }
}

// ---------------------------------------------------------------------
// Data structures for Test2
// ---------------------------------------------------------------------
struct FlightData {
    std::size_t from;       // index in the airports vector
    std::size_t to;         // index in the airports vector
    Timestamp departure;
    Duration duration;
    unsigned capacity;
};

struct BookingRequest {
    std::size_t passenger;  // index in the passengers vector
    std::size_t from;       // index in the airports vector
    std::size_t to;         // index in the airports vector
    unsigned num_passengers;
};

// Books the first path returned by find_paths (up to 3 flights).
// Returns the booking ID, or -1 if no path exists.
BookingID book_first_path(Manager& manager, PassengerID passenger,
                          AirportID origin, AirportID destination, unsigned num_passengers);

// Processes all the requests in order and stores the IDs of the bookings created.
void book_requests(Manager& manager, const std::vector<BookingRequest>& requests,
                   const std::vector<PassengerID>& passengers, const std::vector<AirportID>& airports,
                   std::vector<BookingID>& bookings);

void test1();
void test2();

int main() {
    // Small test for debugging the code
    test1();

    // Bigger test with a larger system
    // test2();

    return 0;
}

BookingID book_first_path(Manager& manager, PassengerID passenger, AirportID origin,
                          AirportID destination, unsigned num_passengers) {
    const auto paths = manager.find_paths(origin, destination, num_passengers, 3);
    if (paths.empty())
        return -1;

    return manager.add_booking(passenger, paths.front(), num_passengers);
}

void book_requests(Manager& manager, const std::vector<BookingRequest>& requests,
                   const std::vector<PassengerID>& passengers, const std::vector<AirportID>& airports,
                   std::vector<BookingID>& bookings) {
    for (const BookingRequest& r : requests) {
        const BookingID id = book_first_path(manager, passengers[r.passenger],
                                             airports[r.from], airports[r.to], r.num_passengers);
        if (id != -1)
            bookings.push_back(id);
    }
}

void test1() {
    Manager manager;

    // ------------------------------------------------------------------
    section("Setup: airports, flights, passengers");
    // ------------------------------------------------------------------
    AirportID mxp = manager.add_airport("MXP", "Milano");
    AirportID fco = manager.add_airport("FCO", "Roma");
    AirportID pmo = manager.add_airport("PMO", "Palermo");

    FlightID f0 = manager.add_flight(mxp, fco,  10,  60, 3);   // arrives at 70
    FlightID f1 = manager.add_flight(fco, pmo, 100,  50, 2);   // arrives at 150
    FlightID f2 = manager.add_flight(mxp, pmo,  20, 120, 2);   // direct, arrives at 140
    FlightID f3 = manager.add_flight(fco, pmo,  65,  50, 2);   // leaves FCO before f0 lands

    PassengerID alice = manager.add_passenger("Alice");
    PassengerID bob   = manager.add_passenger("Bob");
    PassengerID carla = manager.add_passenger("Carla");

    // ------------------------------------------------------------------
    section("Invalid flights and airports");
    // ------------------------------------------------------------------
    manager.add_flight(mxp, 99, 10, 60, 3);      // unknown destination
    manager.add_flight(mxp, mxp, 10, 60, 3);     // same origin and destination
    manager.add_flight(mxp, fco, 10, 0, 3);      // zero duration
    manager.add_flight(mxp, fco, 10, 60, 0);     // zero seats

    // ------------------------------------------------------------------
    section("Searching flights and paths");
    // ------------------------------------------------------------------
    std::cout << "Direct flights FCO -> PMO:" << std::endl;
    for (FlightID id : manager.find_flights(fco, pmo))
        std::cout << "\tflight " << id << std::endl;

    std::cout << "Paths MXP -> PMO for 1 passenger:" << std::endl;
    print_paths(manager.find_paths(mxp, pmo, 1));       // f2 and f0 -> f1 (f3 leaves too early)

    std::cout << "Paths MXP -> PMO for 3 passengers:" << std::endl;
    print_paths(manager.find_paths(mxp, pmo, 3));       // only f0 has 3 seats, f1 and f2 have 2

    std::cout << "Paths MXP -> unknown airport:" << std::endl;
    print_paths(manager.find_paths(mxp, 99, 1));

    // ------------------------------------------------------------------
    section("Invalid bookings (all must return -1)");
    // ------------------------------------------------------------------
    manager.add_booking(carla, {f1, f0}, 1);      // not connected and wrong time order
    manager.add_booking(carla, {f0, f3}, 1);      // f3 leaves before f0 lands
    manager.add_booking(carla, {f0, 99}, 1);      // unknown flight
    manager.add_booking(carla, {f0, f0}, 1);      // duplicate flight
    manager.add_booking(carla, {}, 1);            // no flights
    manager.add_booking(carla, {f0}, 0);          // zero passengers
    manager.add_booking(carla, {f0}, 4);          // more passengers than seats
    manager.add_booking(42, {f0}, 1);             // unknown passenger

    // ------------------------------------------------------------------
    section("Valid bookings");
    // ------------------------------------------------------------------
    BookingID b0 = manager.add_booking(alice, {f0, f1}, 1);   // single booking, two legs
    manager.add_booking(bob,   {f2}, 2);                      // group booking, f2 is now full
    BookingID b2 = manager.add_booking(carla, {f0}, 2);       // group booking, f0 is now full
    manager.add_booking(carla, {f1}, 1);                      // f1 is now full

    std::cout << "\nThe flights are now full:" << std::endl;
    manager.add_booking(carla, {f2}, 1);          // f2 is full -> -1
    std::cout << "check_booking_request(alice, {f2}, 1): "
              << (manager.check_booking_request(alice, {f2}, 1) ? "true" : "false") << std::endl;

    // ------------------------------------------------------------------
    section("Passengers and bookings");
    // ------------------------------------------------------------------
    for (PassengerID p : {alice, bob, carla}) {
        manager.print_passenger(p);
        std::cout << "\tBooking IDs:";
        for (BookingID b : manager.get_passenger_bookings(p))
            std::cout << " " << b;
        std::cout << std::endl;
    }
    manager.print_passenger(42);                  // unknown passenger
    manager.get_passenger_bookings(42);

    manager.print_booking(b0);
    manager.print_booking(99);                    // unknown booking
    manager.print_flight(f0);
    manager.print_flight(99);                     // unknown flight

    // ------------------------------------------------------------------
    section("Departures and arrivals");
    // ------------------------------------------------------------------
    manager.print_next_departure_from(mxp, 5);    // f0 (t=10), f2 (t=20)
    manager.print_next_arrivals_to(pmo, 5);       // f3 (115), f2 (140), f1 (150)
    manager.print_next_arrivals_to(pmo, 1);       // limited to the first one
    manager.print_next_departure_from(99, 5);     // unknown airport

    // ------------------------------------------------------------------
    section("Cancelling bookings");
    // ------------------------------------------------------------------
    manager.cancel_booking(b2);                   // frees the 2 seats of Carla on f0
    manager.cancel_booking(b2);                   // already canceled
    manager.cancel_booking(99);                   // unknown booking
    manager.print_booking(b2);

    // ------------------------------------------------------------------
    section("Cancelling a flight cancels its bookings");
    // ------------------------------------------------------------------
    manager.cancel_plane(f1);                     // cancels b0 (Alice, f0+f1) and b3 (Carla, f1)
    manager.cancel_plane(f1);                     // already canceled
    manager.cancel_plane(99);                     // unknown flight
    manager.print_passenger(alice);
    manager.print_passenger(carla);

    std::cout << "\nPaths MXP -> PMO for 1 passenger after the cancellations:" << std::endl;
    print_paths(manager.find_paths(mxp, pmo, 1));   // f2 is full, f0 -> f1 is gone

    // b0 was canceled, so Alice's seat on f0 is free again: all 3 seats can be booked.
    BookingID b4 = manager.add_booking(bob, {f0}, 3);
    std::cout << "Booking of 3 seats on flight 0 returned " << b4 << std::endl;

    // ------------------------------------------------------------------
    section("Flight life cycle");
    // ------------------------------------------------------------------
    manager.land_plane(f0);                       // cannot land: not departed yet
    manager.take_off_plane(f0);
    manager.take_off_plane(f0);                   // already departed
    manager.cancel_plane(f0);                     // too late to cancel
    manager.add_booking(carla, {f0}, 1);          // departed flights are not bookable
    manager.print_next_departure_from(mxp, 5);    // only f2 is left
    manager.print_next_arrivals_to(fco, 5);       // f0 is still on its way

    manager.land_plane(f0);
    manager.land_plane(f0);                       // already arrived
    manager.take_off_plane(99);                   // unknown flight
    manager.print_next_arrivals_to(fco, 5);       // None
    manager.print_flight(f0);
    manager.print_flight(f2);

    manager.cancel_booking(b4);                   // allowed: the booking is canceled, seats stay with the flight
    manager.print_booking(b4);

    // ------------------------------------------------------------------
    section("Report");
    // ------------------------------------------------------------------
    manager.print_report();
}

void test2() {
    Manager manager;

    // Airport indices, to make the tables readable.
    enum { MXP, FCO, PMO, NAP, TRN, VCE, BRI, CTA };

    // ------------------------------------------------------------------
    section("Setup: airports");
    // ------------------------------------------------------------------
    const std::vector<std::pair<std::string, std::string>> airport_data = {
        {"MXP", "Milano"}, {"FCO", "Roma"},   {"PMO", "Palermo"}, {"NAP", "Napoli"},
        {"TRN", "Torino"}, {"VCE", "Venezia"}, {"BRI", "Bari"},   {"CTA", "Catania"}
    };
    std::vector<AirportID> airports;
    for (const auto& [name, location] : airport_data)
        airports.push_back(manager.add_airport(name, location));

    // ------------------------------------------------------------------
    section("Setup: flights");
    // ------------------------------------------------------------------
    // Sorted by departure time, so the flight IDs follow the time order.
    const std::vector<FlightData> flight_data = {
        {MXP, FCO,   0,  60, 4}, {TRN, MXP,  10,  50, 3}, {FCO, PMO,  80,  60, 3},
        {MXP, PMO,  90, 120, 2}, {VCE, FCO, 100,  70, 4}, {FCO, NAP, 130,  40, 3},
        {NAP, CTA, 190,  60, 2}, {MXP, VCE, 200,  60, 5}, {FCO, BRI, 220,  60, 3},
        {PMO, CTA, 230,  40, 2}, {BRI, MXP, 300, 100, 4}, {CTA, FCO, 320,  80, 3},
        {MXP, TRN, 340,  50, 3}, {FCO, MXP, 360,  60, 4}, {PMO, FCO, 380,  60, 3},
        {VCE, BRI, 400,  80, 2}, {NAP, FCO, 420,  40, 3}, {MXP, FCO, 440,  60, 4},
        {FCO, PMO, 500,  60, 3}, {TRN, FCO, 520,  90, 2}, {FCO, VCE, 540,  70, 4},
        {BRI, NAP, 560,  60, 3}, {CTA, PMO, 580,  40, 2}, {PMO, MXP, 600, 120, 3},
        {MXP, NAP, 620,  90, 3}, {NAP, MXP, 700,  90, 3}, {FCO, TRN, 720,  90, 2},
        {VCE, MXP, 740,  60, 4}, {BRI, FCO, 760,  60, 3}, {CTA, MXP, 800, 130, 2}
    };
    std::vector<FlightID> flights;
    for (const FlightData& f : flight_data)
        flights.push_back(manager.add_flight(airports[f.from], airports[f.to],
                                             f.departure, f.duration, f.capacity));

    // ------------------------------------------------------------------
    section("Setup: passengers");
    // ------------------------------------------------------------------
    const std::vector<std::string> names = {
        "Alice", "Bob", "Carla", "Davide", "Elena", "Fabio", "Giulia", "Hassan", "Irene", "Luca",
        "Marta", "Nicola", "Olga", "Paolo", "Quinn", "Rita", "Sara", "Tommaso", "Ugo", "Vera"
    };
    std::vector<PassengerID> passengers;
    for (const std::string& name : names)
        passengers.push_back(manager.add_passenger(name));

    // ------------------------------------------------------------------
    section("Morning: passengers book their trips");
    // ------------------------------------------------------------------
    const std::vector<BookingRequest> morning_requests = {
        { 0, MXP, PMO, 1}, { 0, TRN, FCO, 2}, { 1, MXP, CTA, 2}, { 1, VCE, PMO, 1},
        { 2, FCO, MXP, 3}, { 2, BRI, FCO, 1}, { 3, MXP, NAP, 1}, { 3, CTA, MXP, 2},
        { 4, TRN, PMO, 1}, { 5, VCE, BRI, 2}, { 5, FCO, VCE, 1}, { 6, PMO, MXP, 1},
        { 7, NAP, MXP, 2}, { 7, MXP, CTA, 1}, { 8, BRI, MXP, 1}, { 9, FCO, TRN, 1},
        {10, MXP, FCO, 4}, {10, PMO, FCO, 1}, {11, TRN, NAP, 1}, {12, CTA, FCO, 1},
        {13, VCE, MXP, 1}, {14, FCO, PMO, 2}, {14, MXP, BRI, 1}, {15, NAP, FCO, 1},
        {16, BRI, NAP, 1}, {17, TRN, VCE, 1}, {17, PMO, CTA, 1}, {18, CTA, PMO, 1},
        {18, MXP, TRN, 2}, {19, FCO, NAP, 1}, {19, VCE, FCO, 2}, { 4, NAP, CTA, 1}
    };
    std::vector<BookingID> bookings;
    book_requests(manager, morning_requests, passengers, airports, bookings);
    std::cout << "\nBookings created: " << bookings.size() << std::endl;

    // ------------------------------------------------------------------
    section("Some passengers cancel their bookings");
    // ------------------------------------------------------------------
    for (std::size_t i = 0; i < bookings.size(); i += 5)
        manager.cancel_booking(bookings[i]);

    // ------------------------------------------------------------------
    section("Some flights are canceled (with all their bookings)");
    // ------------------------------------------------------------------
    manager.cancel_plane(flights[3]);
    manager.cancel_plane(flights[17]);
    manager.cancel_plane(flights[29]);

    // ------------------------------------------------------------------
    section("Seats freed: new bookings");
    // ------------------------------------------------------------------
    const std::vector<BookingRequest> afternoon_requests = {
        { 1, MXP, PMO, 1}, { 4, TRN, PMO, 1}, { 9, FCO, TRN, 1}, {11, TRN, NAP, 1},
        {12, CTA, FCO, 1}, {13, VCE, MXP, 1}, { 6, FCO, VCE, 2}, { 8, MXP, FCO, 1}
    };
    book_requests(manager, afternoon_requests, passengers, airports, bookings);

    // ------------------------------------------------------------------
    section("Day goes on: take-offs and landings");
    // ------------------------------------------------------------------
    // Flight IDs follow the departure order: the first half takes off,
    // the first quarter also lands, the others stay scheduled.
    for (std::size_t i = 0; i < flights.size() / 2; ++i)
        manager.take_off_plane(flights[i]);
    for (std::size_t i = 0; i < flights.size() / 4; ++i)
        manager.land_plane(flights[i]);

    // ------------------------------------------------------------------
    section("Evening: late requests (departed flights are not bookable)");
    // ------------------------------------------------------------------
    const std::vector<BookingRequest> evening_requests = {
        { 3, MXP, FCO, 1}, { 5, VCE, FCO, 1}, { 7, NAP, MXP, 1}, {15, PMO, MXP, 1},
        {16, FCO, PMO, 1}, {19, BRI, FCO, 2}, { 2, CTA, MXP, 1}, {10, MXP, NAP, 1}
    };
    book_requests(manager, evening_requests, passengers, airports, bookings);

    // ------------------------------------------------------------------
    section("Report");
    // ------------------------------------------------------------------
    manager.print_report();
}