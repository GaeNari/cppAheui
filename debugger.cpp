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
