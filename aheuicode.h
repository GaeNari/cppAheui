#pragma once

class AheuiCode
{
private:
  int x_len;
  int y_len;
  vector<wstring> codespace;
public:
  void read_file(const string& file_name);
  wchar_t get_code(const unsigned int x, const unsigned int y);
  tuple<int, int, int> split_code(const wchar_t code_char);
  void print_code();
  int x_size();
  int y_size();
};