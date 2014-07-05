SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp = .o)
CC = g++
INCLUDES = 
LIBS =  
CCFLAGS = -g -std=c++0x
my_app : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS) $(CCFLAGS)

%.o : %.cpp
	$(CC) -c  $(CCFLAGS) $<
clean:
	rm *.o
.PHONY:clean
