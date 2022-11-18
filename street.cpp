#include "street.h"
#include <iostream>
#include <fstream>

int Street::street_id_generator = 1;
const int Street::color_array[8] = {95, 23, 111, 143, 48, 96, 176, 224};
const std::string &Street::getStreetName() const
{
    return m_street_name;
}


void Street::setStreetName(const std::string &mStreetName)
{
    m_street_name = mStreetName;
}


size_t Street::getStreetLength() const
{
    return m_street_length;
}


void Street::setStreetLength(size_t mStreetLength)
{
    m_street_length = mStreetLength;
}


Direction Street::getStreetDirection() const
{
    return m_street_direction;
}


Street::Street(std::ifstream &a_input):
m_street_id(street_id_generator),
m_street_color(color_array[street_id_generator % 7]),
m_coordinate(a_input)
{
    int direction;
    ++street_id_generator;
    a_input>>this->m_street_name>>this->m_street_length>>direction;
    if(direction == 1)
    {
        this->m_street_direction = Direction::vertical;
    }
    else if(direction == 0)
    {
        this->m_street_direction = Direction::horizontal;
    }
}

Street::Street(const Street& rhs):
    m_street_color(rhs.m_street_color),
    m_coordinate(rhs.m_coordinate),
    m_street_direction(rhs.m_street_direction),
    m_street_id(rhs.m_street_id),
    m_street_length(rhs.m_street_length),
    m_street_name(rhs.m_street_name)
{
}




int Street::getStreetId()const
{
    return this->m_street_id;
}


bool Street::isHorizontal() const
{
    return this->m_street_direction == Direction::horizontal;
}


std::ostream &Street::print(std::ostream &a_os) const
{
    a_os<<this->m_street_name<<": ";
    a_os<<"ID# "<<this->m_street_id<<" ";
    a_os<< this->m_street_length<<"m ";
    if(this->m_street_direction == Direction::horizontal)
    {
        a_os<<"horizontal";
    }
    else
    {
        a_os<<"vertical";
    }
    return a_os;
}


std::ostream &operator<<(std::ostream &a_os,const Street &a_street)
{
    return a_street.print(a_os);
}


bool Street::operator<(const Street &a_rhs) const
{
    return this->m_street_id<a_rhs.m_street_id;
}

bool Street::operator==(const Street &a_rhs) const
{
    return this->m_street_id == a_rhs.m_street_id;
}

