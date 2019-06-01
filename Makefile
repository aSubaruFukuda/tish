PROGRAM = tish
OBJS	  = main.o commandline.o commandrunner.o controlcommand.o builtincommand.o varlib.o util.o
SRCS	  = $(OBJS:%.o=%.c)
CC		  = gcc
CFLAGS	= -g -Wall
LDFLAGS	=

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	rm $(OBJS)

clean:
	rm $(PROGRAM)

doc:
	doxygen

show_doc:
	doxygen
	google-chrome html/index.html

