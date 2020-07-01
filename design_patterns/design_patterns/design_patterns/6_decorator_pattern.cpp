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
		//cout << "Base ticket price is $10" << endl;
		return 10;
	}

	string Description() override
	{
		//cout << "It is just an Entry ticket to see Garden" << endl;
		return "Base Ticket";
	}

};

class ConcreateDecorator : public ITicket
{
protected:
	unique_ptr<ITicket> addon_ticket;
public: 
	ConcreateDecorator(unique_ptr<ITicket> ticket) : addon_ticket{ std::move(ticket) }
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

};

class PalaceTicket : public ConcreateDecorator
{
public:
	int Price() override
	{
		//cout << "Palace addon - $7" << endl;
		return addon_ticket->Price() + 7;
	}

	string Description() override
	{
		//cout << "Palace" << endl;
		return addon_ticket->Description() + " + Palace";
	}

	PalaceTicket(unique_ptr<ITicket> ticket) : ConcreateDecorator(std::move(ticket))
	{

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

	ToyTrainTicket(unique_ptr<ITicket> ticket) : ConcreateDecorator(std::move(ticket))
	{

	}
};

int main6()
{
	//Base + Palace
	unique_ptr<ITicket> my_ticket = std::make_unique<BaseEntryTicket>();
	my_ticket = std::move(std::make_unique<PalaceTicket>(std::move(my_ticket)));

	cout << ">>>>Price for Base + Palace : "<< my_ticket->Price() << endl;
	cout << ">>>>>Description:  " << my_ticket->Description() << endl;

	my_ticket.reset();
	my_ticket = std::move(std::make_unique<BaseEntryTicket>());
	my_ticket = std::move(std::make_unique<ToyTrainTicket>(std::move(my_ticket)));

	cout << ">>>>Price for Base + ToyTrain : " << my_ticket->Price() << endl;
	cout << ">>>>>Description:  " << my_ticket->Description() << endl;

	my_ticket.reset();
	my_ticket = std::make_unique<BaseEntryTicket>();
	my_ticket = std::move(std::make_unique<ToyTrainTicket>(std::move(my_ticket)));
	my_ticket = std::move(std::make_unique<PalaceTicket>(std::move(my_ticket)));

	cout << ">>>>Price for Base + ToyTrain + Palace : " << my_ticket->Price() << endl;
	cout << ">>>>>Description:  " << my_ticket->Description() << endl;

	return 0;
}