# pragma once
# include "DeltaTime.hpp"

namespace cre
{
	class Intervaler
	{
	private:

		double m_interval;

		double m_elapsedTime;

	public:

		Intervaler() = default;

		Intervaler(double interval, double elapsedTime = 0);

		double interval() const { return m_interval; };

		double elapsedTime() const { return m_elapsedTime; };

		void setInterval(double interval, bool resetElapsedTime);

		void reset(double elapsedTime = 0)
		{
			m_elapsedTime = elapsedTime;
		}

		bool check()
		{
			return check(DeltaTime::GetDeltaTime());
		}

		bool check(double deltaTime);
	};
}
