//
// Created by pietr on 23/10/2026.
//

#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "Developer.h"

class Manager : public Developer
{
private:
    double m_hours = 0.0;
    const double m_rate = 9.0;
public:
    Manager(std::string name,
        std::string surname,
        unsigned employee_id);

    double salary_cal() const override;
    void set_m_hours(double m_hours);
};


#endif //EMPLOYEE_MANAGER_H
