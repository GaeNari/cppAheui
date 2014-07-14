#include "commonheader.h"
#include "storage.h"
#include "aheuicode.h"
#include "interpreter.h"
#include "debugger.h"

int main(int argc, char **argv)
{
  wstring help = L"\
    help: 도움말\n\
    step [숫자]: [숫자]단계 실행. 기본값은 1\n\
    print [글자]: [글자]의 받침에 해당하는 저장공간 출력\n\
    break [숫자1] [숫자2]: ([숫자1],[숫자2])에 breakpoint를 생성\n\
    show breakpoints: breakpoint들을 보여줌\n\
    clear [숫자]: [숫자]번 breakpoint를 삭제. 좌표가 아님에 유의\n\
    continue: breakpoint를 만날 때까지 계속 step\n\
    quit: 종료";
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
    string option;
    option = argv[2];
    if(option.compare("-debug"))
    {
      wcout << L"Only \"-debug\" option is available" << endl;
      exit(1);
    }
    AheuiDebugger debugger;
    debugger.initialize(&interpreter);
    while(true)
    {
      wstring input;
      debugger.show_code();
      wcout << L"(debug) ";
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
      if((!operation.compare(L"s")) || (!operation.compare(L"step")))
      {
	if(arg_exist)
	  debugger.step(stoi(argument));
	else
	  debugger.step();
      }
      else if((!operation.compare(L"p")) || (!operation.compare(L"print")))
      {
	assert(arg_exist);
	debugger.show_storage(static_cast<wchar_t>(argument[0]));
      }
      else if((!operation.compare(L"b")) || (!operation.compare(L"break")))
      {
	int x,y;
	wstringstream ss;
	ss.str(argument);
	ss >> x >> y;
	wcout << L"set breakpoint at " << x << L" " << y << endl;
	debugger.set_breakpoint(x,y);
      }
      else if(!operation.compare(L"show"))
      {
	if(!argument.compare(L"breakpoints"))
	  debugger.show_breakpoints();
      }
      else if(!operation.compare(L"clear"))
      {
	int number;
	wstringstream ss;
	ss.str(argument);
	ss >> number;
	wcout << L"delete breakpoint " << number << endl;
	debugger.delete_breakpoint(number);
      }
      else if((!operation.compare(L"c")) || (!operation.compare(L"continue")))
      {
	debugger.cont();
      }
      else if(!operation.compare(L"help"))
      {
	wcout << help << endl;
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
