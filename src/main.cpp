#include "ffui.hpp"
#include <stdio.h>

#include <string>
#include <vector>

int main() {
  using namespace std;

  vector<string> choices = {
      "file1.cpp", "file2.h",   "main.cpp", "README.md", "config.json",
      "image.jpg", "script.sh", "data.csv", "test.cpp",  "util.h"};

  string selected = ffui(choices);
  printf("%s\n", selected.c_str());

  return 0;
}
