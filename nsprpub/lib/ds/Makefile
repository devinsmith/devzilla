# Makefile for nspr libplds

.PHONY: all clean

SRCS = plarena.c plevent.c plhash.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDES = -I../../pr/include
CFLAGS = -Wall -O2

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
endif


LIB = libplds
STATIC_LIB = $(LIB).a

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(STATIC_LIB)

# Include automatically generated dependency files
-include $(DEPS)
