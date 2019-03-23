#include "Song.h"

namespace MyKTV
{
	void Song::addPopularity()
	{
		m_popularity++;
	}

	bool Song::addScore(int score)
	{
		if (score > 5 || score < 1) {
			std::cout << "请在1-5之间评分" << std::endl;
			return false;
		}
		m_score = m_score * m_popularity + score;
		addPopularity();
		m_score /= m_popularity;
		return true;
	}

	Song::Song(string const &_str)
{
	auto strs = Split(_str, ' ');
	if (strs.size() == 4)
	{
		m_id = StrToUInt(strs[0]);
		m_name = strs[1];
		m_singer = strs[2];
		m_firstLetter = strs[3];
		m_popularity = 0;
		m_score = 0;
		return;
	}
	if (strs.size() == 3)
	{
		m_name = strs[0];
		m_singer = strs[1];
		m_firstLetter = strs[2];
		m_popularity = 0;
		m_score = 0;
		m_id = 0;
		return;
	}
	m_id = -1;
	//ERROR 非法字符串导入失败
}

Song::~Song()
{
}

} // namespace MyKTV
