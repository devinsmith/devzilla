# Makefile for nspr libc

.PHONY: all clean

SRCS = base64.c strcat.c strcpy.c strdup.c strcmp.c strccmp.c strlen.c
#SRCS = plerror.c plgetopt.c plvrsion.c \
#			 strchr.c strcpy.c strcstr.c \
#			 strpbrk.c strstr.c strtok.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDES = -I../include -I../../../pr/include
CFLAGS = -Wall -O2

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	# Shell can be sh.exe (cmd.exe) or /bin/sh (msys)
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
endif

LIB = libnsprc
STATIC_LIB = $(LIB).a

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

print-%  : ; @echo $* = $($*)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(STATIC_LIB)

# Include automatically generated dependency files
-include $(DEPS)
