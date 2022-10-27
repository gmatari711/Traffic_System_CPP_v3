#ifndef TRAFFIC_SYSTEM_CPP_V2_CAR_H
#define TRAFFIC_SYSTEM_CPP_V2_CAR_H

#include <iostream>
#include <thread>
#include <mutex>
#include "coordinate.h"


class TrafficRoads
{
protected:
    friend class Car;
    static std::mutex roads_mutex;
    virtual bool isMovementPossible(const Car& a_car) const = 0;
    virtual bool isOutOfRoad(const Car& a_car)const = 0;
    virtual void removeCarFromRoadMap(const Car& a_car) = 0;
    virtual void updateCarPosOnRoadMap(const Car& a_car) = 0;
};


class LicensePlate
{
private:
    /**
     * Generating a new license plate value to be set to a_license_plate.
     * @param a_license_plate
     */
    static void licensePlateGenerator(LicensePlate &a_license_plate);

    char m_license_plate;
    std::ostream &print(std::ostream &os)const;
public:
    LicensePlate();
    friend std::ostream &operator<<(std::ostream &os, const LicensePlate &rhs);
};

enum class DriveDirection{left , up , right , down};

class Car
{
private:
    LicensePlate m_license_plate;
    Coordinate m_coordinate;
    DriveDirection m_drive_direction;
    TrafficRoads &m_roads;
    std::thread m_car_thread;
    
    /**
     *
     * @param os
     * @return
     */
    std::ostream &print(std::ostream &os)const;
public:
    Car(TrafficRoads& a_tr, int a_x_coord, int a_y_coord, DriveDirection a_direction);
    friend std::ostream &operator<<(std::ostream &os, const Car &rhs);
    int getX()const;
    int getY()const;
    void setX(int a_x_coord);
    void setY(int a_y_coord);
    void drive();
    void changeDriveDirection(DriveDirection a_new_direction);
    inline DriveDirection getDirection()const {return this->m_drive_direction;}
};




#endif