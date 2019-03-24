#include "Controller.h"

namespace MyKTV{

Controller* Controller::Instance = nullptr;

Controller::Controller()
{
}


Controller::~Controller()
{
}
Controller & Controller::getInstance()
{
	if (Instance == nullptr) {
		Instance = new Controller;
	}
	return *Instance;
}
void Controller::Login()
{
	View & view = View::getInstance();
	view.clearScreen();
	view.showMessage("1 ： 管理员登录");
	view.showMessage("2 ： 用户登录");
	view.showMessage("0 ： 退出系统");
REREAD:
	switch (view.getKeyDownInt())
	{
		case 1:
			ManagerLogin();
			Login();
			return;
		case 2:
			User();
			Login();
			return;
		case 0:
			return;
		default:
		goto REREAD;
	}
}
void Controller::First()
{
	View::getInstance().clearScreen();
	View::getInstance().showMessage("欢迎使用KTV点歌 v0.91");
	View::getInstance().showMessage("作者：181860007 陈盛恺 karl07");
	View::getInstance().showMessage("https://github.com/Karl0007/");
	View::getInstance().getKeyDown();
}

void Controller::Last()
{
	View::getInstance().clearScreen();
	View::getInstance().showMessage("感谢使用KTV点歌 v0.91");
	View::getInstance().showMessage("作者：181860007 陈盛恺 karl07");
	View::getInstance().showMessage("https://github.com/Karl0007/");
	View::getInstance().getKeyDown();

}
void Controller::ManagerLogin()
{
	View & view = View::getInstance();
	Data & data = Data::getInstance();
	int cnt = 3;
	while (cnt)
	{
		view.clearScreen();
		view.showMessage("请输入用户名：");
		string name = view.getString();
		view.showMessage("请输入密码");
		string key = view.getString();
		if (data.m_password.count(name) && data.m_password[name] == key) {
			view.showMessage("登陆成功");
			view.getKeyDown();
			curUser = name;
			Manager();
			return;
		}
		else {
			cnt--;
			view.showMessage("登录失败");
			if (cnt) view.showMessage("还有" + My::UIntToStr(cnt) + "次机会");
			view.getKeyDown();
		}
	}


}
void Controller::User()
{
	string str;
	auto letter = [&str](unique_ptr<Song>&ptr)->bool {
		for (int i = 0; i < str.length(); i++)
		{
			if (i >= ptr->getFirst().length() || str[i] != ptr->getFirst()[i]) return false;
		}
		return true;
	};
	auto name = [&str](unique_ptr<Song>&ptr)->bool {
		return ptr->getName() == str;
	};	
	auto singer = [&str](unique_ptr<Song>&ptr)->bool {
		return ptr->getSiner() == str;
	};
	auto all = [&str](unique_ptr<Song>&ptr)->bool {
		return true;
	};
	View & view = View::getInstance();
	view.clearScreen();
	view.showMessage("1 ： 歌手点歌");
	view.showMessage("2 ： 歌曲搜索");
	view.showMessage("3 ： 拼音点歌");
	view.showMessage("4 ： 所有歌曲");
	view.showMessage("5 ： 已点歌曲");
	view.showMessage("6 ： 切    歌");
	view.showMessage("7 ： 删除歌曲");
	view.showMessage("8 ： 置顶歌曲");
	view.showMessage("0 ： 退    出");
	vector<Song*> table;
	Song* tmp = nullptr;
REREAD:
	switch (view.getKeyDownInt())
	{
	case 1:
		view.showMessage("请输入歌手名：");
		str = view.getString();
		table = Data::getInstance().ShowByFun(singer);
		goto SELECT;
	case 2:
		view.showMessage("请输入歌曲名：");
		str = view.getString();
		table = Data::getInstance().ShowByFun(name);
		goto SELECT;
	case 3:
		view.showMessage("请输入拼音：");
		str = view.getString();
		table = Data::getInstance().ShowByFun(letter);
		goto SELECT;
	case 4:
		table = Data::getInstance().ShowByFun(all);
		goto SELECT;
	case 5:
		table = SongQueue::getInstance().getList();
		if (table.empty()) {
			view.showMessage("播放列表为空");
			view.getKeyDown();
			User();
			return;
		}
		else {
			Select(table, false);
			User();
			return;
		}

	case 7:
		table = SongQueue::getInstance().getList();
		if (table.empty()) {
			view.showMessage("播放列表为空");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table, true);
			if (tmp) {
				view.showMessage("删除成功 ：" + tmp->getName() + "(" + tmp->getSiner() + ")");
				SongQueue::getInstance().deletSong(tmp);
			}	
			else {
				view.showMessage("取消删除");
			}
			view.getKeyDown();
			User();
			return;
		}

	case 8:
		table = SongQueue::getInstance().getList();
		if (table.empty()) {
			view.showMessage("播放列表为空");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table, true);
			if (tmp) {
				view.showMessage("置顶成功 ：" + tmp->getName() + "(" + tmp->getSiner() + ")");
				SongQueue::getInstance().deletSong(tmp);
				SongQueue::getInstance().addSongFirst(tmp);
			}
			else {
				view.showMessage("取消置顶");
			}
			view.getKeyDown();
			User();
			return;
		}
	SELECT:
		if (table.empty()) {
			view.showMessage("未找到歌曲！");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table,true);
			if (tmp) {
				if (SongQueue::getInstance().addSong(tmp)) {
					view.showMessage("成功添加 " + tmp->getName() + " " + tmp->getSiner());
				}
				else {
					view.showMessage("已存在 " + tmp->getName() + " " + tmp->getSiner());
				}
			}
			else {
				view.showMessage("添加已取消");
			}
			view.getKeyDown();
			User();
			return;
		}

	case 6:
		tmp = SongQueue::getInstance().nextSong();
		if (tmp) {
			if (SongQueue::getInstance().getCurSong()) {
				view.showMessage("切歌成功 当前歌曲：" + SongQueue::getInstance().getCurSong()->getName());
			}
			else {
				view.showMessage("切歌成功 当前列表为空");
			}
			view.showMessage("请为" + tmp->getName() + "(" + tmp->getSiner() + ")" + "评分(1~5)");
			int x = view.getKeyDownInt();
			while (x < 1 || x>5)x=view.getKeyDownInt();
			view.showMessage(My::UIntToStr(x)+"分 评分成功！");
			tmp->addScore(x);
			view.getKeyDown();
			User();
			return;
		}
		else
		{
			view.showMessage("列表为空！");
			view.getKeyDown();
			User();
			return;
		}
	case 0:
		return;
	default:
		goto REREAD;
	}
}

