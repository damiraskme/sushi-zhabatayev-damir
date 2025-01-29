#include "Sushi.hh"
#include <cmath>

std::string Sushi::read_line(std::istream &in)
{
  char buffer[Sushi::MAX_INPUT];
  in.getline(buffer, Sushi::MAX_INPUT);
  
   if (in.fail() && !in.eof()) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Line too long, truncated." << std::endl;
        return "";
    }

  std::string line(buffer);

  line.erase(line.find_last_not_of(" \t\f\v\n\r") + 1);
  line.erase(0, line.find_first_not_of(" \t\f\v\n\r"));

  if(line.empty()) {
    std::cerr << "Line empty, truncated" << std::endl;
    return "";
  }
  store_to_history(line);
  return line;
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  std::ifstream ifs(fname);
  if(!ifs.good()) {
    if(ok_if_missing) return true;
    std::perror("File does not exist"); return false;
  }
  
  while(!ifs.eof()) {
    read_line(ifs);
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
  int size = history.size();
  if(line.empty()) return;
  if(size >= Sushi::HISTORY_LENGTH) {
    history.pop();
    history.push(line);
  }
  else {
    history.push(line);
  }
  Sushi::count++;
}


void Sushi::show_history()
{
  std::queue<std::string> temp = history;
  for (int i = 0; i < history.size(); i++) {
    std::cout << std::setw(5) << std::right << 
      abs(Sushi::count - history.size() + i) << "  " << temp.front() << std::endl;
    temp.pop();
  }
}

