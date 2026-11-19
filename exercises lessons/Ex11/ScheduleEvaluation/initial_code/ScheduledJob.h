//
// Created by Federica Filippini on 16/11/2020.
//

#ifndef SCHEDULEEVALUATION_SCHEDULEDJOB_H
#define SCHEDULEEVALUATION_SCHEDULEDJOB_H

#include <memory> // I need to include memory to work with smart pointer,

#include "Job.h"

class ScheduledJob {

private:
    std::shared_ptr<const Job> pointer;  // I initialise a scheduled job as a shared pointer to a job (which is constant since we don't have to modify it)
    Job::time_instant start_time;

    void adjust_start_time();

public:
    ScheduledJob (const std::shared_ptr<const Job> & job_pointer, Job::time_instant st_time) // We can either construct by passing a shared pointer reference to a job and the starting time
            : pointer(job_pointer), start_time (st_time)
    {
        adjust_start_time();
    }

    ScheduledJob (Job j, Job::time_instant st_time)     // or pass a job and rely on the previous constructor using the pointer to the job
            : ScheduledJob(std::make_shared<Job>(j), st_time)
    {
        adjust_start_time();
    }

    explicit ScheduledJob (const std::shared_ptr<const Job> & job_pointer)
            : ScheduledJob(job_pointer, job_pointer->get_submission_time())
    {}

    Job::time_instant get_end_time() const;
    Job::time_instant get_start_time() const;
    Job::time_instant get_deadline() const;
    Job::time_instant get_execution_time() const;
    Job::time_instant get_submission_time() const;

    void set_start_time (Job::time_instant  st_time);

    double evaluate() const;

    void print() const;
};


#endif //SCHEDULEEVALUATION_SCHEDULEDJOB_H
