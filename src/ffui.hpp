#ifndef   __LIB_HPP
#define   __LIB_HPP

#include <string>
#include <vector>

void delete_str(std::string &text);
void sortFuzzy(std::string query, std::vector<std::string> &items);
std::string ffui(std::vector<std::string> items);

// extern "C" {
// 	const char* ffui_c(const char* items[], size_t items_length);
// 	std::string ffui(std::vector<std::string> items);
// }

#endif
