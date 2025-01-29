#include <cstdlib>
#include <iostream>
#include "Sushi.hh"

// Initialize the static constants
const size_t Sushi::MAX_INPUT = 256;
const size_t Sushi::HISTORY_LENGTH = 10;
int Sushi::count = 1;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";


int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);
  Sushi sushi;
  std::string line;
  
  sushi.read_config("sushi.conf", false); //Read existing file
  sushi.show_history();
  sushi.read_config("sushi1.conf", false); //File does not exist
  sushi.read_config("sushi1.conf", true); //File does not exist but ok_if_missing = true


  while(true) {
    std::cout << Sushi::DEFAULT_PROMPT;
    line = sushi.read_line(std::cin);
    std::cout << Sushi::DEFAULT_PROMPT << line << std::endl;
    sushi.show_history();
  }
  
  return EXIT_SUCCESS;
}
