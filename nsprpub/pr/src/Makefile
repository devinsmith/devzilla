# Makefile for nspr 

.PHONY: all clean

SRCS = io/prio.c io/priometh.c io/prlog.c io/prfdcach.c \
			 io/prlayer.c io/prmapopt.c io/prscanf.c io/prmwait.c \
			 io/prprf.c io/prdir.c \
			 malloc/prmalloc.c malloc/prmem.c linking/prlink.c \
			 misc/prerror.c misc/prinit.c pthreads/ptsynch.c memory/prseg.c \
			 md/prosdep.c misc/pratom.c \
			 misc/prinrval.c pthreads/ptthread.c \
			 misc/prenv.c \
			 pthreads/ptio.c \
			 threads/prtpd.c pthreads/ptmisc.c threads/prcmon.c \
			 misc/prnetdb.c misc/prsystem.c \
			 misc/prlog2.c

CC? = gcc
AR? = ar
RM = rm -f
FixPath = $1

DEFINES =

LIB = libnspr
STATIC_LIB = $(LIB).a
SHARED_LIB = $(LIB).so

ifeq ($(OS),Windows_NT)
	CC = gcc
	SRCS += md/windows/ntthread.c threads/prcthr.c threads/combined/prucv.c \
		threads/combined/prulock.c threads/prmon.c md/windows/ntmisc.c \
		md/windows/ntio.c md/windows/win32_errors.c threads/combined/pruthr.c \
		md/windows/ntinrval.c threads/combined/prucpu.c \
		threads/combined/prustack.c md/windows/w32poll.c io/prfile.c \
		io/prsocket.c
	SHARED_LIB = $(LIB).dll
	LDFLAGS += -lwsock32 -lwinmm -Wl,--out-implib,$(LIB).a
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
		FixPath = $(subst /,\,$1)
	endif
else
	DEFINES += -D_PR_PTHREADS -DLINUX -Dlinux -DXP_UNIX -DPR_LOGGING
	SRCS += md/unix/unix.c md/unix/unix_errors.c md/unix/uxproces.c \
					md/unix/uxpoll.c md/unix/linux.c
endif

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDES = -I../include -I../include/private -I../include/md
CFLAGS = -Wall -g3


all: $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS) $(LDFLAGS)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(call FixPath,$(OBJS))
	$(RM) $(call FixPath,$(DEPS))
	$(RM) $(STATIC_LIB)

# Include automatically generated dependency files
-include $(DEPS)
