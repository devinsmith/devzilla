# Makefile for libreg

.PHONY: all clean

C_SRCS = reg.c VerReg.c vr_stubs.c

OBJS = $(C_SRCS:.c=.o)
DEPS = $(C_SRCS:.c=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../include -I../../../include \
					 -I../../../js/src -I../../../nsprpub/lib/ds -I../../libutil/public \
					 -I../../../lib/liblayer/include
CFLAGS = -Wall -O2 -DJS_THREADSAFE -DSTANDALONE_IMAGE_LIB

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	CFLAGS += -DXP_WIN -DXP_PC
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
else
	CFLAGS += -fPIC -DXP_UNIX
endif


LIB = libmozreg
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a
LDFLAGS =

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
