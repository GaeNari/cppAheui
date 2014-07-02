#pragma once

class AheuiCode;
class AheuiStorage;
class AheuiStack;
class AheuiQueue;

class AheuiInterpreter
{
private:
  static const int required_elements[];
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
public:
  void initialize(AheuiCode *ah);
  void step();
  void move_cursor();
  void show_code();
  AheuiStorage* get_storage(int index);
};