void Controller::Manager()
{
	auto all = [](unique_ptr<Song>&ptr)->bool {
		return true;
	};
	View & view = View::getInstance();
	Data & data = Data::getInstance();
	view.clearScreen();
	view.showMessage("1 ： 所有歌曲");
	view.showMessage("2 ： 添加歌曲");
	view.showMessage("3 ： 批量添加");
	view.showMessage("4 ： 删除歌曲");
	view.showMessage("5 ： 人气排序");
	view.showMessage("6 ： 评分排序");
	view.showMessage("7 ： 修改密码");
	view.showMessage("0 ： 退    出");
	vector<Song*> table;
	Song* tmp = nullptr;
	string tmpstr = "";
REREAD:
	switch (view.getKeyDownInt())
	{
	case 1:
		data.sortByID();
		table = Data::getInstance().ShowByFun(all);
		goto SELECT;
	case 5:
		data.sortByPopularity();
		table = Data::getInstance().ShowByFun(all);
		data.sortByID();
		goto SELECT;
	case 6:
		data.sortByScore();
		table = Data::getInstance().ShowByFun(all);
		data.sortByID();
		goto SELECT;

	SELECT:
		if (table.empty()) {
			view.showMessage("列表为空！");
			view.getKeyDown();
			Manager();
			return;
		}
		else {
			Select(table, true);
			Manager();
			return;
		}

	case 4:
		table = Data::getInstance().ShowByFun(all);
		if (table.empty()) {
			view.showMessage("列表为空！");
			view.getKeyDown();
			Manager();
			return;
		}
		else {
			tmp = Select(table, true);
			if (tmp) {
				SongQueue::getInstance().deletSong(tmp);
				view.showMessage(tmp->getName() + "(" + tmp->getSiner() + ")" + "删除成功");
				data.deleteSong(tmp->getID());
				view.getKeyDown();
			}
			else {
				view.showMessage("删除已取消");
				view.getKeyDown();
			}
			Manager();
			return;
		}

	case 3:
		view.showMessage("请输入文件名：");
		tmpstr = view.getString();
		data.importSongFromFile(tmpstr);
		view.getKeyDown();
		Manager();
		return;
	case 2:
		view.showMessage("歌曲名\t歌手名\t缩写");
		tmpstr = view.getString();
		data.importSong(tmpstr,true);
		view.getKeyDown();
		Manager();
		return;
	case 7:
		ModifyKey();
		view.getKeyDown();
		Manager();
		return;
	case 0:
		return;
	default:
		goto REREAD;
	}
}

void Controller::ModifyKey()
{
	View & view = View::getInstance();
	Data & data = Data::getInstance();
	string key1, key2, key3;
	view.showMessage("请输入当前密码:");
	key1 = view.getString();
	if (key1 != data.m_password[curUser]) {
		view.showMessage("密码错误");
		return;
	}
	view.showMessage("请输入新密码:");
	key2 = view.getString();
	view.showMessage("请确认新密码：");
	key3 = view.getString();
	if (key2 != key3) {
		view.showMessage("两次输入不同 修改失败");
		return;
	}
	else {
		view.showMessage("修改成功");
		data.m_password[curUser] = key2;
		return;
	}
}

Song* Controller::Select(const vector<Song*> table,bool sel)
{
	int page = 0;
	View & view = View::getInstance();
	while (1) {
		view.clearScreen();
		view.showTalbeByPage(table,!sel,page);
		int num = view.getKeyDown();
		switch (num) {
		case '0':
			return nullptr;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			num -= '1';
			if (sel && page * 9 + num < table.size()) {
				return table[page * 9 + num];
			}
			else {
				break;
			}
		case 75:
			page--;
			break;
		case 77:
			page++;
			break;
		default:
			break;
		}
	}
	return nullptr;
}
}