# include "../DeltaTime.hpp"
# include "../Engine.hpp"
# include "TimeManager.hpp"

namespace cre
{
	namespace DeltaTime
	{
		void Delay(double scale, double time)
		{
			Engine::GetTime()->delay(scale, time);
		}

		double GetDeltaTime()
		{
			return Engine::GetTime()->deltaTime();
		}

		double GetUnscaledDeltaTime()
		{
			return Engine::GetTime()->unscaledDeltaTime();
		}

		double GetTimeScale()
		{
			return Engine::GetTime()->timeScale();
		}

		double GetElapsedTime()
		{
			return Engine::GetTime()->elapsedTime();
		}
	}
}

