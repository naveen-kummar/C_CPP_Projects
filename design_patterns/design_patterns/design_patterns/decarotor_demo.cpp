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
	virtual bool IsParkingAvailed() = 0;
};



class BaseTicket : public ITicket
{
public:

	BaseTicket() : Price_{10},
		Description_{"Base Entry Ticket"},
		ParkingAvailed_{false}
	{

	}

	int Price()
	{
		return Price_;
	}
	string Description()
	{
		return Description_;
	}

	bool IsParkingAvailed()
	{
		return ParkingAvailed_;
	}

private:
	bool ParkingAvailed_;
	int Price_;
	string Description_;
};



class ConcreateDecorator : public ITicket
{
protected:
	ITicket *addon_ticket;
public:
	ConcreateDecorator(ITicket *ticket) : addon_ticket{ ticket }
	{

	}

	int Price() override
	{
		//cout << "Concrete Decorator - Price" << endl;
		return addon_ticket->Price();
	}

	string Description() override
	{
		//cout << "Concrete Decorator - Decription" << endl;
		return addon_ticket->Description();
	}

	bool IsParkingAvailed()
	{
		return addon_ticket->IsParkingAvailed();
	}

};

class ToyTrainTicket : public ConcreateDecorator
{
public:
	int Price() override
	{
		//cout << "ToyTrain addon - $4" << endl;
		return addon_ticket->Price() + 4;
	}

	string Description() override
	{
		//cout << "ToyTrain" << endl;
		return addon_ticket->Description() + " + ToyTrain";
	}

	ToyTrainTicket(ITicket* ticket) : ConcreateDecorator(ticket)
	{

	}
};


int main()
{
	//Base + Palace
	ITicket *my_ticket = new ToyTrainTicket(new BaseTicket());

	cout << ">>>> Price for Base  : " << my_ticket->Price() << endl;
	cout << ">>>>> Description:  " << my_ticket->Description() << endl;

	getchar();

	return 0;
}
