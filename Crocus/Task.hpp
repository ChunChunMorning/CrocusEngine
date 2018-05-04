# pragma once
# include <atomic>
# include <thread>

class Task
{
private:

	std::atomic<bool> m_isDone;

	std::thread m_thread;

public:

	Task() : m_isDone(true) {}

	Task(const std::function<void()>& task) :
		m_isDone(false), m_thread([this, task]() { task(); m_isDone.store(true); }) {}

	~Task()
	{
		wait();
	}

	void start(const std::function<void()>& task)
	{
		wait();

		m_isDone = false;
		m_thread = std::thread([this, task]() { task(); m_isDone.store(true); });
	}

	void wait()
	{
		if (m_thread.joinable())
		{
			m_thread.join();
		}
	}

	bool isDone() const
	{
		return m_isDone.load();
	}
};
