#ifndef TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_LIGHT_H
#define TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_LIGHT_H

#include<Windows.h>
#include <thread>
#include <mutex>


enum class Exit { left, up, right, down};

class TrafficLight
{
private:
	std::thread m_traffic_light_thread;
	Exit m_current_exit;
	void runTrafficLight();
public:
	TrafficLight();
	bool getTrafficLightStatus(Exit a_exit)const;
	Exit getActiveExit()const;

};

#endif