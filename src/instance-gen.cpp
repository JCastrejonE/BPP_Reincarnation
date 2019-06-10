#include <iostream>
#include <random>
#include "jarro2783/cxxopts.hpp"

using namespace std;

int main(int argc, char **argv)
{
  (void)argc;
  int n = 0, b = 0, seed = 0;

  cxxopts::Options options(argv[0], "Instance generator for Bin Packing Problem.");
  try
  {
    options
      .add_options()
      ("h, help", "Show help")
      ("n, items", "Number of items.", cxxopts::value<int>(), "N")
      ("b, bin", "Bin size.", cxxopts::value<int>(), "N")
      ("s, seed", "Seed to use for random engine.", cxxopts::value<int>(), "N");

    auto result = options.parse(argc, argv);
    if (result.count("h"))
    {
      cout << options.help() << endl;
      return 0;
    }
    if (result.count("n"))
    {
      n = result["n"].as<int>();
    }
    if (result.count("b"))
    {
      b = result["b"].as<int>();
    }
    if (result.count("s"))
    {
      seed = result["s"].as<int>();
    }
  }
  catch (const cxxopts::OptionException &e)
  {
    cout << "Error parsing options: " << e.what() << endl;
    return 1;
  }

  default_random_engine dre(seed);
  uniform_int_distribution<int> uid(1, b);

  printf("%d %d\n", n, b);
  for (int i = 0; i < n; i++)
  {
    printf("%d\n", uid(dre));
  }

  return 0;
}