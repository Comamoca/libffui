<div align="center">

![Last commit](https://img.shields.io/github/last-commit/Comamoca/libffui?style=flat-square)
![Repository Stars](https://img.shields.io/github/stars/Comamoca/libffui?style=flat-square)
![Issues](https://img.shields.io/github/issues/Comamoca/libffui?style=flat-square)
![Open Issues](https://img.shields.io/github/issues-raw/Comamoca/libffui?style=flat-square)
![Bug Issues](https://img.shields.io/github/issues/Comamoca/libffui/bug?style=flat-square)

<img src="https://emoji2svg.deno.dev/api/🦊" alt="eyecatch" height="100">

# libffui

Simple fuzzy select UI library.

<br>
<br>


</div>

<div align="center">

</div>

https://github.com/Comamoca/haru/assets/93137338/e00ca0b1-9466-4493-8f4b-6348570a11b3

## 🚀 How to use

```
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
```

## ⬇️  Install

### Using CMake

WIP

## ⛏️   Development

```sh
cmake -B build && cmake --build build/ && ./build/app
```
## 📝 Todo

- [ ] Create C API.
- [ ] Add filter process after transform.

## 📜 License

MIT

### 🧩 Modules

- [RapidFuzz](https://github.com/rapidfuzz/RapidFuzz)
- [ncurses](https://invisible-island.net/ncurses/announce.html)

## 👏 Affected projects

- [fzf](https://github.com/junegunn/fzf)
- [fzy](https://github.com/jhawthorn/fzy)
