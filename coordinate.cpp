#include "coordinate.h"
#include <fstream>

Coordinate::Coordinate(int a_x_axis, int a_y_axis):m_y_axis(a_y_axis),m_x_axis(a_x_axis){}

void Coordinate::setX(int a_x_axis) {
    if(is_valid_coord(a_x_axis)){
        this->m_x_axis = a_x_axis;
    }
    else {
        std::cerr<<"Invalid X axis value!"<<std::endl;
    }
}

void Coordinate::setY(int a_y_axis) {
    if(is_valid_coord(a_y_axis)){
        this->m_y_axis = a_y_axis;
    }
    else {
        std::cerr<<"Invalid Y axis value!"<<std::endl;
    }
}

Coordinate::Coordinate(std::ifstream &a_input) {
    int coord_x =0 , coord_y = 0;

    a_input >> coord_y >> coord_x;
    this->setY(coord_y);
    this->setX(coord_x);
}

bool Coordinate::operator<(const Coordinate &rhs) const {
    bool result = false;

    if(this->m_y_axis < rhs.m_y_axis){
        result = true;
    }
    else if(this->m_y_axis == rhs.m_y_axis){
        result = (this->m_x_axis < rhs.m_x_axis);
    }
    return result;
}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return this->m_x_axis == rhs.m_x_axis && this->m_y_axis == rhs.m_y_axis;
}



