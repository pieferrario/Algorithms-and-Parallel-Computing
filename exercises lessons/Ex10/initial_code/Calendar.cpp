#include "Calendar.h"

/* YOUR CODE GOES HERE */
void Calendar::addEvent (const Event& e) const
{
    events->push_back(e);
}

void Calendar::updateEvent (time_t old_date, const std::string& old_name , time_t new_date, const std::string& new_name) const
{
    bool found = false;
    /* version 1
    for (size_t i = 0; i < events -> size() && !found; i++)
    {
        if ((*events)[i].getTime() == old_date &&
            (*events)[i].getName() == old_name)
        {
            found = true;
            (*events)[i].setTime(new_date);
            (*events)[i].setName(new_name);
        }
    }
    */

    for (std::vector<Event>::iterator it = events -> begin(); it != events->end(); ++it) // TODO
    {
        if (it->getName() == old_name && it->getTime() == old_date)
        {
            found = true;

            it -> setTime(new_date);
            it -> setName(new_name);
        }
    }
}

void Calendar::print (void) const
{
    for (const Event & e : *events)
    {
        std::cout << e.getName() << std::endl;
    }
}
