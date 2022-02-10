#pragma once
#include <chrono>


class Timer {

public:
    Timer();

    double Remains(double done);
    void Reset();

    std::chrono::steady_clock::time_point begin;
};


class ProgressBar {

public:

    ProgressBar();

    void Update(double done);

    Timer timer;
    int nLen{ 20 };
};
