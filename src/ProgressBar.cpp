#include "ProgressBar.h"
#include <iostream>

Timer::Timer()
{
	Reset();
}

double Timer::Remains(double done)
{
	auto current = std::chrono::steady_clock::now();
	int lapse = std::chrono::duration_cast<std::chrono::seconds> (current - begin).count();
	double dLeft = (1 - done) * lapse / done;

	return dLeft;
	
}

void
Timer::Reset()
{
	begin = std::chrono::steady_clock::now();
}

ProgressBar::ProgressBar() {
	// Pongo el timepo a 0
	timer.Reset();
}

void
ProgressBar::Update(double done)
{
	int block = round(done * nLen);
	double seconds = timer.Remains(done);

	std::cout << "\r";
	printf("%.2f", done * 100);
	std::cout << "% ";
	if (int(seconds) < 60)
		std::cout << int(seconds) << " seconds ";
	else
		std::cout << int(seconds/60) << " minutes ";

	std::cout << "[" << std::string(block, '|') << std::string(nLen - block, ' ') << "]";
}
