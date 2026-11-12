#ifndef CALENDAR_H
#define  CALENDAR_H

#include <iostream>
#include <vector>
#include <memory>

#include "Event.h"

class Calendar {

private:
    std::vector<std::shared_ptr<Event>> events;

public:
    // The default constructor Calendar(void);  produces an empty vector
    // Then we have to create an object every time we create an event
    Calendar(void) = default;

    void addEvent (const Event&);  // The method is no longer const because the vector changes
    void updateEvent (time_t, const std::string&, time_t, const std::string&) const; // In this case, the event changes but the vector is still the same (no events added nor pointers changed)
    void print (void) const;
};

#endif // CALENDAR_H