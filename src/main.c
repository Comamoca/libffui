#include "ffui.hpp"
#include <stdio.h>
#include <cstring>

int main() {
  using namespace std;

  const char *houkura[] = {"kaho", "tiyoko", "rinze", "natuha", "juri"};
  size_t houkura_size = sizeof(houkura) / sizeof(houkura[0]);


  char selected_c = ffui_c(houkura);

  printf("%s", selected_c);

  return 0;
}
