# pragma once
# include <Siv3D.hpp>
# include "CameraDepth.hpp"
# include "Coloring.hpp"
# include "Component.hpp"

namespace cre
{
	class IDrawable
	{
	private:

		bool m_isActive;

		Color m_color;

		double m_alpha;

	public:

		IDrawable() :
			m_isActive(true), m_color(Palette::White), m_alpha(1.0) {}

		virtual ~IDrawable() = default;

		bool activate(bool isActive) { return m_isActive = isActive; }

		const Color& setColor(double alpha)
		{
			m_color.a = Coloring::Alpha(alpha);

			return m_color;
		}

		const Color& setColor(const Color& diffuse) { return m_color = diffuse; }

		double setAlpha(double alpha)
		{
			assert(InRange(alpha, 0.0, 1.0));

			return m_alpha = alpha;
		}

		bool isActive() const { return m_isActive; }

		const Color& color() const { return m_color; }

		double alpha() const { return m_alpha; }

		Color diffuse() const
		{
			return Color(m_color, static_cast<uint32>(m_color.a * m_alpha));
		}

		virtual CameraDepth depth() const = 0;

		virtual void draw() const = 0;
	};

	class Drawable : public Component, public IDrawable
	{
	public:

		virtual ~Drawable() = default;

		void init() override;
	};
}
