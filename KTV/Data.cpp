#include "Data.h"

namespace MyKTV
{
	Data *Data::Instance = nullptr;

	Data::Data(/* args */)
	{
		m_password["admin"] = "admin";
	}

	Data::~Data()
	{
	}

	Data &Data::getInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new Data;
		}
		return *Instance;
	}

	void Data::sortByID()
	{
		sort(m_songList.begin(), m_songList.end(),
			[](unique_ptr<Song> &l, unique_ptr<Song> &r)
			-> bool { return l->getID() < r->getID(); });
	}

	void Data::sortByScore()
	{
		sort(m_songList.begin(), m_songList.end(),
			[](unique_ptr<Song> &l, unique_ptr<Song> &r)
			-> bool { return l->getScore() > r->getScore(); });
	}

	void Data::sortByPopularity()
	{
		sort(m_songList.begin(), m_songList.end(),
			[](unique_ptr<Song> &l, unique_ptr<Song> &r)
			-> bool { return l->getPopularity() > r->getPopularity(); });
	}

	bool Data::importSong(string const &_str, bool _sorted = false)
	{
		View &view = View::getInstance();
		if (!_sorted)
			sortByID();
		unique_ptr<Song> tmp(new Song(_str));
		if (tmp->m_id == -1)
		{
			view.showMessage("非法输入：" + _str);
			return false;
		}
		for (auto &var : m_songList)
		{
			if (*var == *tmp)
			{
				view.showMessage("歌曲已存在" + _str);
				return false;
			}
		}
		if (m_songList.size()!=0) {
			tmp->m_id = m_songList.back()->m_id + 1;
		}
		else {
			tmp->m_id = 1;
		}
		m_songList.push_back(std::move(tmp));
		view.showMessage("成功导入：" + _str);
		return true;
	}

	int Data::importSongFromFile(string const &_file)
	{
		View &view = View::getInstance();
		int cnt = 0;
		std::ifstream is(_file);
		if (!is.is_open())
		{
			view.showMessage("文件不存在：" + _file);
			return cnt;
		}
		string tmp;
		while (!is.eof())
		{
			std::getline(is,tmp);
			cnt += importSong(tmp, true);
		}
		view.showMessage("成功导入" + My::UIntToStr(cnt)+"首歌曲");
		return cnt;
	}

	void Data::reID()
	{
		int cnt = 0;
		for (auto &song : m_songList)
		{
			song->m_id = ++cnt;
		}
	}

	bool Data::deleteSong(int _pos)
	{
		sortByID();
		if (_pos >= m_songList.size() || _pos <= 0)
		{
			return false;
		}
		m_songList.erase(m_songList.begin() + (_pos - 1));
		reID();
		return true;
	}


	vector<Song*> Data::ShowByFun(function<bool(unique_ptr<Song> &)> fun)
	{
		vector<Song *> tmp;
		for (auto &i : m_songList)
		{
			if (fun(i))
				tmp.push_back(i.get());
		}
		return tmp;
	}

} // namespace MyKTV
