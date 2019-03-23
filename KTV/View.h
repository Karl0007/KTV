#pragma once
#include<cstdlib>
#include <vector>
#include"Song.h"
#include<iostream>
#include<conio.h>
using std::cout;
using std::vector;
namespace MyKTV{
class View
{
private:
	static View* Instance;
	View();
	~View();
	View(View const &) = delete;
	View(View&&) = delete;
	View & operator=(View const&) = delete;
	View & operator=(View&&) = delete;

public:
	static View & getInstance();
	void clearScreen();
	void showSongTable(const vector<Song*> tab,bool user);
	void showMessage(const string & str);
	void showTalbeByPage(const vector<Song*> tab, bool user, int &page);
	int getInt();
	int getKeyDownInt();
	char getKeyDown();
	string getString();
};
}

