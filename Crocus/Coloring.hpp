# pragma once
# include <Siv3D.hpp>
# include "DeltaTime.hpp"

namespace cre
{
	namespace Coloring
	{
		constexpr uint32 Alpha(double alpha)
		{
			return static_cast<uint32>(255u * alpha);
		}

		inline double Blink(double speed = 20.0)
		{
			return (Math::Sin(speed * DeltaTime::GetElapsedTime()) + 1) / 2;
		}

		constexpr Color Transparentize(const Color& color, double alpha)
		{
			return Color(color, static_cast<uint32>(color.a * alpha));
		}
	}
}
