#pragma once

class AheuiCode;
class AheuiStorage;
class AheuiStack;
class AheuiQueue;

class AheuiInterpreter
{
private:
  static const int required_elements[];
  static const int required_elements_go_to[];
  static const int final_strokes[];
  AheuiCode *code;
  struct
  {
    int x;
    int y;
    int dx;
    int dy;
  } cursor;
  AheuiStack *stack[27];
  AheuiQueue *queue;
  AheuiStorage *storage;
  bool goto_mode;
  const int *required;
public:
  void initialize(AheuiCode *ah, bool goto_mode);
  void step();
  void execute(wchar_t character);
  void move_cursor();
  void move_cursor(int x, int y);
  void show_code();
  AheuiStorage* get_storage(int index);
  tuple<int, int> get_cursor();
};
