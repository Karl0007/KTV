#include "StringOperator.h"

namespace My
{
extern vector<string> Split(const string &_str, const char &_ch)
{
	vector<string> res;
	string tmp;
	for (int i = 0; i < _str.size(); i++)
	{
		if (_str[i] == _ch)
		{
			if (tmp.size() != 0)
			{
				res.push_back(tmp);
				tmp.clear();
			}
		}
		else
		{
			tmp += _str[i];
		}
	}
	if (tmp.size())
		res.push_back(tmp);
	return res;
}

extern int StrToUInt(string const &_str)
{
	int res = 0;
	for (auto ch : _str)
	{
		if (ch >= '0' && ch <= '9')
			res = res * 10 + ch - '0';
	}
	return res;
}

extern string UIntToStr(int _x)
{
	string res;
	while (_x)
	{
		res += _x % 10 + '0';
		_x /= 10;
	}
	std::reverse(res.begin(), res.end());
	if (res.empty()) res = "0";
	return res;
}
} // namespace My
