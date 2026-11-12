//
// Created by pietr on 23/10/2026.
//

#ifndef EMPLOYEE_INITIAL_EMPLOYEE_H
#define EMPLOYEE_INITIAL_EMPLOYEE_H

#include<string>
#include<iostream>

class Employee
{
protected:
    const std::string name;
    const std::string surname;
    const unsigned employee_id;
    const double pay_rate = 8.5; // $/hour
    double work_hours = 0.0;
public:
    Employee(const std::string & name_,
    const std::string & surname_,
    const unsigned & employee_id_); // the constructor can be implemented either here or in the cpp file

    virtual double salary_cal() const;

    void set_work_hours(const double & work_hours_);
    void print() const;
};


#endif //EMPLOYEE_INITIAL_EMPLOYEE_H
