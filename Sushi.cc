#include "Sushi.hh"
#include <cmath>

std::string Sushi::read_line(std::istream &in)
{
  std::string line;
  if(!std::getline (in, line)) {
    if(!in.eof()) { 
      std::perror("getline");
    }
    return "";
  }
    
  if(std::all_of(line.begin(), line.end(), isspace)) {
    return "";
  }

  if(line.size() > Sushi::MAX_INPUT) {
    line.resize(Sushi::MAX_INPUT);
    std::cerr << "Line too long, truncated." << std::endl;
  }
  
  return line; 
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  std::ifstream ifs(fname);
  std::string line;
  if(!ifs.good()) {
    if(ok_if_missing) return true;
    std::perror(fname);
    return false;
  }
  
  while(!ifs.eof()) {
    line = read_line(ifs);
    if(parse_command(line) == 0 ) store_to_history(line);
  }

  if (ifs.bad()) {
       std::perror("File reading error");
        return false;
    }

    ifs.close();
    if (ifs.fail()) {
        std::perror("Error closing file");
        return false;
    }
    return true;

}

void Sushi::store_to_history(std::string line)
{
  if(line.empty()) return;
  while(history.size() >= HISTORY_LENGTH) {
    history.pop_front();
  }
  history.emplace_back(line); 
}


void Sushi::show_history()
{
  int i = 1;
  for (const auto &line : history) {
    std::cout << std::setw(5) << i++ << " " << line << std::endl;
  }
}

void Sushi::set_exit_flag()
{
  Sushi::exit_flag = true;
}

bool Sushi::get_exit_flag() const
{
  return Sushi::exit_flag;
}

//---------------------------------------------------------
// New methods
int Sushi::spawn(Program *exe, bool bg)
{
  // Must be implemented
  UNUSED(exe);
  UNUSED(bg);

  return EXIT_SUCCESS;
}

void Sushi::prevent_interruption() {
  // Must be implemented
}

void Sushi::refuse_to_die(int signo) {
  // Must be implemented
  UNUSED(signo);
}

char* const* Program::vector2array() {
  // Must be implemented
  return nullptr; 
}

void Program::free_array(char *const argv[]) {
  // Must be implemented
  UNUSED(argv);
}

Program::~Program() {
  // Do not implement now
}
