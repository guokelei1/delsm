//
// Created by daiyi on 2020/02/02.
//

#include "timer.h"

#include <cassert>


namespace delsm {

Timer::Timer(const std::string& name):time_accumulated(0), started(false),name(name) {}

void Timer::Start() {
  assert(!started);
  time_started =delsm::env->NowMicros();
  started = true;
}

void Timer::Pause() {
  assert(started);
  time_accumulated += (delsm::env->NowMicros() - time_started);
    return ;
}

void Timer::Reset() {
  time_accumulated = 0;
  started = false;
}

uint64_t Timer::Time() {
  // assert(!started);
  return time_accumulated;
}

Stats* Stats::singleton = nullptr;

Stats::Stats() :  initial_time(__rdtsc()) {
        std::vector<std::string> predefinedNames = {
        "Alpha", "Beta", "Gamma", "Delta", "Epsilon",
    };
    // 默认名字前缀
    std::string defaultNamePrefix = "TimerDefault";

    for (int i = 0; i < 20; ++i) {
        std::string timerName;
        if (i < predefinedNames.size()) {
            // 使用预定义的名字
            timerName = predefinedNames[i];
        } else {
            // 使用默认名字
            timerName = defaultNamePrefix + std::to_string(i - predefinedNames.size());
        }
        timers.emplace_back(timerName); // 使用emplace_back来直接在容器中构造Timer对象
    }
  
}

Stats* Stats::GetInstance() {
  if (!singleton) singleton = new Stats();
  return singleton;
}

void Stats::StartTimer(uint32_t id) {
  Timer& timer = timers[id];
  timer.Start();
}
void Stats::PauseTimer(uint32_t id) {
  Timer& timer = timers[id];
  timer.Pause();
  return ;
}

void Stats::ResetTimer(uint32_t id) {
  Timer& timer = timers[id];
  timer.Reset();
}

uint64_t Stats::ReportTime(uint32_t id) {
  Timer& timer = timers[id];
  return timer.Time();
}

void Stats::ReportTime() {
  for (int i = 0; i < timers.size(); ++i) {
    printf("Timer %u: %lu :%s\n", i, timers[i].Time(),timers[i].GetName().c_str());
  }
}



void Stats::ResetAll() {
  for (Timer& t : timers) t.Reset();
  initial_time = __rdtsc();
}

Stats::~Stats() { ReportTime(); }

}  // namespace delsm