#pragma once
class CResource
{

private:
	static int NumOfFood;
	static int NumOfMoney;
	static int NumOfManPower;
	static int NumOfCitizen;
public:

	int GetFood();
	int GetMoney();
	int GetManPower();
	int GetCitizen();

	void SetFood(int NewFood);
	void SetMoney(int NewMoney);
	void SetManpower(int NewManPower);
	void SetCitizen(int NewCitizen);


	CResource(void);
	~CResource(void);
};

