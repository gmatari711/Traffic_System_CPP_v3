#include "traffic_system.h"
#include <windows.h>
#include <fstream>
#include <cstdlib>

const char *TrafficSystem::VERTICAL_STREET_LEFT_BORDER = "|";
const char *TrafficSystem::VERTICAL_STREET_MIDDLE = " ";
const char *TrafficSystem::VERTICAL_STREET_RIGHT_BORDER = "|";
const char *TrafficSystem::HORIZONTAL_STREET_TOP_BORDER = "---";
const char *TrafficSystem::HORIZONTAL_STREET_MIDDLE = " ";
const char *TrafficSystem::HORIZONTAL_STREET_MIDDLE_LEFT = " ";
const char *TrafficSystem::HORIZONTAL_STREET_MIDDLE_RIGHT = " ";
const char *TrafficSystem::HORIZONTAL_STREET_BOTTOM_BORDER = "---";
const char *TrafficSystem::NO_ROAD = "   ";

TrafficSystem::TrafficSystem(const char *a_filename)
{
    std::ifstream input(a_filename);

    input>>this->m_length>>this->m_width;
    //Create table.
    createTables();
    while(!input.eof())
    {
        const Street *curr{nullptr};
        curr = &(*this->m_streets.insert(Street(input)));
        if(curr->getStreetDirection() == Direction::horizontal)
        {
            this->setHorizontalStreetToTable(curr->getX(),curr->getY(),curr);
        }
        else
        {
            this->setVerticalStreetToTable(curr->getX(),curr->getY(),curr);
        }
    }
}

void TrafficSystem::createTables()
{
    this->m_traffic_table = new Cell*[this->m_length];
    this->m_traffic_lights = new Exit*[this->m_length];
    for(size_t i = 0 ; i < this->m_length ; ++i)
    {
        this->m_traffic_table[i] = new Cell[this->m_width];
        this->m_traffic_lights[i] = new Exit[this->m_width];
    }

}

void TrafficSystem::destroyTables()
{
    for(size_t i = 0 ; i < this->m_length ; ++i)
    {
        delete [] this->m_traffic_table[i];
        delete [] this->m_traffic_lights[i];
    }
    delete[] this->m_traffic_table;
    delete [] this->m_traffic_lights;
}

TrafficSystem::~TrafficSystem()
{
    destroyTables();
}

void TrafficSystem::setHorizontalStreetToTable(int a_x_coord, int a_y_coord, const Street *a_street)
{
    for(size_t i = a_x_coord ; i < a_x_coord + a_street->getStreetLength()/100 ; ++i)
    {
        this->m_traffic_table[a_y_coord][i].setHorizontalStreet(a_street);
    }
}

void TrafficSystem::setVerticalStreetToTable(int a_x_coord, int a_y_coord, const Street *a_street)
{
    for(size_t i = a_y_coord ; i < a_y_coord + a_street->getStreetLength()/100 ; ++i)
    {
        this->m_traffic_table[i][a_x_coord].setVerticalStreet(a_street);
    }
}



bool TrafficSystem::isCellJunction(const Cell &a_cell)
{
    return a_cell.getHorizontalStreet() && a_cell.getVerticalStreet();
}


bool TrafficSystem::isCellEmpty(const Cell &a_cell)
{
    return !(a_cell.getHorizontalStreet() || a_cell.getVerticalStreet());
}


void TrafficSystem::printRow(size_t a_row) const
{
    this->printRowTop(a_row);
    this->printRowMiddle(a_row);
    this->printRowBottom(a_row);
}


void TrafficSystem::printRowTop(size_t a_row) const
{
    for(size_t i = 0 ; i < this->m_width ; ++i)
    {
        if(isCellJunction(m_traffic_table[a_row][i]))
        {
            printTopJunction(i,a_row);
        }
        else if(m_traffic_table[a_row][i].getVerticalStreet())
        {
            printVerticalStreetTop(m_traffic_table[a_row][i]);
        }
        else if (m_traffic_table[a_row][i].getHorizontalStreet())
        {
            printHorizontalStreetTop();
        }
        else
        {
            std::cout<<NO_ROAD;
        }
    }
    std::cout<<std::endl;
}

