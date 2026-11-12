#include "Calendar.h"

/* YOUR CODE GOES HERE */
void Calendar::addEvent (const Event& e)
{
   events.push_back(std::make_shared<Event>(e));
}

void Calendar::updateEvent (time_t old_date, const std::string& old_name , time_t new_date, const std::string& new_name) const
{
    bool found = false;
    for (std::vector<std::shared_ptr<Event>>::const_iterator it = events.cbegin(); it != events.cend() && !found; ++it)
    {
        std::shared_ptr<Event> ptr = *it;

        if (ptr -> getName() == old_name && ptr -> getTime() == old_date)
        {
            found = true;
            ptr -> setTime(new_date);
            ptr -> setName(new_name);
        }
    }
}

void Calendar::print (void) const
{
    for (const std::shared_ptr<Event> & e : events)
    {
        std::cout << e -> getName() << std::endl;
    }
}
