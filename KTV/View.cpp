#include "View.h"


namespace MyKTV {
View* View::Instance = nullptr;
View::View()
{
}


View::~View()
{
}

View & View::getInstance()
{
	if (Instance == nullptr) {
		Instance = new View;
	}
	return *Instance;
}
void View::clearScreen()
{
	system("cls");
}

void View::showSongTable(const vector<Song*> tab,bool user)
{
	int len = 15;
	cout.width(len);
	cout << "编号";
	cout.width(len);
	cout << "歌曲名";
	cout.width(len);
	cout << "歌手";
	cout.width(len);
	cout << "人气";
	cout.width(len);
	cout << "评分\n";
	for (auto i : tab)
	{
		cout.width(len);
		cout << i->getID();
		cout.width(len);
		cout << i->getName();
		cout.width(len);
		cout << i->getSiner();
		cout.width(len);
		cout << i->getPopularity();
		cout.width(len);
		cout << i->getScore();
		if (user) {
			cout << "正在播放...";
			user = false;
		}
		cout << std::endl;
	}
}

void View::showMessage(const string & str)
{
	cout << str << std::endl;
}

void View::showTalbeByPage(const vector<Song*> tab, bool user, int &page)
{
	if (page < 0) {
		page = 0;
	}
	if (page > tab.size() / 9 - (tab.size() % 9 == 0)){
		page = tab.size() / 9 - (tab.size() % 9 == 0);
	}
	if (page != 0) {
		user = false;
	}
	int len = 15;
	cout.width(len);
	cout << "键盘：编号";
	cout.width(len);
	cout << "歌曲名";
	cout.width(len);
	cout << "歌手";
	cout.width(len);
	cout << "人气";
	cout.width(len);
	cout << "评分";
	cout << std::endl;
	len = 14;
	int cnt = 0;
	for (int k=page*9;k<tab.size()&& cnt<9;k++)
	{
		auto i = tab[k];
		cout.width(len);
		cout << ++cnt;
		cout <<"：" << i->getID();
		cout.width(len);
		cout << i->getName();
		cout.width(len);
		cout << i->getSiner();
		cout.width(len);
		cout << i->getPopularity();
		cout.width(len);
		cout << i->getScore();
		if (user) {
			cout.width(len);
			cout << "正在播放...";
			user = false;
		}
		cout << std::endl;
	}
	cout << "第" << page + 1 << "/" << tab.size() / 9 - (tab.size() % 9 == 0) + 1 << "页   ← → 翻页   0：退出\n";
}

int View::getInt()
{
	int tmp;
	std::cin >> tmp;
	return tmp;
}

int View::getKeyDownInt()
{
	return getKeyDown()-'0';
}


char View::getKeyDown()
{
	while (1) {
		if(_kbhit())
			return _getch();
	}
}

string View::getString()
{
	string tmp;
	std::getline(std::cin,tmp);
	return tmp;
}



}