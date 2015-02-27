#pragma once
#include <iostream>
#include <string>
using namespace std;

class CGameTime
{
	private:
		int Day;
		int Hour;
		int Minute;
		float Second;
		string TimeFrame;
		string CurrentTime;
		float Fincrement;
		float Iincrement;
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
		void SetTimeFrame(string tf);
		//get
		int GetDay(void);
		int GetHour(void);
		int GetMinute(void);
		int GetSecond(void);
		string GetTimeFrame(void);
};

