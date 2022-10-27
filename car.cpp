#include "car.h"
#include <Windows.h>



void LicensePlate::licensePlateGenerator(LicensePlate &a_license_plate)
{
    static char generator = 'a';
    a_license_plate.m_license_plate = generator++;
    //Handle limits.
}

std::ostream &operator<<(std::ostream &os, const LicensePlate &rhs)
{
    return rhs.print(os);
}

std::ostream &LicensePlate::print(std::ostream &os) const
{
    os<<this->m_license_plate;
    return os;
}

LicensePlate::LicensePlate()
{
    licensePlateGenerator(*this);
}

std::mutex Car::car_mutex;

std::ostream &Car::print(std::ostream &os) const
{
    os<<this->m_license_plate;
    return os;
}

Car::Car(TrafficRoads& a_tr, int a_x_coord, int a_y_coord, DriveDirection a_direction) :
    m_roads(a_tr),m_coordinate(a_x_coord,a_y_coord),m_drive_direction(a_direction)
{
    this->m_car_thread = std::thread(&Car::drive, this);
}

std::ostream &operator<<(std::ostream &os, const Car &rhs) {
    return rhs.print(os);
}

int Car::getX() const {
    return this->m_coordinate.getX();
}

int Car::getY() const {
    return this->m_coordinate.getY();
}

void Car::setX(int a_x_coord) {
    this->m_coordinate.setX(a_x_coord);
}


void Car::setY(int a_y_coord) {
    this->m_coordinate.setY(a_y_coord);
}

void Car::drive()
{
    while (!m_roads.isOutOfRoad(*this))
    {
        car_mutex.lock();
        if (m_roads.isMovementPossible(*this))
        {
            switch (this->m_drive_direction)
            {
            case DriveDirection::up:
                this->setY(this->getY() - 1);
                break;
            case DriveDirection::down:
                this->setY(this->getY() + 1);
                break;
            case DriveDirection::left:
                this->setX(this->getX() - 1);
                break;
            case DriveDirection::right:
                this->setX(this->getX() + 1);
                break;
            }
        }
        car_mutex.unlock();
        Sleep(1000);
    }
}

void Car::changeDriveDirection(DriveDirection a_new_direction) {
    this->m_drive_direction = a_new_direction;
}