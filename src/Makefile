CC        := clang++
LD    	  := clang++

MODULES   := ncurses

BUILD_DIR := ../build
BIN_DIR    = $(BUILD_DIR)/bin
LIB_DIR   := $(BUILD_DIR)/lib
OBJS_DIR  := $(BUILD_DIR)/objs
INC_DIR    = ../inc

TARGET    := $(LIB_DIR)/libncframe.so
CFLAGS    := -std=c++14 -Wall -Wextra -pg -O0 -fPIC -Weffc++
LIBS      := -lncurses++w -lncursesw -lmenu -lpanel -lform -lcurl -ljsoncpp

INCLUDES  := -I$(INC_DIR)
LDFLAGS   := -L$(BUILD_DIR) -shared

SOURCES   := $(foreach sdir,$(MODULES),$(wildcard $(sdir)/*.cpp))
OBJECTS   := $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SOURCES))


.PHONEY: clean

all: $(TARGET)

dev: CFLAGS+=-g
dev: all

$(TARGET): $(OBJECTS)
	$(LD) $^ $(LDFLAGS) $(LIBS) -o $@

$(OBJECTS): $(OBJS_DIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
