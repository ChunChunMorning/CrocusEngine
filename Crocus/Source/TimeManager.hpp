# pragma once
# include <Siv3D.hpp>

namespace cre
{
	using namespace s3d;

	class TimeManager
	{
	private:

		struct Delay
		{
			double scale;
			double time;
		};

		double m_deltaTime;

		double m_currentDeltaTime;

		double m_timeScale;

		double m_elapsedTime;

		Array<Delay> m_delays;

		Stopwatch m_stopwatch;

	public:

		TimeManager() :
			m_deltaTime(0), m_currentDeltaTime(0),
			m_timeScale(1), m_elapsedTime(0) {}

		void update()
		{
			m_deltaTime = Min(m_stopwatch.ms() / 1000.0, 1 / 60.0);
			m_timeScale = 1.0;

			for (auto& delay : m_delays)
			{
				m_timeScale *= delay.scale;
				delay.time -= m_deltaTime;
			}

			Erase_if(m_delays, [](const Delay& delay) { return delay.time < 0; });

			m_currentDeltaTime = m_deltaTime * m_timeScale;
			m_elapsedTime += m_currentDeltaTime;
			m_stopwatch.restart();
		}

		void delay(double scale, double time)
		{
			m_delays.push_back({scale, time});
		}

		double unscaledDeltaTime() const
		{
			return m_deltaTime;
		}

		double deltaTime() const
		{
			return m_currentDeltaTime;
		}

		double timeScale() const
		{
			return m_timeScale;
		}

		double elapsedTime() const
		{
			return m_elapsedTime;
		}
	};
}
