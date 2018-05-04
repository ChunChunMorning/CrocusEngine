# pragma once

namespace cre
{
	namespace DeltaTime
	{
		void Delay(double scale, double time);

		double GetDeltaTime();

		double GetUnscaledDeltaTime();

		double GetTimeScale();

		double GetElapsedTime();
	}
}
