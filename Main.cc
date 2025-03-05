#include <cstdlib>
#include <iostream>
#include "Sushi.hh"


const std::string Sushi::DEFAULT_PROMPT = "sushi> ";
const std::string Sushi::DEFAULT_CONFIG = "sushi.conf";

Sushi my_shell;

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);

  Sushi::prevent_interruption();
  
  std::string line;

  const char *home_dir = std::getenv("HOME");
  if (!home_dir) {
    std::cerr << "Error: HOME environment variable not set." << std::endl;
    return EXIT_FAILURE;
  }

  my_shell.read_config(Sushi::DEFAULT_CONFIG.c_str(), true);
  
  while(!my_shell.get_exit_flag()) {
    std::cout << Sushi::DEFAULT_PROMPT;
    line = my_shell.read_line(std::cin);
    if(line.empty()) std::cin.clear();
    if(my_shell.parse_command(line) == 0 ) my_shell.store_to_history(line);  
  }
  
  return EXIT_SUCCESS;
}
