#pragma once

class AheuiInterpreter;
class AheuiStorage;

struct breakpoint
{
  int x;
  int y;
};

enum JUJAK_TYPE
{
  STR_PUSH,
  STR_POP,
  STR_SWAP,
  STR_DUP,
};

class AheuiDebugger
{
private:
  vector<struct breakpoint> breakpoints;
  AheuiInterpreter *target;
  AheuiStorage *storage;
public:
  void initialize(AheuiInterpreter *t);
  void show_code();
  void show_storage(const wchar_t name);
  void show_breakpoints();
  void set_breakpoint(int x, int y);
  void delete_breakpoint(int num);
  void step();
  void step(int num);
  void cont();
  void set_storage(const wchar_t name);
  void jujak_storage(JUJAK_TYPE type);
  void jujak_storage(JUJAK_TYPE type, long long value);
};
