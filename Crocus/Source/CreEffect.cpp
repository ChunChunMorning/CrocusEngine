# include "../Effect.hpp"

namespace cre
{
	using ElementType = std::pair<std::unique_ptr<IEffect>, double>;

	Effect::Effect() : m_speed(1.0) {}

	void Effect::add(std::unique_ptr<IEffect>&& effect)
	{
		m_emitters.emplace_back(std::move(effect), 0);
	}

	void Effect::erase(double seconds)
	{
		Erase_if(m_emitters, [&](ElementType& e) {return e.second > seconds; });
	}

	void Effect::update(double deltaTime)
	{
		Erase_if(
			m_emitters,
			[&](ElementType& e) {
				e.second += m_speed * deltaTime;
				return !e.first->update(e.second);
			}
		);
	}
}
