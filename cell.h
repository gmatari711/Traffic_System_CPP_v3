#ifndef TRAFFIC_SYSTEM_CPP_V2_CELL_H
#define TRAFFIC_SYSTEM_CPP_V2_CELL_H

#include "car.h"
#include "street.h"
#include "coordinate.h"
#include "traffic_light.h"

class Cell
{
private:
    const Street *m_vertical{nullptr};
    const Street *m_horizontal{nullptr};
    const Car *m_car{nullptr};
    TrafficLight* m_traffic_light{ nullptr };
public:
    const Street *getVerticalStreet()const;
    const Street *getHorizontalStreet()const;
    void setHorizontalStreet(const Street *a_street);
    void setVerticalStreet(const Street *a_street);
    void setCar(const Car *a_car);
    const Car *getCar()const;
    const Car *removeCar();
    bool isEmptyCell()const;
    bool isHorizontalStreet();
    bool isVerticalStreet();
    bool isJunction();
    const TrafficLight* getTrafficLight() const;
    bool hasCar()const{return this->m_car != nullptr;}
};


#endif
