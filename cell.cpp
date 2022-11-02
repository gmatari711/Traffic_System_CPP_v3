//
// Created by gmata on 10/7/2022.
//

#include "cell.h"

void Cell::setVerticalStreet(const Street *a_street)
{
    this->m_vertical = a_street;
}

void Cell::setHorizontalStreet(const Street *a_street)
{
    this->m_horizontal = a_street;
}

const Street *Cell::getVerticalStreet() const
{
    return this->m_vertical;
}

const Street *Cell::getHorizontalStreet() const
{
    return this->m_horizontal;
}

void Cell::setCar(const Car *a_car)
{
    this->m_car = a_car;
}

const Car *Cell::getCar() const {
    return this->m_car;
}

const Car *Cell::removeCar() {
    const Car *result = this->m_car;
    this->m_car = nullptr;
    return result;
}

bool Cell::isEmptyCell() const
{
    return !(this->m_horizontal || this->m_vertical);
}

bool Cell::isHorizontalStreet()const
{
    return this->m_horizontal && !this->m_vertical;
}

bool Cell::isVerticalStreet()const
{
    return this->m_vertical && !this->m_horizontal;
}

bool Cell::isJunction()const
{
    return this->m_vertical && this->m_horizontal;
}

void Cell::addTrafficLights()
{
    this->m_traffic_light = new TrafficLights();
}

const TrafficLights* Cell::getTrafficLights() const
{
    return this->m_traffic_light;
}




