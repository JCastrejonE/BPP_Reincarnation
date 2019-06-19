#include <iostream>
#include <chrono>
#include <fstream>
#include "jarro2783/cxxopts.hpp"
#include "best-fit.hpp"
#include "Reincarnation.hpp"

using namespace std;

int main(int argc, char **argv)
{
  auto gstart = chrono::steady_clock::now();
  int seed = 0;
  int n, b;
  bool greedy = false;
  vector<int> items;

  istream *is = &cin;
  ifstream inFile;

  cxxopts::Options options(argv[0], "BPP solution using Reincarnation heuristic.");
  try
  {
    options
      .add_options()
      ("h, help", "Show help")
      ("f, file", "Input file to read instance (ignore to read from stdin) \nTip: use ./instance-gen -h to create test instances.", cxxopts::value<string>(), "input_file")
      ("s, seed", "Seed to use. Default is 0", cxxopts::value<int>(), "N")
      ("greedy", "Compute best-fit algorithm result.");

    auto result = options.parse(argc, argv);
    if (result.count("h"))
    {
      cout << options.help() << endl;
      return 0;
    }
    if (result.count("f"))
    {
      inFile.open(result["f"].as<string>());
      is = &inFile;
    }
    if (result.count("s"))
    {
      seed = result["s"].as<int>();
    }
    if (result.count("greedy"))
    {
      greedy = true;
    }
  }
  catch (const cxxopts::OptionException &e)
  {
    cout << "Error parsing options: " << e.what() << endl;
    return 1;
  }

  *is >> n >> b;
  int tmp;
  for (int i = 0; i < n; i++)
  {
    *is >> tmp;
    items.push_back(tmp);
  }
  Reincarnation RA(items, b);
  RA.setRandomEngine(seed);

  printf("\nSeed: %d\n", seed);
  pair<vector<int>, int> S = RA.computeSolution();
  for(int x:S.first) {
    printf("%d, ", x);
  }
  printf("\nBins: %d\n", S.second);

  if(greedy)
    printf("\nBest-fit: %d\n\n", bestFit(items, items.size(), b));

  auto gend = chrono::steady_clock::now();
  printf("Total elapsed time: %lld\n", chrono::duration_cast<chrono::seconds>(gend - gstart).count());
}