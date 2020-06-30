#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class IButton
{
public:
	virtual void OnClick() = 0;
	virtual void Render(int x1, int y1, int x2, int y2) = 0;
};

class WindowsButton : public IButton
{
public:
	void OnClick() override
	{
		cout << "Win Button Click" << endl;
	}

	void Render(int x1, int y1, int x2, int y2)
	{
		cout << "Rendering Windows Button" << endl;
	}
};

class WebButton : public IButton
{
public:
	void OnClick() override
	{
		cout << "Wed Button Click" << endl;
	}

	void Render(int x1, int y1, int x2, int y2)
	{
		cout << "Rendering Web Button" << endl;
	}
};

class Dialog_Abstract
{
private:
	virtual unique_ptr<IButton> CreateButton() = 0;

public:
	void Render()
	{
		unique_ptr<IButton> button = CreateButton();
		button->OnClick();
		button->Render(1,1,10,10);
	}
};

class WindowsDialog : public Dialog_Abstract
{
	unique_ptr<IButton> CreateButton() override
	{
		return make_unique<WindowsButton>();
	}
};

class WebDialog : public Dialog_Abstract
{
	unique_ptr<IButton> CreateButton() override
	{
		return make_unique<WebButton>();
	}
};

int main4()
{
	int os;
	cin >> os;

	unique_ptr<Dialog_Abstract> dialog;
	if (os == 1)
	{
		dialog = make_unique<WindowsDialog>();
	}
	else if (os == 2)
	{
		dialog = make_unique<WebDialog>();
	}

	dialog->Render();

	getchar();

	return 0;
}