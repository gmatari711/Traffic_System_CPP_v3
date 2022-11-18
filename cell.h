#ifndef TRAFFIC_SYSTEM_CPP_V2_CELL_H
#define TRAFFIC_SYSTEM_CPP_V2_CELL_H

#include "car.h"
#include "street.h"
#include "coordinate.h"
#include "traffic_light.h"

class Cell
{
private:
    Street *m_vertical{nullptr};
    Street *m_horizontal{nullptr};
    const Car *m_car{nullptr};
    TrafficLights* m_traffic_light{ nullptr };
public:
    const Street *getVerticalStreet()const;
    const Street *getHorizontalStreet()const;
    void setHorizontalStreet(Street *a_street);
    void setVerticalStreet(Street *a_street);
    void setCar(const Car *a_car);
    const Car *getCar()const;
    const Car *removeCar();
    bool isEmptyCell()const;
    bool isHorizontalStreet()const;
    bool isVerticalStreet()const;
    bool isJunction()const;
    void createTrafficLights();
    const TrafficLights* getTrafficLights() const;
    bool hasCar()const{return this->m_car != nullptr;}


    inline void insertExit(Exit a_exit) { this->m_traffic_light->insertExit(a_exit);}
    inline void activateTrafficLights() { this->m_traffic_light->turnOnTrafficLights(); }
};


#endif
