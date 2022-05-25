//
//  HealthPoints.hpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 18/05/2022.
//

#ifndef HealthPoints_hpp
#define HealthPoints_hpp

#define DEFAULT_MAX_HEALTH 100

#include <stdio.h>
#include <iostream>
#include <stdexcept>
using namespace std;

class HealthPoints {
public:
    HealthPoints(int maxHealth = DEFAULT_MAX_HEALTH);
    HealthPoints& operator+=(const int rhs);
    bool operator==(const HealthPoints& rhs);
    bool operator!=(const HealthPoints& rhs);
    bool operator<(const HealthPoints& rhs);
    bool operator<=(const HealthPoints& rhs);
    bool operator>(const HealthPoints& rhs);
    bool operator>=(const HealthPoints& rhs);
    friend std::ostream& operator<<(std::ostream& stream, const HealthPoints& hp);
    
    struct InvalidArgument{
        const std::string what () {
            return "Invalid Argument";
        }
    };
private:
    int m_value;
    int m_maxValue;

};

HealthPoints operator+(HealthPoints& lhs, const int rhs);
HealthPoints operator+(const int lhs, HealthPoints& rhs);
HealthPoints operator-(HealthPoints& lhs, const int rhs);
HealthPoints& operator-=(HealthPoints& lhs, const int rhs);

#endif /* HealthPoints_hpp */
