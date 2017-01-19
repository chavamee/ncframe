CC        := clang++
LD    	  := clang++

BUILD_DIR := ../../build
BIN_DIR    = $(BUILD_DIR)/bin
LIB_DIR   := $(BUILD_DIR)/lib
OBJS_DIR  := $(BUILD_DIR)/objs
INC_DIR    = ../../inc

TARGET    := $(BIN_DIR)/feedlr
CFLAGS    := -std=c++14 -Wall -Wextra -pg -g -O0
LIBS      := -lncurses++w -lncursesw -lmenu -lpanel -lform -lcurl -ljsoncpp -lncframe

INCLUDES  := -I$(INC_DIR) -I../inc
LDFLAGS   := -L$(LIB_DIR)

SOURCES   := $(wildcard *.cpp)
OBJECTS   := $(SOURCES:%.cpp=$(OBJS_DIR)/%.o)

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
