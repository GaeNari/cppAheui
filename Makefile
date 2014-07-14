CC = g++
OBJS = storage.o aheuicode.o interpreter.o debugger.o main.o
TARGET = main

.SUFFIXES : .cpp .o

all : $(TARGET)

CPPFLAGS = -std=c++11

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(TARGET) *.o
