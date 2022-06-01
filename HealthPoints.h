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
    
    HealthPoints(const int maxHealth = DEFAULT_MAX_HEALTH);
    
    ~HealthPoints() = default;
    HealthPoints(const HealthPoints& other) = default;
    HealthPoints& operator=(const HealthPoints& other) = default;
    
    
    
    HealthPoints operator+(const int rhs) const;
    HealthPoints operator-(const int rhs) const;
    
    HealthPoints& operator+=(const int rhs);
    HealthPoints& operator-=(const int rhs);
    
    friend bool operator<(const HealthPoints& current, const HealthPoints& other);
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


bool operator>=(const HealthPoints& lhs, const HealthPoints& rhs);
bool operator<=(const HealthPoints& lhs, const HealthPoints& rhs);
bool operator>(const HealthPoints& lhs, const HealthPoints& rhs);
bool operator!=(const HealthPoints& lhs, const HealthPoints& rhs);
HealthPoints operator+(const int lhs, const HealthPoints& rhs);
bool operator==(const HealthPoints& lhs, const HealthPoints& rhs);

#endif /* HealthPoints_hpp */
