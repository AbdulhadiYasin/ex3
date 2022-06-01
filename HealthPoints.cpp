//
//  HealthPoints.cpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 18/05/2022.
//

#include "HealthPoints.h"
#include <stdexcept>

HealthPoints::HealthPoints(const int maxHealth): m_value(maxHealth), m_maxValue(maxHealth) {
    if(maxHealth <= 0)
        throw InvalidArgument();
}

HealthPoints& HealthPoints::operator+=(const int rhs) {
    if((m_value + rhs) > m_maxValue)
        m_value = m_maxValue;
    else if((m_value + rhs) < 0)
        m_value = 0;
    else
        m_value += rhs;
    
    return *this;
}

HealthPoints HealthPoints::operator+(const int rhs) const {
    HealthPoints rslt = *this;
    rslt += rhs;
    return rslt;
}

HealthPoints operator+(const int lhs, const HealthPoints& rhs){
    return rhs + lhs;
}

HealthPoints& HealthPoints::operator-=(const int rhs) {
    *this += (-rhs);
    return *this;
}

HealthPoints HealthPoints::operator-(const int rhs) const {
    HealthPoints rslt = *this;
    rslt -= rhs;
    return rslt;
}

bool operator==(const HealthPoints& lhs, const HealthPoints& rhs) {
    return !((lhs < rhs) || (rhs < lhs));
}

bool operator<(const HealthPoints& lhs, const HealthPoints& rhs){
    return (lhs.m_value < rhs.m_value);
}

bool operator>(const HealthPoints& lhs, const HealthPoints& rhs){
    return !((lhs < rhs)||(lhs == rhs));
}
bool operator>=(const HealthPoints& lhs, const HealthPoints& rhs){
    return ((lhs > rhs)||(lhs == rhs));
}

bool operator<=(const HealthPoints& lhs, const HealthPoints& rhs){
    return ((lhs < rhs)||(lhs == rhs));
}

bool operator!=(const HealthPoints& lhs, const HealthPoints& rhs){
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& points) {
    os << points.m_value << "(" << points.m_maxValue << ")";
    return os;
}
