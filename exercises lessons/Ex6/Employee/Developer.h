//
// Created by pietr on 23/10/2026.
//

#ifndef EMPLOYEE_DEVELOPER_H
#define EMPLOYEE_DEVELOPER_H

#include"Employee.h"


class Developer: public Employee
{
protected:
    double wsh_hours = 0.0;
    const double wsh_rate = 9.0;
public:
    Developer(const std::string & name,
    const std::string & surname,
    const unsigned & employee_id);

    virtual double salary_cal() const;
    void set_wsh_hours (double wsh_hours_);
};


#endif //EMPLOYEE_DEVELOPER_H