void TrafficSystem::printRowMiddle(size_t a_row) const
{
    for(size_t i = 0 ; i < this->m_width ; ++i)
    {
        if(isCellJunction(m_traffic_table[a_row][i]))
        {
            printMiddleJunction(i , a_row);
        }
        else if(m_traffic_table[a_row][i].getVerticalStreet())
        {
            printVerticalStreetMiddle(m_traffic_table[a_row][i]);
        }
        else if (m_traffic_table[a_row][i].getHorizontalStreet())
        {
            printHorizontalStreetMiddle(m_traffic_table[a_row][i]);
        }
        else
        {
            std::cout<<NO_ROAD;
        }
    }
    std::cout<<std::endl;
}


void TrafficSystem::printRowBottom(size_t a_row) const
{
    for(size_t i = 0 ; i < this->m_width ; ++i)
    {
        if(isCellJunction(m_traffic_table[a_row][i]))
        {
            printBottomJunction(i, a_row);
        }
        else if(m_traffic_table[a_row][i].getVerticalStreet())
        {
            printVerticalStreetBottom(m_traffic_table[a_row][i]);
        }
        else if (m_traffic_table[a_row][i].getHorizontalStreet())
        {
            printHorizontalStreetBottom();
        }
        else
        {
            std::cout<<NO_ROAD;
        }
    }
    std::cout<<std::endl;
}

void TrafficSystem::printTopJunction(int a_x_coord, int a_y_coord)const
{
    if(isValidExit(a_x_coord,a_y_coord, Exit::up))
    {
        std::cout<<" ";
        printTrafficLight(false);
        std::cout<<" ";
    }
    else
    {
        std::cout<<"---";
    }
}

void TrafficSystem::printMiddleJunction(int a_x_coord, int a_y_coord)const
{
    if(isValidExit(a_x_coord,a_y_coord,Exit::left))
    {
        printTrafficLight(false);
    }
    else
    {
        std::cout<<VERTICAL_STREET_LEFT_BORDER;
    }
    std::cout<<"+";
    if(isValidExit(a_x_coord,a_y_coord,Exit::right))
    {
        printTrafficLight(false);
    }
    else
    {
        std::cout<<VERTICAL_STREET_RIGHT_BORDER;
    }
}

void TrafficSystem::printBottomJunction(int a_x_coord, int a_y_coord)const
{
    if(isValidExit(a_x_coord,a_y_coord,Exit::down))
    {
        std::cout<<" ";
        printTrafficLight(false);
        std::cout<<" ";
    }
    else
    {
        std::cout<<"---";
    }
}

void TrafficSystem::showTrafficSystem()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
    //Print traffic system layout.
    for(size_t i = 0 ; i < this->m_length ; ++i)
    {
        this->printRow(i);
    }
    //Print streets information.
    for(const auto &e : this->m_streets)
    {
        std::cout<<e<<std::endl;
    }

}

