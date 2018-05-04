# include "../Intervaler.hpp"

namespace cre
{
	Intervaler::Intervaler(double interval, double elapsedTime) :
		m_interval(interval), m_elapsedTime(elapsedTime) {}

	void Intervaler::setInterval(double interval, bool resetElapsedTime)
	{
		m_interval = interval;

		if (resetElapsedTime)
		{
			m_elapsedTime = 0;
		}
	}

	bool Intervaler::check(double deltaTime)
	{
		m_elapsedTime += deltaTime;

		if (m_elapsedTime > m_interval)
		{
			m_elapsedTime -= m_interval;
			return true;
		}

		return false;
	}
}
