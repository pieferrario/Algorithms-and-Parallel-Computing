//
// Created by pietr on 23/10/2026.
//

#include "Employee.h"

Employee::Employee (const std::string & name_,
    const std::string & surname_,
    const unsigned & employee_id_): name(name_), surname(surname_), employee_id(employee_id_) {}

double Employee::salary_cal() const
{
    return work_hours * pay_rate;
}

void Employee::set_work_hours(const double & work_hours_)
{
    work_hours = work_hours_;
}

void Employee::print() const
{
    std::cout << name << " " << surname << ", " << employee_id << std::endl;
}