#pragma once
#include <bits/stdc++.h>
#include "Song.h"
using std::string;
using std::vector;
using std::list;
namespace MyKTV {

class SongQueue
{
private:
	SongQueue();
	~SongQueue();
	SongQueue(SongQueue const &) = delete;
	SongQueue(SongQueue &&) = delete;
	SongQueue &operator=(SongQueue const &) = delete;
	SongQueue &operator=(SongQueue &&) = delete;

	static SongQueue* Instance;

public:
	static SongQueue & getInstance();

	bool addSong(Song*);
	Song* nextSong();
	bool setScore(int);
	bool deletSong(Song*);
	Song* getCurSong();
	vector<Song*> getList();
private:
	list<Song*> m_userSongs;
};

}
