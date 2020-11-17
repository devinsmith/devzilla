# Makefile for widget library.
#
.PHONY: build clean

# Xlib
XLIB_SRCS = xlib/nsAppShell.cpp xlib/nsComboBox.cpp xlib/nsLabel.cpp \
						xlib/nsMenuBar.cpp xlib/nsPopUpMenu.cpp xlib/nsTabWidget.cpp \
						xlib/nsTextWidget.cpp xlib/nsWidget.cpp xlib/nsButton.cpp \
						xlib/nsDialog.cpp xlib/nsListBox.cpp xlib/nsMenu.cpp \
						xlib/nsRadioButton.cpp xlib/nsTextAreaWidget.cpp \
						xlib/nsToolkit.cpp xlib/nsWidgetFactory.cpp xlib/nsCheckButton.cpp \
						xlib/nsFileWidget.cpp xlib/nsLookAndFeel.cpp xlib/nsMenuItem.cpp \
						xlib/nsScrollBar.cpp xlib/nsTextHelper.cpp \
						xlib/nsTooltipWidget.cpp xlib/nsWindow.cpp

# Motif
MOTIF_C_SRCS = motif/nsXtManageWidget.c
MOTIF_SRCS = motif/Motifdlldeps.cpp motif/nsMotifWidgetFactory.cpp \
			 motif/nsAppShell.cpp motif/nsToolkit.cpp motif/nsWindow.cpp \
			 motif/nsXtEventHandler.cpp motif/nsMenu.cpp motif/nsMenuBar.cpp \
			 motif/nsMenuItem.cpp

# Windows
WIN_SRCS = win/nsAppShell.cpp win/nsObject.cpp win/nsToolkit.cpp \
		win/nsWinWidgetFactory.cpp win/nsWindow.cpp

# Common
COMMON_SRCS = xpwidgets/nsBaseWidget.cpp

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I../../base/src \
					 -I../../base/public \
					 -I../../gfx/public -I../../nsprpub/lib/ds -Ixpwidgets

CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f
FixPath = $1

LIB = raptorwidget
SHARED_LIB = libraptorwidget.so

LDFLAGS = -L../../base/src -lraptorbase

ifeq ($(OS),Windows_NT)
	CPP_SRCS = $(WIN_SRCS) $(COMMON_SRCS)
	SHARED_LIB = $(LIB).dll
	CFLAGS += -D_IMPL_NS_WIDGET -DXP_PC
	INCLUDES += -I../../gfx/src/win32
	LDFLAGS += -L../../xpcom/src -lxpcom \
						 -lgdi32 -L../../gfx/src -lraptorgfx \
						 -Wl,--out-implib,lib$(LIB).a -lgdi32 -lcomctl32
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
		FixPath = $(subst /,\,$1)
	endif
else
#	C_SRCS = $(MOTIF_C_SRCS)
#	CPP_SRCS = $(MOTIF_SRCS) $(COMMON_SRCS)
	CPP_SRCS = $(XLIB_SRCS) $(COMMON_SRCS)
	CFLAGS += -fPIC
#	LDFLAGS += -lXt -lX11
	LDFLAGS += -lX11
endif

OBJS = $(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(CPP_SRCS:.cpp=.d)

all: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(call FixPath,$(OBJS))
	$(RM) $(call FixPath,$(DEPS))
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)

