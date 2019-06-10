#include <algorithm>
#include "Reincarnation.hpp"

Reincarnation::Reincarnation(vector<int> &items, int bin_size)
{
  this->n = items.size();
  this->bin_size = bin_size;
  this->max_lifetime = MAX_LIFETIME;
  for (int i = 0; i < POPULATION; i++)
  {
    vector<int> karma = items;
    shuffle(karma.begin(), karma.end(), this->dre);
    Soul *s = new Soul(i, karma);
    computeSoulCost(s);
    this->T.push_back(s);
  }
}

pair<vector<int>, int> Reincarnation::computeSolution()
{
  while (this->T.size() > 0 && currentGen < GENERATIONS)
  {
    prepareGeneration();
    currentGen++;
    while (this->current_alive > 0)
    {
      performKarma(0, this->gurus, GURU);
      performKarma(this->gurus, this->commoners + this->gurus, COMMONER);
      performKarma(this->commoners + this->gurus, this->current_alive, ATHEIST);
    }
  }
  return {this->best_solution, this->best_cost};
}

void Reincarnation::prepareGeneration()
{
  sort(this->T.rbegin(), this->T.rend(), karmaSort);

  // Attain Nirvana verification
  this->best_guru = this->T[0];
  if(this->best_guru->cost < this->best_cost) {
    this->best_cost = this->best_guru->cost;
    this->best_solution = this->best_guru->karma;
  }
  int i = 0;
  for (Soul *s : this->T)
  {
    if (s->cost == this->best_guru->cost)
    {
      s->bestCount++;
      if (s->bestCount == NIRVANA_THRESHOLD)
      {
        this->T.erase(this->T.begin() + i);
        i--;
      }
    }
    else
    {
      s->bestCount = 0;
    }
    i++;
  }

  int living = this->T.size();

  uniform_int_distribution<int> years(1, this->max_lifetime);
  for (int i = 0; i < (int)this->T.size(); i++)
  {
    this->T[i]->lifetime = years(this->dre);
  }

  // Gurus define
  uniform_int_distribution<int> uid(1, living >= 3 ? living / 3 : living);
  this->gurus = uid(this->dre);
  uniform_int_distribution<int> communities(0, this->gurus);

  // Non human enqueue
  for (int i = 0; i < WORST_SOULS; i++)
  {
    if (living > 0)
    {
      this->u.push(this->T[this->T.size() - 1]);
      this->T.pop_back();
      living--;
    }
  }

  // Non human dequeue
  while (this->u.size() > WORST_SOULS * SUSPENSION)
  {
    this->u.front()->lifetime = years(this->dre);
    this->T.push_back(this->u.front());
    this->u.pop();
    living++;
  }

  // Commoners define
  uniform_int_distribution<int> uid2(0, living - gurus);
  this->commoners = uid2(this->dre);
  for (int i = this->gurus; i < this->gurus + this->commoners; i++)
  {
    this->T[i]->community_guru = communities(dre);
  }

  // Atheists define
  this->atheists = living - gurus - commoners;
  for (int i = this->gurus + this->commoners; i < living; i++)
  {
    this->T[i]->community_guru = communities(dre);
  }

  this->current_alive = this->T.size();
}

void Reincarnation::performKarma(int start, int end, int type)
{
  uniform_int_distribution<int> prop(0, n - 1);
  // INFLUENCE
  if(type == GURU) {
    for (int i = start; i < end; i++)
    {
      if(this->T[i]->lifetime > 0) {
        int change = prop(dre);
        this->T[i]->karma[change] = this->best_guru->karma[change];
        computeSoulCost(this->T[i]);
        this->T[i]->lifetime--;
        // printf("%d, ", this->T[i]->lifetime);
        if(this->T[i]->lifetime == 0) {
          this->current_alive--;
        }
      }
    }
  }
  else if(type == COMMONER) {
    for (int i = start; i < end; i++)
    {
      if(this->T[i]->lifetime > 0) {
        int change = prop(dre);
        int guru = this->T[i]->community_guru;
        this->T[i]->karma[change] = this->T[guru]->karma[change];
        computeSoulCost(this->T[i]);
        this->T[i]->lifetime--;
        if(this->T[i]->lifetime == 0) {
          this->current_alive--;
        }
      }
    }
  }
  // SELF STUDY
  else if(type == ATHEIST) {
    for (int i = start; i < end; i++)
    {
      if(this->T[i]->lifetime > 0) {
        int change = prop(dre);
        int tmp = this->T[i]->karma[0];
        this->T[i]->karma[0] = this->T[i]->karma[change];
        this->T[i]->karma[change] = tmp;
        this->T[i]->lifetime--;
        if(this->T[i]->lifetime == 0) {
          this->current_alive--;
        }
      }
    }
  }
}

void Reincarnation::computeSoulCost(Soul *s)
{
  int bins = 0;
  int actualBin = 0;
  for (int item : s->karma)
  {
    if (actualBin + item > this->bin_size)
    {
      bins++;
      actualBin = item;
    }
    else
    {
      actualBin += item;
    }
  }
  s->cost = bins;
}

void Reincarnation::setRandomEngine(int seed)
{
  default_random_engine dre(seed);
  this->dre = dre;
}

bool karmaSort(Soul *a, Soul *b)
{
  return a->cost < b->cost;
}