#ifndef TRAFFIC_SYSTEM_CPP_V2_CAR_H
#define TRAFFIC_SYSTEM_CPP_V2_CAR_H

#include <iostream>
#include <thread>
#include <mutex>
#include "coordinate.h"

//Car size, trucks - add factory.
/**
 * TrafficRoads is an abstract class to serve as an interface for all traffic system classes who want
 * to use Car class.
 */
class TrafficRoads
{
protected:
    friend class Car;
    /**
     * Test if a certain can move according to its movement direction.
     * @param a_car A reference to a Car object.
     * @return True if Car movement is allowed. False otherwise.
     */
    virtual bool isMovementPossible(const Car& a_car) const = 0;
    /**
     * Check if a given Car object is within road bounds.
     * @param a_car A reference to a Car object.
     * @return True if Car is out of road bound. False otherwise.
     */
    virtual bool isOutOfRoad(const Car& a_car)const = 0;
    /**
     * Removes a given Car object from road system.
     * @param a_car A reference to a Car object. 
     */
    virtual void removeCarFromRoadMap(const Car& a_car) = 0;
    /**
     * Sets a given Car object from road system.
     * @param a_car A reference to a Car object.
     */
    virtual void updateCarPosOnRoadMap(const Car& a_car) = 0;
};


class LicensePlate
{
private:
    /**
     * Generating a new license plate value to be set to a_license_plate.
     * @param a_license_plate A LicensePlate object reference.
     */
    static void licensePlateGenerator(LicensePlate &a_license_plate);
    /** License plate is represented by an alphabetic character. */
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
    std::mutex* m_cur_street_mutex{ nullptr };
    
    std::ostream &print(std::ostream &os)const;
public:
    Car(TrafficRoads& a_tr, int a_x_coord, int a_y_coord, DriveDirection a_direction, std::mutex* a_mutex);
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