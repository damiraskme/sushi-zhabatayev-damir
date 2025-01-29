#pragma once
#include <string> 
#include <limits>
#include <queue>
#include <fstream>
#include <filesystem>
#include <iostream>

class Sushi {
private:
  static const size_t HISTORY_LENGTH;
  static const size_t MAX_INPUT;
  static int count;
  std::queue<std::string> history;

public:
  Sushi() : history() {};
  std::string read_line(std::istream &in);
  bool read_config(const char *fname, bool ok_if_missing);
  void store_to_history(std::string line);
  void show_history();
  static const std::string DEFAULT_PROMPT;
};

#define UNUSED(expr) do {(void)(expr);} while (0)
