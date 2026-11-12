//
// Created by pietr on 23/10/2026.
//

#include "Developer.h"
Developer::Developer(const std::string & name,
    const std::string & surname,
    const unsigned & employee_id): Employee (name, surname, employee_id){}

double Developer::salary_cal() const
{
    double w_salary = (work_hours - wsh_hours) * pay_rate;
    double wsh_salary = wsh_hours * wsh_rate;
    return w_salary + wsh_salary;
}

void Developer::set_wsh_hours (double wsh_hours_)
{
    wsh_hours = wsh_hours_;
}
