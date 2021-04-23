# modify these 3 lines depending of what you want
CFLAGS 		:= -Wno-unused-command-line-argument# -Werror -Wall -Wextra
LDFLAGS		:=
LIBS 		:= -lpthread -lGL -lGLEW -lSDL2main -lSDL2 -lSDL2_image
# type of source files
# c or cpp (make sure to not have space after)
SRCEXT 		?= cpp
CVERSION	?= 11
CPPVERSION	?= 14

# detect if compiler is gcc instead of clang. Not viewing for other compiler
# C
ifeq ($(SRCEXT), c)
	ifeq ($(CC), gcc)
		CC := gcc
	else
		CC := clang
	endif # C : clang or gcc
	CFLAGS += -std=c$(CVERSION)
# C++
else
	ifeq ($(CXX), g++)
		CC := g++
	else
		CC := clang++
	endif # C++ : clang++ or g++
	CFLAGS += -std=c++$(CPPVERSION)
endif

# executable name
ifdef PGNAME
	EXECUTABLE = $(PGNAME)
else
	EXECUTABLE 	:= program
endif # pgname

# program name location
OUT 		?= ./bin

# compilation mode
ifdef DEBUG
	TARGETDIR = $(OUT)/debug
else
	TARGETDIR = $(OUT)/release
endif # debug

# final full executable location
TARGET 		:= $(TARGETDIR)/$(EXECUTABLE)
# .o location
BUILDDIR 	?= ./build
# source files location
SRCDIR 		?= ./src
# header files location
INCDIR 		?= ./include

SOURCES 	:= $(shell find $(SRCDIR)/** -type f -name *.$(SRCEXT))

INCDIRS		:=
INCLIST		:=
BUILDLIST	:=
INC			:=

ifneq (, $(firstword $(wildcard $(INCDIR)/*)))
	INCDIRS 	:= $(shell find $(INCDIR)/** -name '*.h' -exec dirname {} \; | sort | uniq)
	INCLIST 	:= $(patsubst $(INCDIR)/%, -I $(INCDIR)/%, $(INCDIRS))
	BUILDLIST 	:= $(patsubst $(INCDIR)/%, $(BUILDDIR)/%, $(INCDIRS))
	INC 		:= $(INCLIST)
endif # incdir

ifneq ($(SRCDIR), $(INCDIR))
	INC += -I $(INCDIR)
endif


ifdef DEBUG
OBJECTS 	:= $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"
	$(CC) -g -o $(TARGET) $^ $(LIBS) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
ifdef BUILDLIST
	@mkdir -p $(BUILDLIST)
endif
	@echo "Compiling $<...";
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

else # RELEASE

$(TARGET):
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	$(CC) $(INC) -o $(TARGET) $(SOURCES) $(LIBS) $(LDFLAGS)

endif #debug / release targets


clean:
	rm -f -r $(BUILDDIR)/**
	@echo "All objects removed"

clear: clean
	rm -f -r  $(OUT)/**
	@echo "$(OUT) folder cleared"

.PHONY: clean clear