#include "GameTime.h"

CGameTime::CGameTime()
{

}
CGameTime::~CGameTime()
{

}
void CGameTime::Init()
{
	Day = 1;
	Hour = 11;
	Minute = 0;
	Second = 0.0f;
	Fincrement = 1.0f;
	TimeFrame = "AM";
	Iincrement = 1;
}
void CGameTime::Update()
{
	GetTimeFrame();
	Second += Fincrement;
	if(Second>59)
	{
		Minute += Iincrement;
		Second = 0.0f;
	}
	if(Minute>59)
	{
		Hour += Iincrement;
		Minute = 0;
	}
	if(Hour>23)
	{
		Hour = 0;
		Day+=Iincrement;
	}
	if(Day>30)
	{
		Day = 0;
	}
}
//set
void CGameTime::SetDay(int d)
{
	Day = d;
}
void CGameTime::SetHour(int hr)
{
	Hour = hr;
}
void CGameTime::SetMinute(int min)
{
	Minute = min;
}
void CGameTime::SetSecond(int sec)
{
	Second = sec;
}

//get
int CGameTime::GetDay(void)
{
	return Day;
}
int CGameTime::GetHour(void)
{
	return Hour;
}
int CGameTime::GetMinute(void)
{
	return Minute;
}
int CGameTime::GetSecond(void)
{
	return Second;
}
string CGameTime::GetTimeFrame(void)
{
	if(Hour<12)
	{
		TimeFrame = "AM";
	}else
	{
		TimeFrame = "PM";
	}
	return TimeFrame;
}