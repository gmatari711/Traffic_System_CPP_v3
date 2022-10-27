#include "traffic_light.h"

void TrafficLight::runTrafficLight()
{
	while (true)
	{

		switch (this->m_current_exit)
		{
		case Exit::up:
			this->m_current_exit = Exit::right;
			break;
		case Exit::right:
			this->m_current_exit = Exit::down;
			break;
		case Exit::down:
			this->m_current_exit = Exit::left;
			break;
		case Exit::left:
			this->m_current_exit = Exit::up;
			break;
		}
		Sleep(20000);

	}
}

TrafficLight::TrafficLight() :
	m_current_exit(Exit::left),
	m_traffic_light_thread(&TrafficLight::runTrafficLight,this)
{}

bool TrafficLight::getTrafficLightStatus(Exit a_exit) const
{
	return this->m_current_exit == a_exit;
}

Exit TrafficLight::getActiveExit() const
{
	return m_current_exit;
}
