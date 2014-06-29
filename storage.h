#pragma once

class AheuiStorage : public list<long long>
{
public:
  virtual void push(long long value) = 0;
  virtual long long pop() = 0;
  virtual void dup() = 0;
  virtual void swap() = 0;
};

class AheuiQueue : public AheuiStorage
{
public:
  void push(long long value);
  long long pop();
  void dup();
  void swap();
};

class AheuiStack : public AheuiStorage
{
public:
  void push(long long value);
  long long pop();
  void dup();
  void swap();
};
