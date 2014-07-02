#include "commonheader.h"
#include "interpreter.h"
#include "aheuicode.h"
#include "storage.h"

const int AheuiInterpreter::required_elements[] =
{
    0, 0, 2, 2, 2, 2, 1, 0, 1, 0, 1, 0, 2, 0, 1, 0, 2, 2, 0
};

const int AheuiInterpreter::final_strokes[] =
{
    0, 2, 4, 4, 2, 5, 5, 3, 5, 7, 9, 9, 7, 9,
    9, 8, 4, 4, 6, 2, 4, 1, 3, 4, 3, 4, 4, 3
};

void AheuiInterpreter::initialize(AheuiCode *ah)
{
  code = ah;
  cursor.x = 0;
  cursor.y = 0;
  cursor.dx = 0;
  cursor.dy = 1;
  for(int i=0;i<27;++i)
    stack[i] = new AheuiStack();
  queue = new AheuiQueue;
  storage = stack[0];
  delete stack[21]; //ㅇ 스택은 없음
}

void AheuiInterpreter::step()
{
  tuple<int, int, int> broken = code->split_code(code->get_code(cursor.x, cursor.y));

  /* 홀소리 */
  switch(get<1>(broken))
  {
    case 0: cursor.dx = 1; cursor.dy = 0; break;      //ㅏ
    case 2: cursor.dx = 2; cursor.dy = 0; break;      //ㅑ
    case 4: cursor.dx = -1; cursor.dy = 0; break;     //ㅓ
    case 6: cursor.dx = -2; cursor.dy = 0; break;     //ㅕ
    case 8: cursor.dx = 0; cursor.dy = -1; break;     //ㅗ
    case 12: cursor.dx = 0; cursor.dy = -2; break;    //ㅛ
    case 13: cursor.dx = 0; cursor.dy = 1; break;     //ㅜ
    case 17: cursor.dx = 0; cursor.dy = 2; break;     //ㅠ
    case 18: cursor.dy *= -1; break;                  //ㅡ
    case 19: cursor.dx *= -1; cursor.dy *=-1; break;  //ㅢ
    case 20: cursor.dx *= -1; break;                  //ㅣ
    default: break;
  }
  if(storage->size() < required_elements[get<0>(broken)])
  {
    cursor.dx *= -1; cursor.dy *= -1;
  }
  /* 닿소리 */
  long long a,b;
  switch(get<0>(broken))
  {
    case 2: //ㄴ
      a = storage->pop();
      b = storage->pop();
      storage->push(b/a);
      break;
    case 3: //ㄷ
      a = storage->pop();
      b = storage->pop();
      storage->push(b+a);
      break;
    case 4: //ㄸ
      a = storage->pop();
      b = storage->pop();
      storage->push(b*a);
      break;
    case 5: //ㄹ
      a = storage->pop();
      b = storage->pop();
      storage->push(b%a);
      break;
    case 6: //ㅁ
      a = storage->pop();
      switch(get<2>(broken))
      {
	case 21: //ㅇ
	  wcout << a;
	  break;
	case 27: //ㅎ
	  wcout << static_cast<wchar_t>(a);
	  break;
	default:
	  break;
      }
      break;
    case 7: //ㅂ
      switch(get<2>(broken))
      {
	case 21: //ㅇ
	  long long input_num;
	  wcin >> input_num;
	  storage->push(a);
	  break;
	case 27: //ㅎ
	  wchar_t input_char;
	  wcin >> input_char;
	  storage->push(static_cast<long long>(input_char));
	  break;
	default:
	  storage->push(final_strokes[get<2>(broken)]);
	  break;
      }
      break;
    case 8: //ㅃ
      storage->dup();
      break;
    case 9: //ㅅ
      switch(get<2>(broken))
      {
	case 21: //ㅇ
	  storage = queue;
	  break;
	case 27: //ㅎ
	  //TODO: 확장기능 통로
	  wcout << L"현재 확장기능 통로는 구현되어있지 않습니다" << endl;
	  assert(false);
	  break;
	default:
	  storage = stack[get<2>(broken)];
	  break;
      }
      break;
    case 10: //ㅆ
    {
      long long item = storage->pop();
      AheuiStorage *target;
      switch(get<2>(broken))
      {
	case 21: //ㅇ
	  target = queue;
	  break;
	case 27: //ㅎ
	  //TODO: 확장기능 통로
	  wcout << L"현재 확장기능 통로는 구현되어있지 않습니다" << endl;
	  assert(false);
	  break;
	default:
	  target = stack[get<2>(broken)];
	  break;
      }
      target->push(item);
      break;
    }
    case 12: //ㅈ
      a = storage->pop();
      b = storage->pop();
      if(b<a) 
	storage->push(0);
      else 
	storage->push(1);
      break;
    case 14: //ㅊ
      a = storage->pop();
      if(a==0)
      {
	cursor.dx *= -1; cursor.dy *= -1;
      }
      break;
    case 16: //ㅌ
      a = storage->pop();
      b = storage->pop();
      storage->push(b-a);
      break;
    case 17: //ㅍ
      storage->swap();
      break;
    case 18: //ㅎ
      if(storage->size() == 0) exit(0);
      else exit(storage->pop());
      break;
    default:
      break;
  }
}

void AheuiInterpreter::move_cursor()
{
  cursor.x += cursor.dx;
  cursor.y += cursor.dy;
  if(cursor.x < 0) cursor.x = code->x_size() - 1;
  if(cursor.x >= code->x_size()) cursor.x = 0;
  if(cursor.y < 0) cursor.y = code->y_size() - 1;
  if(cursor.y >= code->y_size()) cursor.y = 0;
}

void AheuiInterpreter::show_code()
{
  code->show_code(cursor.x, cursor.y);
}

AheuiStorage* AheuiInterpreter::get_storage(int index)
{
  AheuiStorage *target;
  switch(index)
  {
    case 21:
      target = queue;
      break;
    case 27:
      wcout << L"현재 확장기능 통로는 구현되어있지 않습니다" << endl;
      target = nullptr;
      assert(false);
      break;
    default:
      target = stack[index];
      break;
  }
  return target;
}
