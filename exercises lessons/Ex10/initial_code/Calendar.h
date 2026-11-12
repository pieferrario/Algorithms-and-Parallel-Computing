#ifndef CALENDAR_H
#define  CALENDAR_H

#include <iostream>
#include <vector>
#include <memory>

#include "Event.h"

class Calendar {

private:
    std::shared_ptr<std::vector<Event>> events;

public:
    // The default constructor Calendar(void); would produce a null pointer.
    // Then we have to allocate an empty data structure first and then use the constructor.
    Calendar(void): events (std::make_shared<std::vector<Event>>()){}

    void addEvent (const Event&) const; // The methods are const because the pointer is const. add_event and update_event, don't change the pointer.
    void updateEvent (time_t, const std::string&, time_t, const std::string&) const;
    void print (void) const;
};

#endif // CALENDAR_H