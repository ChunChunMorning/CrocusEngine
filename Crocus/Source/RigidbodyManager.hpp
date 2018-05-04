# pragma once
# include <map>
# include <Siv3D.hpp>
# include "../Intervaler.hpp"
# include "../Physics.hpp"
# include "../Pointer.hpp"

namespace cre
{
	using namespace s3d;

	class Rigidbody;

	class RigidbodyManager
	{
	private:

		Intervaler m_intervaler;

		std::map<Physics::Group, Array<weak_ptr<Rigidbody>>> m_rigidbodies;

	public:

		RigidbodyManager() : m_intervaler(1.0 / 60) {}

		void update();

		void escape();

		static void Add(const weak_ptr<Rigidbody>& rigidbody);

# ifdef _DEBUG
		void draw() const;
# endif
	};
}
