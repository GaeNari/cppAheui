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
      wstring input;
      wcout << endl;
      debugger.show_code();
      getline(wcin,input);
      int found = input.find(L" ");
      wstring operation;
      wstring argument;
      bool arg_exist = false;
      if(found != -1)
      {
	assert(input.length()>found);
	operation = input.substr(0,found);
	argument = input.substr(found+1);
	arg_exist = true;
      }
      else
	operation = input;
      if(!operation.compare(L"step"))
      {
	if(arg_exist)
	  debugger.step(stoi(argument));
	else
	  debugger.step();
      }
      else if(!operation.compare(L"print"))
      {
	assert(arg_exist);
	debugger.show_storage(static_cast<wchar_t>(argument[0]));
      }
      else if(!operation.compare(L"break"))
      {
	//TODO: add breakpoint
      }
      else if(!operation.compare(L"clear"))
      {
	//TODO: remove breakpoint
      }
      else if(!operation.compare(L"continue"))
      {
	//TODO: continue
      }
      else if(!operation.compare(L"quit"))
	exit(0);
      else
	wcout << L"Invalid operation";
      wcout << endl;
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
