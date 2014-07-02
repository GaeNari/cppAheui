#include "commonheader.h"
#include "storage.h"
#include "aheuicode.h"
#include "interpreter.h"
#include "debugger.h"
#include <cstring>

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    wcout << L"usage : " << argv[0] << " " << L"<file_name> [-debug]" << endl;
    exit(1);
  }
  locale::global(locale("ko_KR.UTF-8"));
  AheuiInterpreter interpreter;
  AheuiCode code;
  if(!code.read_file(argv[1]))
  {
    wcout << L"Cannot open " << argv[1] << endl;
    exit(1);
  }
  interpreter.initialize(&code);
  if(argv[2])
  {
    if(strcmp(argv[2],"-debug"))
    {
      wcout << L"Only \"-debug\" option is available" << endl;
      exit(1);
    }
    AheuiDebugger debugger;
    debugger.initialize(&interpreter);
    while(true)
    {
      wchar_t input;
      debugger.show_code();
      wcout << endl;
      wcin >> input;
      debugger.show_storage(input);
      wcout << endl;
      debugger.step();
    }
  }
  else
  {
    while(true)
    {
      interpreter.step();
      interpreter.move_cursor();
    }
  }
}
