#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ITicket
{
public:
	virtual int Price() = 0;
	virtual string Description() = 0;
};

class BaseEntryTicket : public ITicket
{
public:
	int Price() override
	{
		cout << "Base ticket price is $10" << endl;
		return 10;
	}

	string Description() override
	{
		cout << "It is just an Entry ticket to see Garden" << endl;
		return "Desc: It is just an Entry ticket to see Garden";
	}

};

class ConcreateDecorator : public ITicket
{
protected:
	shared_ptr<ITicket> addon_ticket;
public: 
	ConcreateDecorator(shared_ptr<ITicket> ticket) : addon_ticket{ ticket }
	{
			
	}

	int Price() override
	{
		cout << "Concrete Decorator - Price" << endl;
		return addon_ticket->Price();
	}

	string Description() override
	{
		cout << "Concrete Decorator - Decription" << endl;
		return addon_ticket->Description();
	}

};

class PalaceTicket : public ConcreateDecorator
{
public:
	int Price() override
	{
		cout << "Palace addon - $7" << endl;
		return addon_ticket->Price() + 7;
	}

	string Description() override
	{
		cout << "Palace" << endl;
		return addon_ticket->Description() + "Palace";
	}

	PalaceTicket(shared_ptr<ITicket> ticket) : ConcreateDecorator(ticket)
	{

	}

};

class ToyTrainTicket : public ConcreateDecorator
{
public:
	int Price() override
	{
		cout << "ToyTrain addon - $4" << endl;
		return addon_ticket->Price() + 7;
	}

	string Description() override
	{
		cout << "ToyTrain" << endl;
		return addon_ticket->Description() + "ToyTrain";
	}
};

int main()
{
	//Base + Palace
	shared_ptr<ITicket> my_ticket = std::make_shared<BaseEntryTicket>();
	my_ticket = std::make_shared<PalaceTicket>(my_ticket);

	cout << "Price: "<< my_ticket->Price() << endl;
	cout << "Final Desc: " << my_ticket->Description() << endl;



	return 0;
}