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
	view.showMessage("1 �� ����Ա��¼");
	view.showMessage("2 �� �û���¼");
	view.showMessage("0 �� �˳�ϵͳ");
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
	View::getInstance().showMessage("��ӭʹ��KTV��� v0.91");
	View::getInstance().showMessage("���ߣ�181860007 ��ʢ�� karl07");
	View::getInstance().showMessage("https://github.com/Karl0007/");
	View::getInstance().getKeyDown();
}

void Controller::Last()
{
	View::getInstance().clearScreen();
	View::getInstance().showMessage("��лʹ��KTV��� v0.91");
	View::getInstance().showMessage("���ߣ�181860007 ��ʢ�� karl07");
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
		view.showMessage("�������û�����");
		string name = view.getString();
		view.showMessage("����������");
		string key = view.getString();
		if (data.m_password.count(name) && data.m_password[name] == key) {
			view.showMessage("��½�ɹ�");
			view.getKeyDown();
			curUser = name;
			Manager();
			return;
		}
		else {
			cnt--;
			view.showMessage("��¼ʧ��");
			if (cnt) view.showMessage("����" + My::UIntToStr(cnt) + "�λ���");
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
	view.showMessage("1 �� ���ֵ��");
	view.showMessage("2 �� ��������");
	view.showMessage("3 �� ƴ�����");
	view.showMessage("4 �� ���и���");
	view.showMessage("5 �� �ѵ����");
	view.showMessage("6 �� ��    ��");
	view.showMessage("7 �� ɾ������");
	view.showMessage("8 �� �ö�����");
	view.showMessage("0 �� ��    ��");
	vector<Song*> table;
	Song* tmp = nullptr;
REREAD:
	switch (view.getKeyDownInt())
	{
	case 1:
		view.showMessage("�������������");
		str = view.getString();
		table = Data::getInstance().ShowByFun(singer);
		goto SELECT;
	case 2:
		view.showMessage("�������������");
		str = view.getString();
		table = Data::getInstance().ShowByFun(name);
		goto SELECT;
	case 3:
		view.showMessage("������ƴ����");
		str = view.getString();
		table = Data::getInstance().ShowByFun(letter);
		goto SELECT;
	case 4:
		table = Data::getInstance().ShowByFun(all);
		goto SELECT;
	case 5:
		table = SongQueue::getInstance().getList();
		if (table.empty()) {
			view.showMessage("�����б�Ϊ��");
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
			view.showMessage("�����б�Ϊ��");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table, true);
			if (tmp) {
				view.showMessage("ɾ���ɹ� ��" + tmp->getName() + "(" + tmp->getSiner() + ")");
				SongQueue::getInstance().deletSong(tmp);
			}	
			else {
				view.showMessage("ȡ��ɾ��");
			}
			view.getKeyDown();
			User();
			return;
		}

	case 8:
		table = SongQueue::getInstance().getList();
		if (table.empty()) {
			view.showMessage("�����б�Ϊ��");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table, true);
			if (tmp) {
				view.showMessage("�ö��ɹ� ��" + tmp->getName() + "(" + tmp->getSiner() + ")");
				SongQueue::getInstance().deletSong(tmp);
				SongQueue::getInstance().addSongFirst(tmp);
			}
			else {
				view.showMessage("ȡ���ö�");
			}
			view.getKeyDown();
			User();
			return;
		}
	SELECT:
		if (table.empty()) {
			view.showMessage("δ�ҵ�������");
			view.getKeyDown();
			User();
			return;
		}
		else {
			auto tmp = Select(table,true);
			if (tmp) {
				if (SongQueue::getInstance().addSong(tmp)) {
					view.showMessage("�ɹ���� " + tmp->getName() + " " + tmp->getSiner());
				}
				else {
					view.showMessage("�Ѵ��� " + tmp->getName() + " " + tmp->getSiner());
				}
			}
			else {
				view.showMessage("�����ȡ��");
			}
			view.getKeyDown();
			User();
			return;
		}

	case 6:
		tmp = SongQueue::getInstance().nextSong();
		if (tmp) {
			if (SongQueue::getInstance().getCurSong()) {
				view.showMessage("�и�ɹ� ��ǰ������" + SongQueue::getInstance().getCurSong()->getName());
			}
			else {
				view.showMessage("�и�ɹ� ��ǰ�б�Ϊ��");
			}
			view.showMessage("��Ϊ" + tmp->getName() + "(" + tmp->getSiner() + ")" + "����(1~5)");
			int x = view.getKeyDownInt();
			while (x < 1 || x>5)x=view.getKeyDownInt();
			view.showMessage(My::UIntToStr(x)+"�� ���ֳɹ���");
			tmp->addScore(x);
			view.getKeyDown();
			User();
			return;
		}
		else
		{
			view.showMessage("�б�Ϊ�գ�");
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
	view.showMessage("1 �� ���и���");
	view.showMessage("2 �� ��Ӹ���");
	view.showMessage("3 �� �������");
	view.showMessage("4 �� ɾ������");
	view.showMessage("5 �� ��������");
	view.showMessage("6 �� ��������");
	view.showMessage("7 �� �޸�����");
	view.showMessage("0 �� ��    ��");
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
			view.showMessage("�б�Ϊ�գ�");
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
			view.showMessage("�б�Ϊ�գ�");
			view.getKeyDown();
			Manager();
			return;
		}
		else {
			tmp = Select(table, true);
			if (tmp) {
				SongQueue::getInstance().deletSong(tmp);
				view.showMessage(tmp->getName() + "(" + tmp->getSiner() + ")" + "ɾ���ɹ�");
				data.deleteSong(tmp->getID());
				view.getKeyDown();
			}
			else {
				view.showMessage("ɾ����ȡ��");
				view.getKeyDown();
			}
			Manager();
			return;
		}

	case 3:
		view.showMessage("�������ļ�����");
		tmpstr = view.getString();
		data.importSongFromFile(tmpstr);
		view.getKeyDown();
		Manager();
		return;
	case 2:
		view.showMessage("������\t������\t��д");
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
	view.showMessage("�����뵱ǰ����:");
	key1 = view.getString();
	if (key1 != data.m_password[curUser]) {
		view.showMessage("�������");
		return;
	}
	view.showMessage("������������:");
	key2 = view.getString();
	view.showMessage("��ȷ�������룺");
	key3 = view.getString();
	if (key2 != key3) {
		view.showMessage("�������벻ͬ �޸�ʧ��");
		return;
	}
	else {
		view.showMessage("�޸ĳɹ�");
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