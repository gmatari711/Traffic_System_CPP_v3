#ifndef TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_LIGHT_H
#define TRAFFIC_SYSTEM_CPP_V2_TRAFFIC_LIGHT_H

#include<Windows.h>
#include <thread>
#include <mutex>
#include <queue>


enum class Exit { left, up, right, down};

class TrafficLights
{
private:
	std::thread m_traffic_light_thread;
	Exit m_current_exit;
	std::queue<Exit> m_exit_queue{};
	void runTrafficLights();
public:
	TrafficLights();
	void insertExit(Exit a_exit);
	void turnOnTrafficLights();
	bool getTrafficLightsStatus(Exit a_exit)const;
	Exit getActiveExit()const;

};

#endif