//
// Created by pietr on 23/10/2026.
//

#include "Manager.h"

Manager::Manager(std::string name,
        std::string surname,
        unsigned employee_id): Developer(name, surname, employee_id){}

double Manager::salary_cal() const
{
        double wsh_pay = (wsh_hours * wsh_rate);
        double m_pay = (m_hours * m_rate);
        double w_pay = (work_hours - wsh_hours - m_hours) * pay_rate;
        return wsh_pay + w_pay + m_pay;
}

void Manager::set_m_hours(double m_hours_)
{
        m_hours = m_hours_;
}