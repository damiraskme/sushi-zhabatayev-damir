#include "Sushi.hh"

std::string *Sushi::unquote_and_dup(const char* s)
{
  std::string dup;
  if (s == nullptr) std::perror(s);
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
        dup += '\e';
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
  return new std::string(dup); // Must be changed
}

void Sushi::re_parse(int i) {
  if(i <= 0 || i > Sushi::HISTORY_LENGTH) {
    std::cerr << "Error: " << "!" << i << ": event not found";
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

