#include <chrono>
#include <locale>
#include <ncurses.h>
#include <rapidfuzz/fuzz.hpp>
#include <stdio.h>
#include <string>
#include <cstring>
#include <thread>
#include <vector>


using namespace std;

#define INPUT_CURSOR 1
#define SELECT_CURSOR 2
#define SELECT_ITEM 3
#define COLOR_DEFAULT -1
#define ctrl(x) ((x)&0x1f)

void delete_str(std::string &text);
void sortFuzzy(std::string query, std::vector<std::string> &items);
std::string ffui(std::vector<std::string> items);

// extern "C" {
// 	string ffui(vector<string> items);
// }

string ffui(vector<string> items) {
  // Initialize
  WINDOW *win;

  win = initscr();
  setlocale(LC_ALL, "");
  noecho();
  nodelay(win, TRUE);
  curs_set(0);
  nonl();
  use_default_colors();
  start_color();

  // Set color alias
  init_pair(INPUT_CURSOR, COLOR_CYAN, COLOR_DEFAULT);
  init_pair(SELECT_CURSOR, COLOR_RED, COLOR_DEFAULT);
  init_pair(SELECT_ITEM, COLOR_WHITE, COLOR_BLACK);

  int w, h;
  int cursorPos;
  string select_item;
  string search_query;

  // Y-coordinate of the bottom of the selection
  int selectMenuUnderY = 3;

  vector<string> matchedItems(items);

  getmaxyx(stdscr, h, w);
  cursorPos = h - selectMenuUnderY;

  while (true) {
    // Show items
    for (int idx = 0; idx < 15; idx++) {
      if (cursorPos == (h - selectMenuUnderY - idx)) {
        // hightlight select item
        attron(COLOR_PAIR(SELECT_ITEM));
        mvprintw(h - selectMenuUnderY - idx, 3, matchedItems[idx].c_str());
        select_item = matchedItems[idx];
        attroff(COLOR_PAIR(SELECT_ITEM));
      } else {
        mvprintw(h - selectMenuUnderY - idx, 3, matchedItems[idx].c_str());
      }
    }

    // for (int idx = 0; idx < matchedItems.size(); idx++) {
    //     mvprintw(h - 17 - idx, 3, matchedItems[idx].c_str());
    // }

    // cbreak();

    int c = getch();

    switch (c) {
    case ctrl('p'):
      // cursor up
      cursorPos = cursorPos - 1;
      erase();
      break;

    case ctrl('n'):
      // cursoe down
      cursorPos = cursorPos + 1;
      erase();
      break;

    case KEY_BACKSPACE:
      // remove input text
      delete_str(search_query);
      break;
    case KEY_DC:
      // remove input text
      delete_str(search_query);
      break;

    case 127:
      // remove input text
      delete_str(search_query);
      break;

    case ctrl('h'):
      delete_str(search_query);
      break;

    case ctrl('u'):
      search_query.clear();
      erase();
      break;

    case '\r':
      goto Exit;
      break;

    case '\n':
      goto Exit;
      break;

    default:
      if (c == '\b') {
        delete_str(search_query);
        break;
      } else

      if (c >= 0x00 && c <= 0x7F) {
        search_query.push_back(c);
        // fuzzy match and sorting
        sortFuzzy(search_query, matchedItems);
      }
      

      break;
    }

    // DEBUG
    // mvprintw(10, 3, select_item.c_str());
    // mvprintw(12, 3, "%d", matchedItems.size());

    // cursorPos top stopper
    if (cursorPos <= (h - selectMenuUnderY - items.size() + 1)) {
      cursorPos = h - selectMenuUnderY - items.size() + 1;
    }

    // cursorPos under stopper
    if (cursorPos >= (h - selectMenuUnderY)) {
      cursorPos = h - selectMenuUnderY;
    }

    // select cursor
    attron(COLOR_PAIR(SELECT_CURSOR));
    mvprintw(cursorPos, 1, "> ");
    attroff(COLOR_PAIR(SELECT_CURSOR));

    // input cursor
    attron(COLOR_PAIR(INPUT_CURSOR));
    mvprintw(h - 1, 1, "> ");
    attroff(COLOR_PAIR(INPUT_CURSOR));

    // mvhline(h - 2, 3, '─', w);
    string matchedItemsLen = to_string(matchedItems.size());

    if (matchedItemsLen.size() >= 2) {
      mvprintw(h - 2, 3, matchedItemsLen.c_str());
      mvprintw(h - 2, 5, "/");
      mvprintw(h - 2, 6, "%d", items.size());

      mvhline(h - 2, 9, '-', w);
    } else {
      mvprintw(h - 2, 3, matchedItemsLen.c_str());
      mvprintw(h - 2, 4, "/");
      mvprintw(h - 2, 5, "%d", items.size());

      mvhline(h - 2, 7, '-', w);
    }

    mvprintw(h - 1, 3, search_query.c_str());
    // getstr(&search_query);

    // 60FPS
    std::this_thread::sleep_for(16ms);
  }

Exit:
  endwin();

  return select_item.c_str();
}

void delete_str(string &text) {
  if (text.empty()) {
    text.clear();
  } else {
    text.pop_back();
  }

  erase();
}

void sortFuzzy(string query, vector<string> &items) {
  sort(items.begin(), items.end(), [&query](string &a, string &b) {
    return rapidfuzz::fuzz::ratio(query, a) > rapidfuzz::fuzz::ratio(query, b);
  });
}
