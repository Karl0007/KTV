#include "SongQueue.h"


namespace MyKTV{

SongQueue* SongQueue::Instance = nullptr;
SongQueue & SongQueue::getInstance()
{
	if (Instance == nullptr) {
		Instance = new SongQueue;
	}
	return *Instance;
}
SongQueue::SongQueue()
{
}


SongQueue::~SongQueue()
{
}

bool SongQueue::addSong(Song * ptr)
{
	for (auto i = m_userSongs.begin(); i != m_userSongs.end();++i) {
		if (**i == *ptr)
			return false;
	}
	m_userSongs.push_back(ptr);
	return true;
}

Song* SongQueue::nextSong()
{
	if (m_userSongs.size() == 0)
		return nullptr;
	auto tmp = m_userSongs.front();
	m_userSongs.pop_front();
	return tmp;
}

bool SongQueue::setScore(int score)
{
	return getCurSong()->addScore(score);
}

bool SongQueue::deletSong(Song * ptr)
{
	for (auto i = m_userSongs.begin(); i != m_userSongs.end(); ++i) {
		if (**i == *ptr) {
			m_userSongs.erase(i);
			return true;
		}
	}
	return false;
}

Song * SongQueue::getCurSong()
{
	if (m_userSongs.empty()) return nullptr;
	return m_userSongs.front();
}

vector<Song*> SongQueue::getList()
{
	vector<Song*> tmp;
	for (auto i : m_userSongs)
	{
		tmp.push_back(i);
	}
	return tmp;
}

}