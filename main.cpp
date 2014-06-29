#include "commonheader.h"
#include "storage.h"
#include "aheuicode.h"
#include "interpreter.h"

int main()
{
  locale::global(locale("ko_KR.UTF-8"));
  AheuiInterpreter interpreter;
  AheuiCode code;
  code.read_file("test.ah");
  interpreter.initialize(&code);
  while(true)
  {
    interpreter.step();
    interpreter.move_cursor();
  }
}
