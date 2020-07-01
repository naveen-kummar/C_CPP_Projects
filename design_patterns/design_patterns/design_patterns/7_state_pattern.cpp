#include <memory>
#include <iostream>
#include <vector>

using namespace std;

//This code will not compile untill each class is moved seprate .h files
//Because forward declartion will not expose hierarchy relationship

class AudioPlayer;
class AbstractState
{
protected:
	shared_ptr<AudioPlayer> player;

public:
	AbstractState(shared_ptr<AudioPlayer> p) : player(p)
	{

	}

	virtual void Lock() = 0;
	virtual void Play() = 0;
	virtual void Next() = 0;
	virtual void Previous() = 0;

};

class AudioPlayer
{
private:
	bool playing;
	shared_ptr<AbstractState> state;
public:
	AudioPlayer() 
	{
		state = make_shared<ReadyState>(*this);
	}
	bool IsPlaying() { return playing; }

	void ChangeState(shared_ptr<AbstractState> s)
	{
		state = s;
	}

	void StartPlayBack()
	{
		cout << "Playing Music" << endl;
	}

	void StopPlayBack()
	{
		cout << "Playback Stopped" << endl;
	}

	void NextSong()
	{
		cout << "Next Song" << endl;
	}

	void PreviousSong()
	{
		cout << "Previous Song" << endl;
	}
};



class ReadyState;

class PlayingState : public AbstractState
{
public:
	PlayingState(shared_ptr<AudioPlayer> p) : AbstractState(p)
	{

	}

	void Lock() override
	{
		player->ChangeState(make_unique<LockedState>(player));
	}

	void Play() override
	{
		player->StartPlayBack();
		player->ChangeState(make_unique<ReadyState>(player));
	}

	void Next() override
	{
		player->NextSong();
	}

	void Previous() override
	{
		player->PreviousSong();
	}
};

class LockedState : public AbstractState
{
public:
	LockedState(shared_ptr<AudioPlayer> p) : AbstractState(p)
	{

	}

	void Lock() override
	{
		if (player->IsPlaying())
		{
			shared_ptr<AbstractState> temp = make_shared<PlayingState>(player);
			player->ChangeState(temp);
		}
		else
		{
			player->ChangeState(make_unique<ReadyState>(std::move(player)));
		}
	}

	void Play() override
	{

	}

	void Next() override
	{

	}

	void Previous() override
	{

	}
};

class ReadyState : public AbstractState
{
public:
	ReadyState(shared_ptr<AudioPlayer> p) : AbstractState(p)
	{

	}

	void Lock() override
	{
		player->ChangeState(make_shared<LockedState>(std::move(player)));
	}

	void Play() override
	{
		player->StartPlayBack();
		player->ChangeState(make_unique<PlayingState>(std::move(player)));
	}

	void Next() override
	{

	}

	void Previous() override
	{

	}
};

int main()
{
	return 0;
}
