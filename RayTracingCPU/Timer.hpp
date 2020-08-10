#pragma once
#include <memory>
#include <iostream>
#include <chrono>
#include <map>

namespace Alice::RayTracingCPU
{
	enum class TimeUnit
	{
		SS = 0, //√Î
		MS,     //∫¡√Î
		US,     //Œ¢√Î
		NS      //ƒ…√Î
	};

	class Timer
	{
		typedef std::chrono::high_resolution_clock hrc;
		typedef std::chrono::time_point<std::chrono::high_resolution_clock>  tp_hrc;
	public:
		Timer():start_(hrc::now()),end_(hrc::now()){}
		virtual ~Timer(){}

		void Start()
		{
			start_ = hrc::now();
		}

		void Stop(){
			end_ = hrc::now();
		}

		void Reset(){
			start_ = hrc::now();
			end_ = hrc::now();
		}

		double Elapsed(TimeUnit type = TimeUnit::MS)
		{
			if(type == TimeUnit::SS)
			{
				return std::chrono::duration_cast<std::chrono::seconds>(end_ - start_).count();
			}
			else if(type == TimeUnit::MS)
			{
				return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
			}
			else if(type == TimeUnit::US)
			{
				return std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
			}
			else if(type == TimeUnit::NS)
			{
				return std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_).count();
			}
		}

	private:
		tp_hrc start_;
		tp_hrc end_;
	};//end Timer

	class TimerFactory{
	public:
		TimerFactory(){}
		virtual ~TimerFactory(){
			if(!timers_.empty()){
				timers_.clear();
			}
		}

		std::shared_ptr<Timer> GetTimer(const std::string& name){
			if(timers_.find(name) != timers_.end()){
				return timers_[name];
			}else{
				timers_[name] = std::make_shared<Timer>();
				return timers_[name];
			}
		}
	private:
		std::map<std::string,std::shared_ptr<Timer> > timers_;
	}; //end TimerFactory

	//int main(){
	//	Timer timer;
	//	timer.Start();
	//	sleep(1);
	//	timer.Stop();
	//	std::cout<<"use time seconds:"<<timer.Elapsed(SS)<<std::endl; 
	//	std::cout<<"use time milliseconds:"<<timer.Elapsed(MS)<<std::endl;
	//	std::cout<<"use time microseconds:"<<timer.Elapsed(US)<<std::endl;
	//	std::cout<<"use time nanoseconds:"<<timer.Elapsed(NS)<<std::endl;
	//}
}