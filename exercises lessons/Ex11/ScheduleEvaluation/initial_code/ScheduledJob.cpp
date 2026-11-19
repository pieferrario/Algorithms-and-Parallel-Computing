//
// Created by Federica Filippini on 16/11/2020.
//

#include "ScheduledJob.h"


// we have to implement an adjust_start_time function
void ScheduledJob::adjust_start_time()
{
    // ScheduledJob::adjust_start_time(), that guarantees
    // that start_time and submission_time of the current job are compatible -> the job must start after its submission
    if (start_time < pointer -> get_submission_time())
    {
        start_time = pointer -> get_submission_time();
    }
}

Job::time_instant ScheduledJob::get_end_time() const
{
    return start_time + pointer -> get_execution_time();
}

Job::time_instant ScheduledJob::get_start_time() const
{
    return start_time;
}

Job::time_instant ScheduledJob::get_deadline() const
{
    return pointer -> get_deadline();
}

Job::time_instant ScheduledJob::get_execution_time() const
{
    return pointer -> get_execution_time();
}

Job::time_instant ScheduledJob::get_submission_time() const
{
    return pointer -> get_submission_time();
}

void ScheduledJob::set_start_time (Job::time_instant  st_time)  // we have developed the adjust_start_time function so we can rely on it as a setter for the smart time.
{
    // ScheduledJob::set_start_time(time), that sets the start time of the current job
    start_time = st_time;
    adjust_start_time();
}

double ScheduledJob::evaluate() const
{
    // computes the weighted tardiness of the current job
    double tardiness = 0.0;
    // precisely the tardiness is 0 if completion_time < due_date and it is completion_time – due_date otherwise.
    // however, those are elements of job so we have to use pointer->getter to access the items
    if (get_end_time() >= pointer -> get_deadline())
    {
        tardiness = pointer -> get_weight() * (get_end_time() - pointer -> get_deadline());
    }
    return tardiness;
}


void ScheduledJob::print() const
{
    pointer->print();
    std::cout << " start_time " << start_time
              << " end_time " << get_end_time();
}
