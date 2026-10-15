#include<iostream>
#include<vector>
#include<algorithm>

struct task{
  int priority;
  int startTime;
  int finishTime;
};

bool comparator(const task &task1, const task &task2){
  return task1.finishTime < task2.finishTime;
}

std::vector<task> taskScheduler(std::vector<task> &Tasks){
  std::sort(Tasks.begin(),Tasks.end(),comparator);
  std::vector<task> S;
  if(Tasks.empty())
    return S;
  S.push_back(Tasks[0]);
  int lastTime = Tasks[0].finishTime;
  for(std::size_t j{1};j < Tasks.size();++j){
    if(Tasks[j].startTime >= lastTime){
      S.push_back(Tasks[j]);
      lastTime = Tasks[j].finishTime;
    }
  }
  return S;
}

int main(){
  std::vector<task> tasks{
    {1,1,4},
    {2,3,5},
    {3,0,6},
    {4,5,7}
  };
  std::vector<task> scheduledTasks = taskScheduler(tasks);
  for(const auto& x : scheduledTasks){
    std::cout << "ID:  " << x.priority << "\nStart: " << x.startTime << "\nFinish: " << x.finishTime << "\n\n";
  }
}
