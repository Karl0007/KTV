#pragma once
#include <bits/stdc++.h>
#include "Song.h"
#include "View.h"
using std::map;
using std::function;
using std::multimap;
using std::multiset;
using std::sort;
using std::unique_ptr;
using std::vector;
using std::cout;
using std::endl;
namespace MyKTV
{
class Data
{
  private:
	static Data *Instance;

	Data();
	~Data();
	Data(Data const &) = delete;
	Data(Data &&) = delete;
	Data &operator=(Data const &) = delete;
	Data &operator=(Data &&) = delete;

	vector<unique_ptr<Song>> m_songList;

  public:
	static Data &getInstance();
	void sortByID();
	void sortByScore();
	void sortByPopularity();
	void reID();
	bool importSong(string const &, bool);
	int importSongFromFile(string const &);
	bool deleteSong(int);

	map<string,string> m_password;

	vector<Song*> ShowByFun(function<bool(unique_ptr<Song> &)>);
};

} // namespace MyKTV
