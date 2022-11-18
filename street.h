#ifndef TRAFFIC_SYSTEM_CPP_V2_STREET_H
#define TRAFFIC_SYSTEM_CPP_V2_STREET_H

#include <string>
#include <mutex>
#include <windows.h>
#include "coordinate.h"
enum class Direction{ vertical , horizontal};

class Street {
private:
    //Change to enum class.
    static int street_id_generator;
    static const int color_array[8];

    const int m_street_color;
    const int m_street_id;
    const Coordinate m_coordinate;

    std::mutex m_street_mutex;
    std::string m_street_name;
    size_t m_street_length;
    Direction m_street_direction;
    /**
     *
     * @param a_os
     * @return
     */
    std::ostream &print(std::ostream &a_os)const;
public:
    friend std::ostream &operator<<(std::ostream &a_os,const Street &a_st);
    const Coordinate &getCoordinate()const{return this->m_coordinate;}
    int getX()const {return this->m_coordinate.getX();}
     int getY()const {return this->m_coordinate.getY();}
    explicit Street(std::ifstream &a_input);
    Street(const Street& rhs);
    /**
     *
     * @return
     */
    bool isHorizontal() const;
    /**
     *
     * @return
     */
    const std::string &getStreetName() const;
    /**
     *
     * @param a_street_name
     */
    void setStreetName(const std::string &a_street_name);
    /**
     *
     * @return
     */
    size_t getStreetLength() const;
    inline int getStreetColor()const{return this->m_street_color;}
    /**
     *
     * @param a_street_length
     */
    void setStreetLength(size_t a_street_length);
    /**
     *
     * @return
     */
    Direction getStreetDirection() const;
    /**
     *
     * @return
     */
    int getStreetId()const;
    /**
     *
     * @param rhs
     * @return
     */
    bool operator<(const Street &a_rhs)const;

    bool operator==(const Street &a_rhs)const;

    bool operator==(const int a_rhs)const;
    
    inline std::mutex* getMutex() { return &this->m_street_mutex; }

};


#endif //TRAFFIC_SYSTEM_CPP_V2_STREET_H
