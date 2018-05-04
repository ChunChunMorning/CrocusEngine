# pragma once
# include <memory>

namespace cre
{
	using std::unique_ptr;
	using std::shared_ptr;
	using std::weak_ptr;

	template<class Type>
	class stupid_ptr
	{
	private:

		Type* m_ptr;

	public:

		stupid_ptr() = default;

		stupid_ptr(Type* other) : m_ptr(other) {}

		stupid_ptr(const unique_ptr<Type>& other) : m_ptr(other.get()) {}

		stupid_ptr(const shared_ptr<Type>& other) : m_ptr(other.get()) {}

		stupid_ptr(const weak_ptr<Type>& other) : m_ptr(other.lock().get()) {}

		explicit operator bool() const noexcept
		{
			return m_ptr != nullptr;
		}

		stupid_ptr<Type>& operator = (Type* other) noexcept
		{
			m_ptr = other;

			return *this;
		}

		stupid_ptr<Type>& operator = (const unique_ptr<Type>& other) noexcept
		{
			m_ptr = other.get();

			return *this;
		}

		stupid_ptr<Type>& operator = (const shared_ptr<Type>& other) noexcept
		{
			m_ptr = other.get();

			return *this;
		}

		stupid_ptr<Type>& operator = (const weak_ptr<Type>& other) noexcept
		{
			m_ptr = other.lock().get();

			return *this;
		}

		bool operator == (const stupid_ptr<Type>& other) const noexcept
		{
			return m_ptr == other.m_ptr;
		}

		bool operator == (const Type* other) const noexcept
		{
			return m_ptr == other;
		}

		bool operator != (const Type* other) const noexcept
		{
			return !(m_ptr == other);
		}

		Type& operator * () const noexcept
		{
			return *m_ptr;
		}

		Type* operator -> () const noexcept
		{
			return m_ptr;
		}
	};

	template<class Type>
	inline bool operator == (Type* a, const stupid_ptr<Type>& b) noexcept
	{
		return b == a;
	}

	template<class Type>
	inline bool operator != (Type* a, const stupid_ptr<Type>& b) noexcept
	{
		return b != a;
	}
}
