#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class IButton
{
public:
	virtual void paint() = 0;
};

class WinButton : public IButton
{
public:
	void paint() override
	{
		cout << "Painting Windows Button" << endl;
	}
};

class MacButton : public IButton
{
public:
	void paint() override
	{
		cout << "Painting Mac Button" << endl;
	}
};


class ICheckBox
{
public:
	virtual void paint() = 0;
};

class WindowsCheckBox : public ICheckBox
{
public:
	void paint() override
	{
		cout << "Painting Windows Checkbox" << endl;
	}
};
class MacCheckBox : public ICheckBox
{
public:
	void paint() override
	{
		cout << "Painting Mac Checkbox" << endl;
	}
};

class IGuiFactory
{
public:
	virtual unique_ptr<IButton> CreateButton() = 0;
	virtual unique_ptr<ICheckBox> CreateCheckBox() = 0;
};

class WinFactory : public IGuiFactory
{
public:
	unique_ptr<IButton> CreateButton() override
	{
		return make_unique<WinButton>();
	}

	unique_ptr<ICheckBox> CreateCheckBox() override
	{
		return make_unique<WindowsCheckBox>();
	}
};
class MacFactory : public IGuiFactory
{
public:
	unique_ptr<IButton> CreateButton() override
	{
		return make_unique<MacButton>();
	}

	unique_ptr<ICheckBox> CreateCheckBox() override
	{
		return make_unique<MacCheckBox>();
	}
};

class ClientFactory
{
private:
	unique_ptr<IGuiFactory> gui_factory;
	unique_ptr<IButton> button;
	unique_ptr<ICheckBox> check_box;

public:
	ClientFactory(unique_ptr<IGuiFactory> factory)
	{
		gui_factory = std::move(factory);

		button = std::move(gui_factory->CreateButton());

		check_box = move(gui_factory->CreateCheckBox());
	}

	void PaintButton()
	{
		button->paint();
	}

	void PaintCheckBox()
	{
		check_box->paint();
	}
};

int main5()
{
	int os{};
	cin >> os;

	unique_ptr<IGuiFactory> factory;

	if (1 == os)
	{
		factory = make_unique<WinFactory>();
	}
	else if (2 == os)
	{
		factory = make_unique<MacFactory>();
	}

	unique_ptr<ClientFactory> client_factory = make_unique<ClientFactory>(std::move(factory));

	client_factory->PaintButton();
	client_factory->PaintCheckBox();

	int temp{};
	cin >> temp;

	return 0;
}

