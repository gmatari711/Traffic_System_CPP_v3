#include "traffic_light.h"

void TrafficLights::runTrafficLights()
{
	while (true)
	{
		this->m_exit_queue.push(this->m_current_exit);
		this->m_current_exit = this->m_exit_queue.front();
		this->m_exit_queue.pop();
		Sleep(20000);
	}
}

TrafficLights::TrafficLights() :
	m_current_exit(Exit::left)
{}

void TrafficLights::insertExit(Exit a_exit)
{
	this->m_exit_queue.push(a_exit);
}

void TrafficLights::turnOnTrafficLights()
{
	this->m_traffic_light_thread = std::thread(&TrafficLights::runTrafficLights, this);
}

bool TrafficLights::getTrafficLightsStatus(Exit a_exit) const
{
	return this->m_current_exit == a_exit;
}

Exit TrafficLights::getActiveExit() const
{
	return m_current_exit;
}
