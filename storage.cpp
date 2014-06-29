#include "commonheader.h"
#include "storage.h"

void AheuiQueue::push(long long value)
{
  this->push_back(value);
}

long long AheuiQueue::pop()
{
  long long ret = this->front();
  this->pop_front();
  return ret;
}

void AheuiQueue::dup()
{
  this->push_front(this->front());
}

void AheuiQueue::swap()
{
  long long a = this->front();
  this->pop_front();
  long long b = this->front();
  this->pop_front();
  this->push_front(a);
  this->push_front(b);
}

void AheuiStack::push(long long value)
{
  this->push_front(value);
}

long long AheuiStack::pop()
{
  long long ret = this->front();
  this->pop_front();
  return ret;
}

void AheuiStack::dup()
{
  this->push_front(this->front());
}

void AheuiStack::swap()
{
  long long a = this->front();
  this->pop_front();
  long long b = this->front();
  this->pop_front();
  this->push_front(a);
  this->push_front(b);
}
