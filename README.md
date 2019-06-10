## About 🕉️
This project forms part of Heuristic combinatorial optimization course that forms part of Computer Science degree at **Facultad de Ciencias, Universidad Nacional Autónoma de México**. It tries to find a solution to Bin Packing Problem using Reincarnation algorithm with some few variants.

For further understanding you can refer to the [PDF document in spanish](tex/Reencarnacion.pdf).

## Building and running

[Meson build system](https://mesonbuild.com/index.html) is used to compile this project. Running:
```
$ meson build && cd build
$ ninja
```
in the root directory should setup *build* directory with the executable inside.

Use `$ build/BPP_Reincarnation -h` to know more about the available options.
```
$ ./BPP_Reincarnation -h
BPP solution using Reincarnation heuristic.
Usage:
  ./BPP_Reincarnation [OPTION...]

  -h, --help             Show help
  -f, --file input_file  Input file to read instance (ignore to read from
                         Tip: use ./instance-gen -h to create test
                         instances.
  -s, --seed N           Seed to use. Default is 0
```

## Instance generator
A very simple instance generator for BPP is included to make testing easier.
```
$ ./instance-gen -h
Instance generator for Bin Packing Problem.
Usage:
  ./instance-gen [OPTION...]

  -h, --help     Show help
  -n, --items N  Number of items.
  -b, --bin N    Bin size.
  -s, --seed N   Seed to use for random engine.
```

## Available tune options
The ant colony optimization heuristic can be tuned to experiment different results.
The header file [include/Reincarnation.hpp](include/Reincarnation.hpp) contains the constraints that can be modified.

Credits to [jarro2783](https://github.com/jarro2783/) for his [cxxopts](https://github.com/jarro2783/cxxopts) library to parse command line options.