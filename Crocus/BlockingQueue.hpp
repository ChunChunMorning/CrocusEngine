# pragma once
# include <mutex>
# include <queue>

template<class Type>
class BlockingQueue
{
private:

	std::queue<Type> m_queue;

	std::mutex m_mutex;

public:

	void push(const Type& value)
	{
		const std::lock_guard<std::mutex> lock(m_mutex);

		m_queue.push(value);
	}

	void push(Type&& value)
	{
		const std::lock_guard<std::mutex> lock(m_mutex);

		m_queue.push(std::move(value));
	}

	bool try_pop(Type& to)
	{
		const std::lock_guard<std::mutex> lock(m_mutex);

		if (m_queue.empty())
		{
			return false;
		}

		to = std::move(m_queue.front());

		m_queue.pop();

		return true;
	}

	bool empty()
	{
		const std::lock_guard<std::mutex> lock(m_mutex);

		return m_queue.empty();
	}
};
