# pragma once
# include <Siv3D.hpp>

namespace cre
{
	class Effect
	{
	private:

		double m_speed;

		Array<std::pair<std::unique_ptr<IEffect>, double>> m_emitters;

	public:

		Effect();

		double getSpeed() const { return m_speed; }

		bool hasEffects() const { return !m_emitters.empty(); }

		uint32 number() const { return static_cast<uint32>(m_emitters.size()); }

		double setSpeed(double speed) { return m_speed = speed; };

		void add(std::unique_ptr<IEffect>&& effect);

		template <class Emitter, class... Args>
		void add(Args&&... args)
		{
			add(std::make_unique<Emitter>(std::forward<Args>(args)...));
		}

		void erase(double seconds = 10);

		void clear()
		{
			m_emitters.clear();
		}

		void update(double deltaTime);
	};
}
