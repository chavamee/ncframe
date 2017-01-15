CC        := clang++
LD    	  := clang++

BUILD_DIR := ../../build
#BIN_DIR    = $(BUILD_DIR)/bin
LIB_DIR   := $(BUILD_DIR)/lib
OBJS_DIR  := $(BUILD_DIR)/objs
INC_DIR    = ../../inc

TARGET    := $(LIB_DIR)/libfeedly.a
CFLAGS    := -std=c++14 -Wall -Wextra -pg -g -c -O0
LIBS      := -lncurses++w -lncursesw -lmenu -lpanel -lform -lcurl -ljsoncpp

INCLUDES  := -I$(INC_DIR)
LDFLAGS    := -L$(BUILD_DIR)

SOURCES   := $(wildcard *.cpp)
OBJECTS   := $(SOURCES:%.cpp=$(OBJS_DIR)/%.o)

.PHONEY: clean

all: $(TARGET)

dev: CFLAGS+=-g
dev: all

$(TARGET): $(OBJECTS)
	ar -cvq $@ $^

$(OBJECTS): $(OBJS_DIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
