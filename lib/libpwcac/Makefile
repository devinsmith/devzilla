# Makefile for libpwcac

.PHONY: all clean

C_SRCS = pwcacapi.c

OBJS = $(C_SRCS:.c=.o) $(SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(SRCS:.cpp=.d)

INCLUDES = -I../../include -I../../nsprpub/pr/include \
					 -I../../modules/security/freenav \
					 -I../../modules/libutil/public \
					 -I../../modules/libimg/public \
					 -I../liblayer/include
CFLAGS = -Wall -O2

CC? = gcc
AR? = ar
RM = rm -f

LIB = libpwcac
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	DEFINES += -D_IMPL_NS_BASE -DWIN32_LEAN_AND_MEAN
	LDFLAGS += -Wl,--out-implib,$(LIB).a -lwsock32 -lwinmm
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
else
	CFLAGS += -fPIC
endif


all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)
	cp $(SHARED_LIB) ../../xpfe/bootstrap

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
