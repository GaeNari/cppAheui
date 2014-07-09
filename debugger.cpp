#include "commonheader.h"
#include "debugger.h"
#include "interpreter.h"
#include "storage.h"

void AheuiDebugger::initialize(AheuiInterpreter *t)
{
  target = t;
}

void AheuiDebugger::show_code()
{
  target->show_code();
  wcout << endl;
}

void AheuiDebugger::show_storage(const wchar_t name)
{
  unsigned int index = (static_cast<unsigned int>(name) - 0xac00) % 28;
  AheuiStorage *storage = target->get_storage(index);
  list<long long>::const_iterator iter;
  for(iter=storage->begin(); iter!=storage->end(); ++iter)
  {
    wcout << (*iter);
    if((0xac00 <= *iter) && (*iter <= 0xd7a3))
    {
      wcout << " (" << static_cast<wchar_t>(*iter) << ")";
    }
    wcout << endl;
  }
}

void AheuiDebugger::show_breakpoints()
{
  vector<struct breakpoint>::const_iterator iter;
  int count = 0;
  wcout << endl;
  for(iter=breakpoints.begin(); iter!=breakpoints.end(); ++iter)
  {
    wcout << L"breakpoint " << count++ << L" (" << (*iter).x << L"," << (*iter).y << L")" << endl;
  }
}

void AheuiDebugger::set_breakpoint(int x, int y)
{
  struct breakpoint b;
  b.x = x;
  b.y = y;
  breakpoints.push_back(b);
}

void AheuiDebugger::delete_breakpoint(int num)
{
  breakpoints.erase(breakpoints.begin()+num);
}

void AheuiDebugger::step()
{
  target->step();
  target->move_cursor();
}

void AheuiDebugger::step(int num)
{
  assert(!(num<0));
  while(num --> 0)
    this->step();
}

void AheuiDebugger::cont()
{
  while(1)
  {
    step();
    bool hit = false;
    tuple<int, int> cursor = target->get_cursor();
    vector<struct breakpoint>::const_iterator iter;
    int count = 0;
    for(iter=breakpoints.begin(); iter!=breakpoints.end(); ++iter)
    {
      if(((*iter).x == get<0>(cursor)) && ((*iter).y == get<1>(cursor)))
      {
	hit = true;
	break;
      }
      count++;
    }
    if(hit)
    {
      wcout << L"breakpoint " << count << L" (" << (*iter).x << "," << (*iter).y << ")" << endl;
      break;
    }
  }
}
