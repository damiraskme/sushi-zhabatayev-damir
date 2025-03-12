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
    // DZ: Once the file is closed, its status is 'fail'
    /*
    if (ifs.fail()) {
        std::perror("Error closing file");
        return false;
    }
    */
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
  UNUSED(bg);
  pid_t child_pid = fork();
  if(child_pid == -1) {
    std::perror("fork");
    return EXIT_FAILURE;
  }

  else if(child_pid == 0) {
    char* const* arr = exe->vector2array();
    int status = execvp(exe->progname().c_str(), arr);
    if(status == -1) {
      // DZ: Use perror to report errors
      std::perror(arr[0]);
      /*
      if(errno == ENOENT) {
        std::cerr << "Error: Command '" << exe->progname() << "' not found." << std::endl;
        exit(EXIT_FAILURE);
      }
      else {
        std::perror("execvp");
        exit(EXIT_FAILURE);
	}*/
    }
    exe->free_array(arr);
  }

  else if(child_pid != 0 && child_pid != -1) {
    pid_t status = waitpid(child_pid, nullptr, 0);
    if (status == -1) {
          std::perror("waitpd");
          return EXIT_FAILURE;
          }
    return EXIT_SUCCESS;
  }

  // DZ: Must formally return something here
    return EXIT_SUCCESS;
}

void Sushi::prevent_interruption() {
  struct sigaction sigintHandler;
  sigintHandler.sa_handler = refuse_to_die;
  sigemptyset(&sigintHandler.sa_mask);
  sigintHandler.sa_flags = 0;

  sigaction(SIGINT, &sigintHandler, NULL);
}

void Sushi::refuse_to_die(int signo) {
  UNUSED(signo);
  std::cout << "Type exit to exit the shell" << std::endl;
}

void Sushi::mainloop() {
  // Must be implemented
}

char* const* Program::vector2array() {
  size_t size = args->size();
  char** arr = new char*[size + 1]; 

  for (size_t i = 0; i < size; i++) {
    arr[i] = const_cast<char*>(args->at(i)->data());
  }
  arr[size] = nullptr;

  return arr;
}


void Program::free_array(char *const argv[]) {
  delete[] argv;
}

Program::~Program() {
  // Do not implement now
}
