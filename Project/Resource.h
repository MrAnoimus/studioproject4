#pragma once
class CResource
{

private:
	static int NumOfFood;
	static int NumOfMoney;
	static int NumOfManPower;
	static int NumOfCitizen;
	static int Win;
	static int maxManPower;
public:


	int GetFood();
	int GetMoney();
	int GetManPower();
	int GetMaxManPower();
	int GetCitizen();
	int GetWin();
	void Update();
	void SetWin(int NewWin);
	void SetFood(int NewFood);
	void SetMoney(int NewMoney);
	void SetManpower(int NewManPower);
	void SetCitizen(int NewCitizen);


	CResource(void);
	~CResource(void);
};

