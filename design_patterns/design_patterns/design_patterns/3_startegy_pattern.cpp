#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class IBonusCalcullation_Startegy
{
public:
	virtual int BonusCalcullation(int emp_id) = 0;

};

class BonusOnGrade : public IBonusCalcullation_Startegy
{
public:
	int BonusCalcullation(int emp_id) override
	{
		//Grade specific calcullation
		cout << "Bonus on Grade!!!!" << endl;
		return 10;
	}

	BonusOnGrade()
	{
		cout << "Bonus on Grade ctor" << endl;
	}

	~BonusOnGrade()
	{
		cout << "Bonus on Grade dtor" << endl;
	}

	BonusOnGrade& operator=(BonusOnGrade&& other)
	{
		cout << "Bonus on grade assignment move operator" << endl;
		return *this;
	}
	BonusOnGrade& operator=(BonusOnGrade& other)
	{
		cout << "Bonus on grade normal assignment operator" << endl;
		return *this;
	}
	BonusOnGrade(BonusOnGrade&& other)
	{
		cout << "Bonus on grade move ctor" << endl;
		*this = std::move(other);
	}
	BonusOnGrade(const BonusOnGrade& other)
	{
		cout << "Bonus on grade copy ctor" << endl;
	}

};

class BonusOnMerit : public IBonusCalcullation_Startegy
{
public:
	int BonusCalcullation(int emp_id) override
	{
		//Merit specific calcullation
		cout << "Bonus on merit!!!!" << endl;
		return 15;
	}

	BonusOnMerit()
	{
		cout << "Bonus on merit ctor" << endl;
	}

	~BonusOnMerit()
	{
		cout << "Bonus on merit dtor" << endl;
	}


	BonusOnMerit& operator=(BonusOnMerit&& other)
	{
		cout << "Bonus on merit move asiisgnment" << endl;
		return *this;
	}

	BonusOnMerit& operator=(BonusOnMerit& other)
	{
		cout << "Bonus on merit normal asiisgnment" << endl;
		return *this;
	}

	BonusOnMerit(BonusOnMerit&& other)
	{
		cout << "Bonus on merit move ctor" << endl;
		*this = std::move(other);
	}


	BonusOnMerit(const BonusOnMerit& other)
	{
		cout << "Bonus on merit copy ctor" << endl;
	}
};

class BonusManager
{

	std::unique_ptr<IBonusCalcullation_Startegy> bonus_calcullator;
	IBonusCalcullation_Startegy* bonus_calcullator1;

public:
	void SetStartegy(std::unique_ptr<IBonusCalcullation_Startegy> p)
	{
		bonus_calcullator = std::move(p);
	}

	int ExecuteBonus(int emp_id)
	{
		return bonus_calcullator->BonusCalcullation(emp_id);
	}

	void ResetStartegy()
	{

		bonus_calcullator1 = bonus_calcullator.get();
		bonus_calcullator.reset();
		//bonus_calcullator1.reset();

	}
};

int main3()
{

	int emp_id;
	int startegy;

	cin >> emp_id;

	cin >> startegy;

	int bonus = 0;
	{
		BonusManager bonus_manger;
		if (startegy == 1)
		{
			bonus_manger.SetStartegy(make_unique<BonusOnGrade>());
		}
		else if (startegy == 2)
		{
			bonus_manger.SetStartegy(make_unique<BonusOnMerit>());
		}

		bonus = bonus_manger.ExecuteBonus(emp_id);

		bonus_manger.ResetStartegy();
	}

	vector<BonusOnGrade> v;
	{
		
		//BonusOnMerit temp;
		//v.push_back(temp);
		v.push_back(BonusOnGrade());
	}
	getchar();
	int t;
	cin >> t;
	cout << "Bonus calc complete!!" << endl;
	

	return bonus;
}