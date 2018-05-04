# pragma once
# include <Siv3D.hpp>

namespace cre
{
	namespace Physics
	{
		class Group
		{
			friend std::basic_ostream<wchar>& operator << (std::basic_ostream<wchar>&, Group);

		private:

			uint16 m_value;

		public:

			Group() = default;

			constexpr Group(uint16 value) : m_value(value) {}

			Group& operator = (uint16 value) { m_value = value; return *this; }

			constexpr Group operator ~ () const { return ~m_value; }

			constexpr Group operator | (Group other) const { return m_value | other.m_value; }

			constexpr bool operator < (Group other) const { return m_value < other.m_value; }

			constexpr bool operator > (Group other) const { return other < *this; }

			constexpr bool operator <= (Group other) const { return !(other < *this); }

			constexpr bool operator >= (Group other) const { return !(other > *this); }

			constexpr bool operator == (Group other) const { return m_value == other.m_value; }

			constexpr bool operator != (Group other) const { return !(*this == other); }

			constexpr operator uint16() const { return m_value; };

			constexpr bool isComplex() const
			{
				return (m_value & (m_value - 1)) != 0;
			}

			constexpr bool contain(Group grounp) const
			{
				return (m_value & grounp.m_value) == grounp.m_value;
			}
		};

		namespace Groups
		{
			constexpr Group Item		= 0b000000001;
			constexpr Group Player		= 0b000000010;
			constexpr Group Enemy		= 0b000000100;
			constexpr Group PlayerWall	= 0b000001000;
			constexpr Group EnemyWall	= 0b000010000;
			constexpr Group Structure	= 0b000100000;
			constexpr Group Environment	= 0b001000000;

			constexpr Group Attack		= 0b010000000;
			constexpr Group Affodance	= 0b100000000;

			constexpr Group Default		= Player | Enemy | Structure | Environment;
			constexpr Group ItemBody	= Structure | Environment;
			constexpr Group PlayerBody	= Player | Enemy | PlayerWall | Structure | Environment;
			constexpr Group EnemyBody	= Player | Enemy | EnemyWall | Structure | Environment;
			constexpr Group All			= 0xFFFF;
		}

		inline std::basic_ostream<wchar>& operator << (std::basic_ostream<wchar>& os, Group group)
		{
			return os << ToString(group.m_value, 2);
		}

		inline std::basic_istream<wchar>& operator >> (std::basic_istream<wchar>& is, Group& group)
		{
			String str;

			is >> str;

			const auto lower = str.lower();

			if (lower == L"item")
			{
				group = Groups::Item;
			}
			else if (lower == L"player")
			{
				group = Groups::Player;
			}
			else if (lower == L"enemy")
			{
				group = Groups::Enemy;
			}
			else if (lower == L"playerwall")
			{
				group = Groups::PlayerWall;
			}
			else if (lower == L"enemywall")
			{
				group = Groups::EnemyWall;
			}
			else if (lower == L"structure")
			{
				group = Groups::Structure;
			}
			else if (lower == L"environment")
			{
				group = Groups::Environment;
			}
			else if (lower == L"attack")
			{
				group = Groups::Attack;
			}
			else if (lower == L"affordance")
			{
				group = Groups::Affodance;
			}
			else if (lower == L"default")
			{
				group = Groups::Default;
			}
			else if (lower == L"itembody")
			{
				group = Groups::ItemBody;
			}
			else if (lower == L"playerbody")
			{
				group = Groups::PlayerBody;
			}
			else if (lower == L"enemybody")
			{
				group = Groups::EnemyBody;
			}
			else if (lower == L"all")
			{
				group = Groups::All;
			}
			else
			{
				group = FromString<uint16>(str, 2);
			}

			return is;
		}
	}
}
