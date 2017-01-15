CC        := clang++
LD    	  := clang++

BUILD_DIR := ../build
BIN_DIR    = $(BUILD_DIR)/bin
LIB_DIR   := $(BUILD_DIR)/lib
OBJS_DIR  := $(BUILD_DIR)/objs
INC_DIR    = ../inc

TARGET    := $(BIN_DIR)/FeedlyTests
CFLAGS    := -std=c++11 -g -Wall -Wextra -O0
LIBS      := -lcurl -ljsoncpp -lgtest

INCLUDES  := -I$(INC_DIR)
LDLAGS    := -L$(LIB_DIR)

SOURCES   := $(wildcard *.cpp)
OBJECTS   := $(SOURCES:%.cpp=$(OBJS_DIR)/%.o)
STATIC_LIBS := $(wildcard $(LIB_DIR)/*.a)

.PHONEY: clean

all: $(TARGET)

dev: CFLAGS+=-g
dev: all

$(TARGET): $(OBJECTS)
	$(LD) $^ $(LIBS) $(STATIC_LIBS) -o $@

$(OBJECTS): $(OBJS_DIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
