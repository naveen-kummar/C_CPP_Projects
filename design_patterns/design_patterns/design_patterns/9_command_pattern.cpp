#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <stack>
#include <functional>

//Getting few compile error as classes need to move respective harders


using namespace std;

class MainApplication;




class Editor
{
public:
	string text;

	string GetSelection()
	{
		cout << "Selecting string" << endl;
		return text;
	}

	void DeleteSelection()
	{
		cout << "Delet selected string" << endl;
		text = "";
	}

	void ReplaceSelectedString(string new_string)
	{
		cout << "Replace Existing String " << text << " with new string " << new_string << endl;
		text = new_string;
	}
};

class AbstractCommand;

class IMainApp
{
public:
	string clip_board;
	unique_ptr<Editor> editor = make_unique<Editor>();


	virtual void ExecuteCommand(unique_ptr<AbstractCommand>  command) = 0;

	virtual void Undo() = 0;

};
class AbstractCommand
{
protected:
	unique_ptr<IMainApp> application;
	unique_ptr<Editor> editor;
	string backup;

public:
	AbstractCommand(unique_ptr<IMainApp> app, unique_ptr<Editor> e) :
		application{ std::move(app) }, editor{std::move(e)}
	{

	}

	void SaveBackup()
	{
		backup = editor->text;
	}

	void Undo()
	{
		editor->text = backup;
	}

	virtual bool execute() = 0;
};



class CopyCommmand : public AbstractCommand
{
public:
	CopyCommmand(unique_ptr<IMainApp> app, unique_ptr<Editor> e) : AbstractCommand(std::move(app), std::move(e))
		
	{

	}

	// The copy command isn't saved to the history since it
// doesn't change the editor's state.
	bool execute() override
	{
		application->clip_board = editor->GetSelection();
		return false;
	}
};

class CutCommmand : public AbstractCommand
{
public:
	CutCommmand(unique_ptr<IMainApp> app, unique_ptr<Editor> e) : AbstractCommand(std::move(app), std::move(e))

	{

	}

	bool execute() override
	{
		SaveBackup();
		application->clip_board = editor->GetSelection();
		editor->DeleteSelection();
		return true;
	}
};

class PasteCommand : public AbstractCommand
{
public:
	PasteCommand(unique_ptr<IMainApp> app, unique_ptr<Editor> e) : AbstractCommand(std::move(app), std::move(e))

	{

	}

	bool execute() override
	{
		SaveBackup();
		editor->ReplaceSelectedString(application->clip_board);

		return true;
	}
};

class UndoCommand : public AbstractCommand
{

public:
	UndoCommand(unique_ptr<IMainApp> app, unique_ptr<Editor> e) : AbstractCommand(std::move(app), std::move(e))

	{

	}

	bool execute() override
	{
		application->Undo();

		return false;
	}
};



class MainApplication : public IMainApp
{
public:
	std::stack<unique_ptr<AbstractCommand>> command_history;

	void ExecuteCommand(unique_ptr<AbstractCommand>  command) override
	{
		if (command->execute())
		{
			command_history.push(std::move(command));
		}
	}

	void Undo() override
	{
		if (command_history.size() > 0)
		{
			unique_ptr<AbstractCommand> Cmd = std::move(command_history.top());
			command_history.pop();
		}
	}

	//std::function<unique_ptr<AbstractCommand>()> fn_copy =
	//	[this]() {return make_unique<CopyCommmand>(std::move(this), std::move(editor)); };

	//std::function<unique_ptr<AbstractCommand>()> fn_cut =
	//	[this]() {return make_unique<CutCommmand>(std::move(this), std::move(editor)); };

	//std::function<unique_ptr<AbstractCommand>()> fn_paste =
	//	[this]() {return make_unique<PasteCommand>(std::move(this), std::move(editor)); };

	//std::function<unique_ptr<AbstractCommand>()> fn_undo =
	//	[this]() {return make_unique<UndoCommand>(std::move(this), std::move(editor)); };

	//void DoCopy()
	//{
	//	fn_copy();
	//}

	//void DoCut()
	//{
	//	fn_cut();
	//}

	//void DoPaste()
	//{
	//	fn_paste();
	//}

	//void DoUndo()
	//{
	//	fn_undo();
	//}
};

int main()
{
	return 0;
}