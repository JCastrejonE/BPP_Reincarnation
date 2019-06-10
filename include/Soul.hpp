#ifndef SOUL_H
#define SOUL_H

#include <vector>

using namespace std;

class Soul
{
private:
public:
  int id;
  int lifetime;
  int community_guru;
  int cost;
  int bestCount;
  vector<int> karma;

  Soul(int id, vector<int> &karma)
  {
    this->id = id;
    this->karma = karma;
    this->bestCount = 0;
  };
};

#endif