#pragma once
#include <bits/stdc++.h>
#include "StringOperator.h"
using namespace My;
using std::unique_ptr;
namespace MyKTV
{

class Data;

class Song
{
  private:
	string m_name;
	string m_singer;
	string m_firstLetter;
	int m_id;
	float m_score;
	int m_popularity;

  public:
	bool operator==(Song const &oth) { return m_name == oth.m_name && m_singer == oth.m_singer; }

	string getName() { return m_name; }
	string getSiner() { return m_singer; }
	string getFirst() { return m_firstLetter; }
	int getID() { return m_id; }
	float getScore() { return m_score; }
	int getPopularity() { return m_popularity; }
	void addPopularity();
	bool addScore(int);

	Song(string const &_str);
	~Song();

	friend class Data;
};

} // namespace MyKTV
