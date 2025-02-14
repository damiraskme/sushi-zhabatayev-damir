#include <cstdlib>
#include <iostream>
#include "Sushi.hh"


const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

Sushi my_shell;

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);
  std::string line;
  my_shell.set_exit_flag();

  while(my_shell.get_exit_flag()) {
    std::cout << Sushi::DEFAULT_PROMPT;
    line = my_shell.read_line(std::cin);
    if(my_shell.parse_command(line) == 0 ) my_shell.store_to_history(line);  
  }
  
  return EXIT_SUCCESS;
}
