#pragma once

class AheuiInterpreter;

struct breakpoint
{
  int x;
  int y;
};

class AheuiDebugger
{
private:
  vector<struct breakpoint> breakpoints;
  AheuiInterpreter *target;
public:
  void initialize(AheuiInterpreter *t);
  void show_code();
  void show_storage(const wchar_t name);
  void show_breakpoints();
  void set_breakpoint(int x, int y);
  void delete_breakpoint(int num);
  void step();
  void step(int num);
};
