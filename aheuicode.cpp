#include "commonheader.h"
#include "aheuicode.h"

template<typename T>
void AheuiCode::load_code(T& is)
{
  static_assert(std::is_convertible<T*, wistream*>::value, "input stream must be derived from wistream");
  x_len = 0; y_len = 0;
  codespace.clear();
  wstring buffer;
  while(getline(is,buffer))
  {
    codespace.push_back(buffer);
    int line_len = buffer.length();
    if(x_len < line_len) x_len = line_len;
    y_len++;
  }
}

bool AheuiCode::read_file(const string& file_name)
{
  wifstream ifs(file_name);
  if(!ifs.is_open()) return false;
  load_code<>(ifs);
  return true;
}

wchar_t AheuiCode::get_code(const unsigned int x, const unsigned int y)
{
  if(y<0 || x<0 || !(y<codespace.size()) || !(x<codespace[y].length()))
  {
    return 0xfffd;
  }
  return codespace[y][x];
}

tuple<int, int, int> AheuiCode::split_code(const wchar_t code_char)
{
  if((0xac00<=code_char) && (code_char <=0xd7a3))
  {
    unsigned int code = static_cast<unsigned int>(code_char) - 0xac00;
    return make_tuple(code/588, (code/28)%21, code%28);
  }
  else
    return make_tuple(-1,-1,-1);
}

void AheuiCode::print_code()
{
  vector<wstring>::const_iterator iter;
  int i=0;
  for(iter=codespace.begin(); iter!=codespace.end(); ++iter)
  {
    wcout << i++ << " " << (*iter) << endl;
  }
}

int AheuiCode::x_size()
{
  return x_len;
}

int AheuiCode::y_size()
{
  return y_len;
}
