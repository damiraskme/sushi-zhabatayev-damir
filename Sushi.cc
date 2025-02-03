#include "Sushi.hh"
#include <cmath>

std::string Sushi::read_line(std::istream &in)
{
  char buffer[Sushi::MAX_INPUT]; // DZ: MAX_INPUT+1, off by 1 error
  in.getline(buffer, Sushi::MAX_INPUT);
  
   if (in.fail() && !in.eof()) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// DZ: "The excess characters (including the newline) should be discarded..."
	// DZ: You did not truncate it, you discarded it
        std::cerr << "Line too long, truncated." << std::endl;
        return "";
    }

  std::string line(buffer);

  line.erase(line.find_last_not_of(" \t\f\v\n\r") + 1);
  line.erase(0, line.find_first_not_of(" \t\f\v\n\r"));

  // DZ: Same here
  if(line.empty()) {
    std::cerr << "Line empty, truncated" << std::endl;
    return "";
  }

  // DZ: This is not read_line's responsibility
  store_to_history(line);
  return line;
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  std::ifstream ifs(fname);
  if(!ifs.good()) {
    if(ok_if_missing) return true;
    // DZ: wrong use of perror
    // std::perror("File does not exist");
    std::perror(fname);
    return false;
  }
  
  while(!ifs.eof()) {
    read_line(ifs);
    // DZ: and store to history
  }

  if (ifs.bad()) {
     // DZ: wrong use of perror
       std::perror("File reading error");
        return false;
    }

    ifs.close();
    if (ifs.fail()) {
    // DZ: wrong use of perror
        std::perror("Error closing file");
        return false;
    }
    return true;

}

void Sushi::store_to_history(std::string line)
{
  // DZ: not `int` but `size_t` (unsigned comparizon)
  int size = history.size();
  if(line.empty()) return;
  if(size >= Sushi::HISTORY_LENGTH) {
    history.pop();
    history.push(line); // DZ: This line should be after `if`
  }
  else {
    history.push(line); // DZ: This line should be after `if`
  }
  // DZ: `count` should not be a static variable
  // my_sushi.count++
  Sushi::count++;
}


void Sushi::show_history()
{
  // DZ: You should have used dequeue, which is iterable
  std::queue<std::string> temp = history;
  // DZ: not `int` but `size_t` (unsigned comparizon)
  for (int i = 0; i < history.size(); i++) {
    // DZ: "Each string should be prefixed by the sequential number (starting at 1)"
    std::cout << std::setw(5) << std::right << 
      abs(Sushi::count - history.size() + i) << "  " << temp.front() << std::endl;
    temp.pop();
  }
}

void Sushi::set_exit_flag()
{
  // To be implemented
}

bool Sushi::get_exit_flag() const
{
  return false; // To be fixed
}
