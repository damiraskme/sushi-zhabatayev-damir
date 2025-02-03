#include <cstdlib>
#include <iostream>
#include "Sushi.hh"

// Initialize the static constants
// DZ: Moved to header file to avoid the `variable length array` error
// const size_t Sushi::MAX_INPUT = 256;
// const size_t Sushi::HISTORY_LENGTH = 10;
int Sushi::count = 1;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

Sushi my_shell; // New global var

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);
  // DZ: Moved to globals. Not an error.
  // Sushi sushi;
  std::string line;
  
  my_shell.read_config("sushi.conf", false); //Read existing file
  my_shell.show_history();
  my_shell.read_config("sushi1.conf", false); //File does not exist
  my_shell.read_config("sushi1.conf", true); //File does not exist but ok_if_missing = true


  // DZ: You did not include the _real_ case:
  // if(!my_shell.read_config("sushi.conf", true)) {...}
  
  while(true) {
    std::cout << Sushi::DEFAULT_PROMPT;
    line = my_shell.read_line(std::cin);
    // DZ: why?
    // std::cout << Sushi::DEFAULT_PROMPT << line << std::endl;
    // DZ: The line must be stored to history HERE, not in `read_line`
    my_shell.show_history();
  }
  
  return EXIT_SUCCESS;
}
