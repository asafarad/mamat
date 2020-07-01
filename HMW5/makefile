CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
CXXLINK = $(CXX)
LIBS =
OBJS = compfunc.o func.o main.o polynom.o
RM=rm -f
TARGET = WolfraMamat

$(TARGET): $(OBJS) 
	$(CXXLINK) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

compfunc.o: compfunc.cpp compfunc.h func.h
func.o: func.cpp func.h
main.o: main.cpp func.h polynom.h compfunc.h
polynom.o: polynom.cpp polynom.h func.h

clean:
	 $(RM) WolfraMamat *.o *.bak *~ "#"* core



