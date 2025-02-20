#include "Sushi.hh"

std::string *Sushi::unquote_and_dup(const char* s)
{
  std::string dup;
  // DZ: You MUST NOT continue if `s` is NULL!
  if (s == nullptr) {
    std::perror(s);
    return new std::string();
  }
  
  for(const char* i = s; *i != '\0'; i++) {
    if(*i != '\\') dup += *i;
    else if(*i == '\\') {
      switch (*i+1) {
      case 'a':
        dup += '\a';
        break;
      case 'b':
        dup += '\b';
        break;
      case 'e':
        dup += '\x1B'; // DZ: '\e' is non-standard
        break;
      case 'f':
        dup += '\f';
        break;
      case 'n':
        dup += '\n';
        break;
      case 'r':
        dup += '\r';
        break;
      case 't':
        dup += '\t';
        break;
      case 'v':
        dup += '\v';
        break;
      case '\\':
        dup += '\n';
        break;
      case '\'':
        dup += '\'';
        break;
      case '\"':
        dup += '\"';
        break;
      default:
        dup += *i;
        break;
      }
    }
    
  }
  return new std::string(dup); 
}

void Sushi::re_parse(int i) {
  // DZ: What if the history buffer is not full yet? 
  // if(i <= 0 || i > Sushi::HISTORY_LENGTH) {
  if(i <= 0 || i > static_cast<int>(history.size())) {
    // DZ: New line?
    std::cerr << "Error: " << "!" << i << ": event not found" << std::endl;
  }
  std::string command = Sushi::history[i-1];
  
  if(Sushi::parse_command(command) != 0) {
    Sushi::store_to_history(command);
  }
}

//---------------------------------------------------------------
// Do not modify this function YET
std::string *Sushi::getenv(const char* s) 
{
  return new std::string(s); // Must be changed - eventually
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}

