CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS = main.o party.o voter.o
RM = rm -f

# Creating the executable (Elect_MMT)
Elect_MMT: $(OBJS)
	$(CCLINK) -o Elect_MMT $(OBJS) $(LIBS)
# Creating object files using the independences
main.o: main.c party.h voter.h
party.o: party.c party.h voter.h
voter.o: voter.c voter.h party.h
#Cleaning old files before new make
clean: 
	$(RM) Elect_MMT *.o *.bak *~ "#"*
