# Makefile for libxpcom

.PHONY: all clean

C_SRCS = plvector.c
CPP_SRCS = nsDebug.cpp nsHashtable.cpp nsID.cpp nsCOMPtr.cpp nsProxyEvent.cpp \
			nsComponentManager.cpp nsRepository.cpp nsServiceManager.cpp \
			nsSupportsArray.cpp nsSupportsArrayEnumerator.cpp \
			nsConjoiningEnumerator.cpp nsTraceRefcnt.cpp nsRegistry.cpp \
			nsXPComFactory.cpp nsEventQueueService.cpp nsAllocator.cpp xcDll.cpp \
			xcDllStore.cpp nsGenericFactory.cpp

CXX? = g++
AR? = ar
RM = rm -f

DEFINES =

LIB = libxpcom
STATIC_LIB = $(LIB).a
SHARED_LIB = $(LIB).so
CFLAGS = -Wall -g3

ifeq ($(OS),Windows_NT)
	CC = gcc
	DEFINES += -D_IMPL_NS_COM -DWIN32_LEAN_AND_MEAN
	SHARED_LIB = xpcom.dll
	LD_FLAGS += -L../../nsprpub/pr/src -L../../nsprpub/lib/libc/src \
		-L../../nsprpub/lib/ds -L../../modules/libreg/src \
		-Wl,--out-implib,$(LIB).a \
		-lmozreg -lnsprc -lplds -lnspr -lwsock32 -lwinmm
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
else
	CFLAGS += -fPIC
endif

OBJS = $(CPP_SRCS:.cpp=.o) $(C_SRCS:.c=.o)
DEPS = $(CPP_SRCS:.cpp=.d) $(C_SRCS:.c=.d)

INCLUDES = -I../public -I../../nsprpub/pr/include \
					 -I../../nsprpub/lib/libc/include -I../../include \
					 -I../../nsprpub/lib/ds -I../../modules/libreg/include

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LD_FLAGS)

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
