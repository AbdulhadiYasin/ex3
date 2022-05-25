//
//  HealthPoints.cpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 18/05/2022.
//

#include "HealthPoints.h"
#include <stdexcept>

HealthPoints::HealthPoints(int maxHealth): m_value(maxHealth), m_maxValue(maxHealth) {
    if(maxHealth <= 0)
        throw HealthPoints::InvalidArgument();
}


bool HealthPoints::operator==(const HealthPoints& rhs) {
    return m_value == rhs.m_value;
}
bool HealthPoints::operator!=(const HealthPoints& rhs) {
    return m_value != rhs.m_value;
}
bool HealthPoints::operator<(const HealthPoints& rhs) {
    return m_value < rhs.m_value;
}
bool HealthPoints::operator<=(const HealthPoints& rhs) {
    return m_value <= rhs.m_value;
}
bool HealthPoints::operator>(const HealthPoints& rhs) {
    return m_value > rhs.m_value;
}
bool HealthPoints::operator>=(const HealthPoints& rhs) {
    return m_value >= rhs.m_value;
}


HealthPoints& HealthPoints::operator+=(const int rhs) {
    m_value += rhs;
    if(m_value < 0)
        m_value = 0;
    else if(m_value > m_maxValue)
        m_value = m_maxValue;
        
    return *this;
}
HealthPoints& operator-=(HealthPoints& lhs, const int rhs) {
    lhs += (-1*rhs);
    return lhs;
}
HealthPoints operator+(HealthPoints& lhs, const int rhs) {
    HealthPoints temp = lhs;
    return temp += rhs;
}
HealthPoints operator+(const int lhs, HealthPoints& rhs){
    return rhs + lhs;
}
HealthPoints operator-(HealthPoints& lhs, const int rhs) {
    return lhs + (-1*rhs);
}

std::ostream& operator<<(std::ostream& stream, const HealthPoints& hp){
    stream << hp.m_value << '(' << hp.m_maxValue << ')';
    return stream;
}
