project(
  'BPP_Reincarnation',
  'cpp', default_options : ['cpp_std=c++11', 'buildtype=release', 'warning_level=1'])

incdir = include_directories('include')

src = ['src/Reincarnation.cpp', 'src/main.cpp']

gen = ['src/instance-gen.cpp']

executable(
  'BPP_Reincarnation',
  src,
  include_directories : incdir)

executable(
  'instance-gen',
  gen,
  include_directories : incdir)