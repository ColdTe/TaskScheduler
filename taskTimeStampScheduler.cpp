#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

class Task{
  private:
    int priority{};
    std::chrono::local_time<std::chrono::minutes> startTime{};
    std::chrono::local_time<std::chrono::minutes> finishTime{};
  public:
    Task(const int task_priority,const int year_s,const unsigned int month_s,const unsigned int day_s,const unsigned int hours_s,const unsigned int minutes_s,const int year_f,const unsigned int month_f,const unsigned int day_f,const unsigned int hours_f,const unsigned int minutes_f):
      priority{task_priority},
      startTime{std::chrono::local_days{std::chrono::year{year_s} / std::chrono::month{month_s} / std::chrono::day{day_s}} + std::chrono::hours{hours_s} + std::chrono::minutes{minutes_s}},
      finishTime{std::chrono::local_days{std::chrono::year{year_f} / std::chrono::month{month_f} / std::chrono::day{day_f}} + std::chrono::hours{hours_f} + std::chrono::minutes{minutes_f}}
    {}

    std::chrono::local_time<std::chrono::minutes> getStartTime() const{
      return startTime;
    }
    
    std::chrono::local_time<std::chrono::minutes> getFinishTime() const{
      return finishTime;
    }

    int getPriority() const{
      return priority;
    }

};

std::ostream& operator<<(std::ostream &out,const Task &task){
  out << "Priority: " << task.getPriority() << '\n';
  out << "StartTime: " << task.getStartTime() << '\n';
  out << "FinishTime: " << task.getFinishTime() << '\n';
  return out;
}

bool comparator(const Task &task1,const Task &task2){
  return task1.getFinishTime() < task2.getFinishTime();
}

std::vector<Task> taskScheduler(std::vector<Task> tasks){
  std::sort(tasks.begin(),tasks.end(),comparator);

  std::vector<Task> S;
  if(tasks.empty())
    return S;
  S.push_back(tasks[0]);
  std::chrono::local_time<std::chrono::minutes> startTime = tasks[0].getStartTime();
  std::chrono::local_time<std::chrono::minutes> lastFinishTime = tasks[0].getFinishTime();
  for(std::size_t i{1};i < tasks.size();++i){
    if(tasks[i].getStartTime() >= lastFinishTime){
      S.push_back(tasks[i]);
      lastFinishTime = tasks[i].getFinishTime();
    }
  }
  return S;
}


int main(){
  std::vector<Task> tasks {
        Task(1, 2026, 10, 14, 20, 0, 2026, 10, 14, 22, 30),
        Task(2, 2026, 10, 14, 22, 0, 2026, 10, 15, 1, 0),
        Task(3, 2026, 10, 15, 0, 30, 2026, 10, 15, 2, 30),
        Task(4, 2026, 10, 15, 1, 30, 2026, 10, 15, 3, 30)
    };
  std::vector<Task> scheduledTasks{taskScheduler(tasks)};
  for(const auto &x : scheduledTasks){
    std::cout << x << "\n\n";
  }
}

