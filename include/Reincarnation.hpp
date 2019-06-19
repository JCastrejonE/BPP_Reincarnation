#ifndef REINCARNATION_H
#define REINCARNATION_H

#include <vector>
#include <queue>
#include <random>
#include <unordered_set>
#include "Soul.hpp"

using namespace std;

#define GENERATIONS 1000
#define POPULATION 200
#define MAX_LIFETIME 20
#define NIRVANA_THRESHOLD 20
#define WORST_SOULS 3
#define SUSPENSION 2

// HUMAN TYPES
#define GURU 0
#define COMMONER 1
#define ATHEIST 2

class Reincarnation
{
private:
  int n;
  int bin_size; //BPP bin size

  int currentGen;
  vector<Soul *> T; // Soul population
  int gurus; // Guru population
  int commoners; // Commoner population
  int atheists; // Atheist population
  Soul *best_guru;
  int max_lifetime;
  queue<Soul *> u; // Suspension queue
  int living;
  int current_alive;
  vector<int> best_solution;
  int best_cost;

  default_random_engine dre;

  void prepareGeneration();
  void performKarma(int, int, int);
  void computeSoulCost(Soul *);

public:
  pair<vector<int>, int> computeSolution();
  void setRandomEngine(int);
  Reincarnation(vector<int> &, int);
};

bool karmaSort(Soul*, Soul*);

#endif