#include <cstdlib>
#include <iostream>
#include "Sushi.hh"


const std::string Sushi::DEFAULT_PROMPT = "sushi> ";
const std::string Sushi::DEFAULT_CONFIG = "sushi.conf";

Sushi my_shell;

int main(int argc, char *argv[])
{
  if (!my_shell.read_config("sushi.conf", false)) {
    exit(EXIT_FAILURE);
  }
  if(argc >= 1) {
    for(int i = 1; i < argc; i++) {
      if(!my_shell.read_config(argv[i], false)) {
        exit(EXIT_FAILURE);
      }
    }
  }
  
  my_shell.mainloop();

  return EXIT_SUCCESS;
}
