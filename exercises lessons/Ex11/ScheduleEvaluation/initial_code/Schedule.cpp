//
// Created by Federica Filippini on 16/11/2020.
//

#include "Schedule.h"


void Schedule::validate()
{
    // Schedule::validate aims to fix discrepancies within start time.
    // Thus we have to adjust start time so that two consecutive jobs are actually sequential

    if (order.empty())
        return;

    for (size_type idx = 1; idx < order.size(); ++idx)
    {
        if (order[idx].get_start_time() < order[idx - 1].get_end_time())
        {
            order[idx].set_start_time(order[idx - 1].get_end_time());
        }
    }
}

void Schedule::add (const std::shared_ptr<Job> & j)
{
    if (order.empty())
    {
        order.push_back(ScheduledJob(j));
    }
    else
    {
        ScheduledJob new_scheduled_job(j, order.back().get_end_time()); // If the vector is not empty, we create a new scheduled job whose start time is the end time of the previous
        order.push_back(new_scheduled_job);
    }
}

double Schedule::evaluate() const
{
    double tardiness = 0.0;
    for (size_type idx = 0; idx < order.size(); ++idx)
    {
        tardiness += order[idx].evaluate();
    }
    return tardiness;
}

Schedule::size_type Schedule::size() const
{
    return order.size();
}

void Schedule::print() const
{
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        order[i].print();
        std::cout << std::endl;
    }
}
