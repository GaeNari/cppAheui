#include "commonheader.h"
#include "storage.h"
#include "aheuicode.h"
#include "interpreter.h"

int main(int argc, char **argv)
{
  if(argc != 2)
  {
    wcout << L"usage : " << argv[0] << " " << "<file_name>" << endl;
    exit(1);
  }
  locale::global(locale("ko_KR.UTF-8"));
  AheuiInterpreter interpreter;
  AheuiCode code;
  if(!code.read_file(argv[1]))
  {
    wcout << L"Cannot open file" << endl;
    exit(-1);
  }
  interpreter.initialize(&code);
  while(true)
  {
    interpreter.step();
    interpreter.move_cursor();
  }
}
