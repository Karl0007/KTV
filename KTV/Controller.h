#pragma once
#include<bits/stdc++.h>
#include"Data.h"
#include"View.h"
#include"SongQueue.h"
namespace MyKTV{
class Controller
{
private:
	Controller();
	~Controller();
	Controller(Controller const &) = delete;
	Controller(Controller&&) = delete;
	Controller& operator=(Controller&&) = delete;
	Controller& operator=(Controller const&) = delete;
	
	static Controller* Instance;
	string curUser;

	void ManagerLogin();
	void User();
	void Manager();
	void ModifyKey();

public:
	static Controller& getInstance();
	void Login();
	void First();
	void Last();

	Song* Select(const vector<Song*>,bool);

};
}

