#pragma once
#include <stdio.h>
#include <iostream>
#include <string>


class CGameTime
{
	private:
		int Day;
		int Hour;
		int Minute;
		float Second;
		std::string TimeFrame;
		std::string CurrentTime;
		
	public:
		CGameTime();
		~CGameTime();
		bool daycheck;
		void Init();
		void Update();
		//set
		void SetDay(int d);
		void SetHour(int hr);
		void SetMinute(int min);
		void SetSecond(int sec);
		void SetTimeFrame(std::string tf);
		//get
		int GetDay(void);
		int GetHour(void);
		int GetMinute(void);
		int GetSecond(void);
		std::string GetTimeFrame(void);
		float Fincrement;
		float Iincrement;
		float HrIncrement;
		float DayIncrement;
};

