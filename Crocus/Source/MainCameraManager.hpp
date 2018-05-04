# pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "../Coordinate.hpp"

namespace cre
{
	using namespace s3d;

	class MainCameraManager : public BasicCamera2D
	{
	private:

		Vec3 m_currentPos;

		Vec3 m_targetPos;

		double m_targetScale;

	public:

		MainCameraManager::MainCameraManager() :
			BasicCamera2D(Vec2::Zero, Coordinate::PixelsPerUnit),
			m_currentPos(Vec3::Zero),
			m_targetPos(Vec3::Zero),
			m_targetScale(Coordinate::PixelsPerUnit) {}

		void update()
		{
			m_currentPos = Math::Lerp(m_currentPos, m_targetPos, 0.2);
			m_pos = Coordinate::Isometric(m_currentPos);
			m_scale = s3d::Math::Lerp(m_scale, m_targetScale, 0.1);
		}

		void setPos(const Vec3& pos)
		{
			m_currentPos = pos;
			BasicCamera2D::setPos(Coordinate::Isometric(pos));
			setTargetPos(pos);
		}

		void setTargetPos(const Vec3& pos)
		{
			m_targetPos = pos;
		}

		void setScale(double scale)
		{
			BasicCamera2D::setScale(scale);
			setTargetScale(scale);
		}

		void setTargetScale(double scale)
		{
			m_targetScale = scale;
		}

		const Vec3& getCurrentPos() const
		{
			return m_currentPos;
		}

		const Vec3& getTargetPos() const
		{
			return m_targetPos;
		}

		double getTargetScale() const
		{
			return m_targetScale;
		}
	};
}
