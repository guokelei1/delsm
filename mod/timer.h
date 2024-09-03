//
// Created by daiyi on 2020/02/02.
// Internal implementation for timers used in Stats class.

#ifndef LEVELDB_TIMER_H
#define LEVELDB_TIMER_H


#include <cstdint>
#include <ctime>
#include <utility>
#include <vector>
#include "mod/util.h"

using std::string;

namespace delsm {


    class Timer {
        uint64_t time_started;
        uint64_t time_accumulated;
        bool started;
        string name;

    public:
        void Start();
        void  Pause();
        void Reset();
        uint64_t Time();
        const string& GetName() const { return name; }

        Timer(const std::string& name);
        ~Timer() = default;
    };


     class Stats {
    private:
        static Stats* singleton;
        Stats();

        std::vector<Timer> timers;
    public:
        uint64_t initial_time;

        static Stats* GetInstance();
        void StartTimer(uint32_t id);
        void PauseTimer(uint32_t id);
        void ResetTimer(uint32_t id);
        uint64_t ReportTime(uint32_t id);
        void ReportTime();
        void ResetAll();
        ~Stats();
    };


}


#endif //LEVELDB_TIMER_H
