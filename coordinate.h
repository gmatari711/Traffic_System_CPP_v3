#ifndef TRAFFIC_SYSTEM_CPP_V2_COORDINATE_H
#define TRAFFIC_SYSTEM_CPP_V2_COORDINATE_H

#include <iostream>

class Coordinate{
private:
    double m_x_axis;
    double m_y_axis;
    /**
     *
     * @param val
     * @return
     */
    inline bool is_valid_coord(int val){ return (val >= 0); }
public:
    explicit Coordinate(std::ifstream& a_input);
    explicit Coordinate(int a_x_axis = 0 , int a_y_axis = 0);
    /**
     *
     * @param a_y_axis
     */
    void setY(int a_y_axis);
    /**
     *
     * @param a_x_axis
     */
    void setX(int a_x_axis);
    /**
     *
     * @return
     */
    inline int getX()const { return this->m_x_axis; }
    /**
     *
     * @return
     */
    inline int getY()const { return this->m_y_axis; }
    /**
     *
     * @param rhs
     * @return
     */
    bool operator==(const Coordinate &rhs)const;
    /**
     *
     * @param rhs
     * @return
     */
    bool operator<(const Coordinate &rhs)const;
};

#endif