void TrafficSystem::printTrafficLight(bool a_status)const
{
    //Set light color
    int light_color = (a_status)?BACKGROUND_GREEN:BACKGROUND_RED;
    //Fix new background color.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY | light_color);
    std::cout<<" ";
    //Return console background color to its original state.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}


bool TrafficSystem::isValidExit(int a_x_coord, int a_y_coord, Exit a_exit) const
{
    bool result = false;
    switch(a_exit)
    {
        case Exit::left:
            if(a_x_coord && this->m_traffic_table[a_y_coord][a_x_coord - 1].getHorizontalStreet())
            {
                result = true;
            }
            break;
        case Exit::right:
            if(a_x_coord < m_width-1 && this->m_traffic_table[a_y_coord][a_x_coord + 1].getHorizontalStreet())
            {
                result = true;
            }
            break;
        case Exit::up:
            if(a_y_coord && this->m_traffic_table[a_y_coord - 1][a_x_coord].getVerticalStreet())
            {
                result = true;
            }
            break;
        case Exit::down:
            if(a_y_coord < m_length - 1 && this->m_traffic_table[a_y_coord + 1][a_x_coord].getVerticalStreet())
            {
                result = true;
            }
            break;
    }
    return result;
}

void TrafficSystem::insertCarToTrafficSystem(Car *a_car, int a_street_id)
{
    for(const auto &st : this->m_streets)
    {
        if(st.getStreetId() == a_street_id)
        {
            a_car->setX(st.getX());
            a_car->setY(st.getY());
            if(st.getStreetDirection() == Direction::vertical)
            {
                a_car->changeDriveDirection(DriveDirection::down);
            }
            else
            {
                a_car->changeDriveDirection(DriveDirection::right);
            }
            this->m_traffic_table[a_car->getY()][a_car->getX()].setCar(a_car);
            this->m_cars.push_back(a_car);
            break;
        }
    }
}

void TrafficSystem::printHorizontalStreetMiddle(const Cell &a_cell)
{
    //Set console BG color.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a_cell.getHorizontalStreet()->getStreetColor());
    std::cout<<HORIZONTAL_STREET_MIDDLE_LEFT;
    if(a_cell.getCar())
    {
        std::cout<<*a_cell.getCar();
    }
    else
    {
        std::cout<<HORIZONTAL_STREET_MIDDLE;
    }
    std::cout<<HORIZONTAL_STREET_MIDDLE_RIGHT;
    //Return console background color to its original state.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void TrafficSystem::printHorizontalStreetTop()
{
    std::cout<<HORIZONTAL_STREET_TOP_BORDER;
}

void TrafficSystem::printHorizontalStreetBottom()
{
    std::cout<<HORIZONTAL_STREET_BOTTOM_BORDER;
}

void TrafficSystem::printVerticalStreetTop(const Cell &a_cell) {
    std::cout<<VERTICAL_STREET_LEFT_BORDER;
    //Set console BG color.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a_cell.getVerticalStreet()->getStreetColor());
    std::cout<<VERTICAL_STREET_MIDDLE;
    //Return console background color to its original state.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout<<VERTICAL_STREET_RIGHT_BORDER;
}

void TrafficSystem::printVerticalStreetMiddle(const Cell &a_cell)
{
    std::cout<<VERTICAL_STREET_LEFT_BORDER;
    //Set console BG color.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a_cell.getVerticalStreet()->getStreetColor());
    //Print car or empty street.
    if(a_cell.getCar())
    {
        std::cout<<*a_cell.getCar();
    }
    else
    {
        std::cout<<VERTICAL_STREET_MIDDLE;
    }
    //Return console background color to its original state.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout<<VERTICAL_STREET_RIGHT_BORDER;

}


void TrafficSystem::printVerticalStreetBottom(const Cell &a_cell) {
    std::cout<<VERTICAL_STREET_LEFT_BORDER;
    //Set console BG color.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a_cell.getVerticalStreet()->getStreetColor());
    std::cout<<VERTICAL_STREET_MIDDLE;
    //Return console background color to its original state.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout<<VERTICAL_STREET_RIGHT_BORDER;
}



bool TrafficSystem::isMovementPossible(const Car &a_car) const
{
    bool result;
    switch(a_car.getDirection())
    {
        case DriveDirection::up:
            result = canMoveUp(a_car);
            break;
        case DriveDirection::down:
            result = canMoveDown(a_car);
            break;
        case DriveDirection::left:
            result = canMoveLeft(a_car);
            break;
        case DriveDirection::right:
            result = canMoveRight(a_car);
            break;
    }
    return result;
}

bool TrafficSystem::canMoveLeft(const Car &a_car) const
{
    bool result = false;

    if(a_car.getX() > 0)
    {
        if(!this->m_traffic_table[a_car.getY()][a_car.getX() - 1].isJunction())
        {
            if(this->m_traffic_table[a_car.getY()][a_car.getX() - 1].isHorizontalStreet())
            {
                result = !this->m_traffic_table[a_car.getY()][a_car.getX() - 1].getCar();
            }
        }
        else
        {
            result = this->m_traffic_table[a_car.getY() - 1][a_car.getX()].getTrafficLight()->getTrafficLightStatus(Exit::left);
        }
    }

    return result;
}

bool TrafficSystem::canMoveRight(const Car &a_car) const
{
    bool result = false;

    if(a_car.getX() + 1< this->m_width)
    {
        if(!this->m_traffic_table[a_car.getY()][a_car.getX() + 1].isJunction())
        {
            if(this->m_traffic_table[a_car.getY()][a_car.getX() + 1].isHorizontalStreet())
            {
                result = !this->m_traffic_table[a_car.getY()][a_car.getX() + 1].getCar();
            }
        }
        else
        {
            result = this->m_traffic_table[a_car.getY() - 1][a_car.getX()].getTrafficLight()->getTrafficLightStatus(Exit::right);
        }
    }

    return result;
}

bool TrafficSystem::canMoveUp(const Car &a_car) const
{
    bool result = false;

    if(a_car.getY() > 0 )
    {
        if(!this->m_traffic_table[a_car.getY() - 1][a_car.getX()].isJunction())
        {
            if(this->m_traffic_table[a_car.getY() - 1][a_car.getX()].isVerticalStreet())
            {
                result = !this->m_traffic_table[a_car.getY() - 1][a_car.getX()].getCar();
            }
        }
        else
        {
            result = this->m_traffic_table[a_car.getY() - 1][a_car.getX()].getTrafficLight()->getTrafficLightStatus(Exit::up);
        }
    }

    return result;
}

bool TrafficSystem::canMoveDown(const Car &a_car) const
{
    bool result = false;

    if(a_car.getY() + 1 < this->m_length )
    {
        if(!this->m_traffic_table[a_car.getY() + 1][a_car.getX()].isJunction())
        {
            if(this->m_traffic_table[a_car.getY() + 1][a_car.getX()].isVerticalStreet())
            {
                result = !this->m_traffic_table[a_car.getY() + 1][a_car.getX()].getCar();
            }
        }
        else
        {
            result = this->m_traffic_table[a_car.getY() - 1][a_car.getX()].getTrafficLight()->getTrafficLightStatus(Exit::down);
        }
    }

    return result;
}

void TrafficSystem::driveCar(Car &a_car)
{
    this->m_traffic_table[a_car.getY()][a_car.getX()].removeCar();
    a_car.drive();
    this->m_traffic_table[a_car.getY()][a_car.getX()].setCar(&a_car);
}

bool TrafficSystem::isStreetEntranceFree(const Street &a_st) const{
    return !this->m_traffic_table[a_st.getY()][a_st.getX()].hasCar();
}

void TrafficSystem::addCars() {
    Car *car{nullptr};
    for(auto &s:this->m_streets)
    {
        if(isStreetEntranceFree(s))
        {
            DriveDirection direction = (s.getStreetDirection() == Direction::vertical) ?
                DriveDirection::down : DriveDirection::right;
            car = new Car(*this,s.getX(),s.getY(), direction);
        }
    }
}

void TrafficSystem::setCarOnStreet(Car *a_car, const Street &a_street)
{
    a_car->setX(a_street.getX());
    a_car->setY(a_street.getY());
    if(a_street.getStreetDirection() == Direction::vertical)
    {
        a_car->changeDriveDirection(DriveDirection::down);
    }
    else
    {
        a_car->changeDriveDirection(DriveDirection::right);
    }
    this->m_traffic_table[a_car->getY()][a_car->getX()].setCar(a_car);
    this->m_cars.push_back(a_car);
}

bool TrafficSystem::isOutOfRoad(const Car& a_car) const
{
    bool result = false;
    if (a_car.getX() == this->m_width || a_car.getY() == this->m_length)
    {
        result = true;
    }
    else if (a_car.getX() < 0 || a_car.getY() < 0)
    {
        result = true;
    }
    else if (a_car.getDirection() == DriveDirection::up || a_car.getDirection() == DriveDirection::down)
    {
        if (!this->m_traffic_table[a_car.getY()][a_car.getX()].isVerticalStreet())
        {
            result = true;
        }
    }
    else if (!this->m_traffic_table[a_car.getY()][a_car.getX()].isHorizontalStreet())
    {
        result = true;
    }

    return result;
}


