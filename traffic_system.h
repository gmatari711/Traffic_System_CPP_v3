#ifndef TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_SYSTEM_H
#define TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_SYSTEM_H

#include "cell.h"
#include "street.h"
#include "coordinate.h"
#include <set>
#include <list>
#include <string>


class TrafficSystem : public TrafficRoads
{
private:
    //Printing constants.
    static const char *VERTICAL_STREET_LEFT_BORDER;
    static const char *VERTICAL_STREET_MIDDLE;
    static const char *VERTICAL_STREET_RIGHT_BORDER;
    static const char *HORIZONTAL_STREET_TOP_BORDER;
    static const char *HORIZONTAL_STREET_MIDDLE;
    static const char *HORIZONTAL_STREET_MIDDLE_LEFT;
    static const char *HORIZONTAL_STREET_MIDDLE_RIGHT;
    static const char *HORIZONTAL_STREET_BOTTOM_BORDER;
    static const char *NO_ROAD;

    //Street table - Each cell holds two pointers to street
    Cell **m_traffic_table{nullptr};
    
    //Value - Traffic System width.
    size_t m_width{};
    //Value - Traffic System Length.
    size_t m_length{};
    //Container - Street key attached to its relevant initial Coordinate.
    std::multiset<Street> m_streets;
    std::set<Coordinate> m_junctions;
    std::list<Car *> m_cars; //May change to vector.

    /**
     * Allocate memory and initialize m_traffic_table according to m_width and m_length.
     */
    void createTables();
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     * @param a_street
     */
    void setHorizontalStreetToTable(int a_x_coord, int a_y_coord, Street *a_street);
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     * @param a_street
     */
    void setVerticalStreetToTable(int a_x_coord, int a_y_coord, Street *a_street);
    /**
     *
     * @param a_cell
     * @return
     */
    static inline bool isCellJunction(const Cell &a_cell);
    /**
     *
     * @param a_cell
     * @return
     */
    static inline bool isCellEmpty(const Cell &a_cell);
    /**
     *
     */
    void destroyTables();

    bool isValidExit(int a_x_coord, int a_y_coord, Exit a_exit)const;
    /**
    * Print a single row from traffic system. Each row is made out of three parts - top middle and bottom.
    * Means that each row is three chars in height.
    * @param a_row Row to be print. The current y coordinate of the table.
    */
    void printRow(size_t a_row) const;
    /**
     * Prints the top part of the current row.
     * @param a_row Row to be print. The current y coordinate of the table.
     */
    void printRowTop(size_t a_row) const;
    /**
     * Prints the bottom part of the current row.
     * @param a_row Row to be print. The current y coordinate of the table.
     */
    void printRowBottom(size_t a_row) const;
    /**
     * Prints the middle part of the current row.
     * @param a_row Row to be print. The current y coordinate of the table.
     */
    void printRowMiddle(size_t a_row) const;
    /**
     * Print the relevant traffic light color. Green if true, red otherwise.
     * @param a_status A boolean value representing traffic light color.
     */
    void printTrafficLights(bool a_status)const;
    /**
     * Print the top part of the junction.If top exit exists - a traffic light is
     * marked with its' current color (green if passage is open red if closed).
     * @param a_junction A Junction object representing a junction on the traffic system.
     */
    void printBottomJunction(int a_x_coord, int a_y_coord)const;
    /**
     * Print the top part of the junction.If left or right exits exists - relevant
     * traffic lights are marked with their current color (green if passage is open red if closed).
     * @param a_junction A Junction object representing a junction on the traffic system.
     */
    void printMiddleJunction(int a_x_coord, int a_y_coord)const;
    /**
     * Print the bottom part of the junction.If top exit exists - a traffic light is
     * marked with its' current color (green if passage is open red if closed).
     * @param a_junction A Junction object representing a junction on the traffic system.
     */
    void printTopJunction(int a_x_coord, int a_y_coord)const;
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     */
    static void printHorizontalStreetTop();
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     */
    static void printHorizontalStreetMiddle(const Cell &a_cell);
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     */
    static void printHorizontalStreetBottom();
    /**
    *
    * @param a_x_coord
    * @param a_y_coord
    */
    static void printVerticalStreetTop(const Cell &a_cell);
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     */
    static void printVerticalStreetMiddle(const Cell &a_cell);
    /**
     *
     * @param a_x_coord
     * @param a_y_coord
     */
    static void printVerticalStreetBottom(const Cell &a_cell);
    /**
     *
     * @param a_car
     * @return
     */
    bool isMovementPossible(const Car &a_car) const;
    /**
     *
     * @param a_car
     * @return
     */
    bool canMoveLeft(const Car &a_car)const;
    /**
     *
     * @param a_car
     * @return
     */
    bool canMoveRight(const Car &a_car)const;
    /**
     *
     * @param a_car
     * @return
     */
    bool canMoveUp(const Car &a_car)const;
    /**
     *
     * @param a_car
     * @return
     */
    bool canMoveDown(const Car &a_car)const;
    /**
     *
     * @param a_car
     */
    void driveCar(Car &a_car);
    /**
     *
     * @param a_st
     * @return
     */
    bool isStreetEntranceFree(const Street &a_st)const;
    /**
     *
     * @param a_car
     * @param a_street
     */
    void setCarOnStreet(Car *a_car,const Street &a_street);
    /**
     *
     * @param
     * @param
     * @return
     */
    bool isOutOfRoad(const Car& a_car)const;
    /**
     *
     * @param
     * @param
     * @return
     */
    void updateCarPosOnRoadMap(const Car& a_car);
    /**
     *
     * @param
     * @param
     * @return
     */
    void removeCarFromRoadMap(const Car& a_car);
    /**
     *
     * @param
     * @param
     * @return
     */
    bool isCarInBound(const Car& a_car)const;
    /**
    *
    * @param
    * @param
    * @return
    */
    void insertTrafficLights(int a_x_coord, int a_y_coord);

public:
    explicit TrafficSystem(const char *a_filename);
    ~TrafficSystem();
    void insertCarToTrafficSystem(Car *a_car, int a_street_id);
    void showTrafficSystem();
    void addCars();
};


#endif
