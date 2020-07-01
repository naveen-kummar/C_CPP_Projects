#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class IEventListener
{
public: 
	virtual void UpdateFileName(string filename) = 0;
};

class LoggingListener : public IEventListener
{
private:
	void SpecificOperation_DoLogging(string filename)
	{
		cout << "Adding in to logging Database for file  " << filename << endl;
	}

public:
	void UpdateFileName(string filename) override
	{
		cout << "Received event for looging for file " << filename << endl;
		SpecificOperation_DoLogging(filename);
	}
};

class EmailListener : public IEventListener
{
private:
	void SpecificOperation_SendEmail(string filename)
	{
		cout << "Sending Email for file  " << filename << endl;
	}

public:
	void UpdateFileName(string filename) override
	{
		cout << "Received event for Emailing for file " << filename << endl;
		SpecificOperation_SendEmail(filename);
	}
};

class EventPublisher
{
private:
	std::map<int, unordered_set<shared_ptr<IEventListener>>> event_listeners;

public:
	void Subscribe(int event_id, shared_ptr<IEventListener> listerner)
	{
		event_listeners[event_id].emplace(listerner);
	}

	void UnSubscribe(int event_id, shared_ptr<IEventListener> listerner)
	{
			(event_listeners[event_id]).erase(listerner);		
	}

	void Notify(int event_id, string data)
	{
		for (auto l : (event_listeners[event_id]))
		{
			l->UpdateFileName(data);
		}
	}
};

class Editor
{
	

public:
	std::unique_ptr<EventPublisher> event_manger;

	Editor()
	{
		event_manger = make_unique<EventPublisher>();

	}

	void LogFile(string filename)
	{
		event_manger->Notify(1, filename);
	}

	void EmailFile(string filename)
	{
		event_manger->Notify(2, filename);
	}
};

int main()
{

	unique_ptr<Editor> editor = make_unique<Editor>();
	shared_ptr<IEventListener> email_listener = make_shared<EmailListener>();

	editor->event_manger->Subscribe(2, email_listener);


	editor->EmailFile("MyFile");

	editor->LogFile("MyFile");//Hav not subscribed

	return 0;

}