#pragma once
#include <chrono>
#include <memory>

class Stopwatch
{
	// ���삵�Ă��邩�̃t���O
// true : ���쒆 / false : ��~��
	bool isRunning = false;
	// ����J�n����
	std::chrono::system_clock::time_point begin;
	// ����J�n����
	std::chrono::system_clock::time_point end;
	// ���v����
	std::chrono::nanoseconds elapsed;

	Stopwatch() = default; // CreateNew or StartNew�ō���āI

public:

	// �Ӗ��Ȃ��Ǝv���̂�move�ȊO�֎~
	~Stopwatch() = default;
	Stopwatch(const Stopwatch&) = delete;
	Stopwatch& operator=(const Stopwatch) = delete;
	Stopwatch(Stopwatch&&) = default;

	Stopwatch& operator=(Stopwatch&&) = default;

	bool getIsRunning() { return this->isRunning; }

	// �C�ӂ̌^�Ōv�����Ԃ����o��
	// Tempalte
	//   Unit  : �擾���������Ԃ̌^
	//   Ratio : ���Ԃ̒P��
	template <typename Unit, class Ratio>
	Unit getElapsed()
	{
		if (this->isRunning)
		{
			return std::chrono::duration_cast<std::chrono::duration<Unit, Ratio>>(
				std::chrono::system_clock::now() - this->begin).count(); // TooLong!!
		}
		else
		{
			return std::chrono::duration_cast<std::chrono::duration<Unit, Ratio>>(this->elapsed).count();
		}
	}

	// �o�ߎ��Ԃ�b�̔{���x���������_�Ƃ��Ď��o��
	double getElapsedSeconds()
	{
		return this->getElapsed<double, std::ratio<1>>();
	}

	// �o�ߎ��Ԃ��~���b�̔{���x���������_�Ƃ��Ď��o��
	double getElapsedMilliseconds()
	{
		return this->getElapsed<double, std::milli>();
	}

	// �o�ߎ��Ԃ��i�m�b�Ƃ��Ď��o��
	long long getElapsedNanoseconds()
	{
		return this->getElapsed<long long, std::nano>();
	}

	void reset()
	{
		elapsed = std::chrono::nanoseconds(0);
		begin = end = std::chrono::system_clock::now();
	}

	void restart()
	{
		this->reset();
		this->start();
	}

	void start()
	{
		if (this->isRunning)
		{
			return;
		}

		this->isRunning = true;
		begin = end = std::chrono::system_clock::now();
	}

	void stop()
	{
		if (!this->isRunning)
		{
			return;
		}

		this->isRunning = false;
		end = std::chrono::system_clock::now();
		this->elapsed = this->elapsed + std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	}

	static std::unique_ptr<Stopwatch> createNew()
	{
		std::unique_ptr<Stopwatch> sw(new Stopwatch());
		return sw;
	}

	static std::unique_ptr<Stopwatch> startNew()
	{
		auto sw = createNew();
		sw->start();
		return sw;
	}


};

