//
// Created by pietr on 23/10/2026.
//

#include "Secretary.h"

Secretary::Secretary(const std::string & name,
    const std::string & surname,
    const unsigned & employee_id): Employee(name, surname, employee_id){} // If we don't rely on the delegated constructor, we can't use name, surname and employee id since they are const in the Employee class