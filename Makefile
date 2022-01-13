TARGET 		?= aot

BUILD_DIR 	?= ./.objs
SRC_DIR   	?= ./

# Use all c++ source files.
SRCS		:= $(wildcard *.cpp)
OBJS		:= $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

INC_DIRS	:= $(shell find $(SRCS_DIRS) -type d)
INC_FLAGS	:= $(addprefix -I,$(INC_DIRS))

# Pre Processor Flags
CPPFLAGS	?= $(INC_FLAGS) -MMD -MP

# Warning Flags
WFLAGS		:= -g -Wall -Wextra 

#
STDFLAGS	:= -std=c++17

# Setup Linker Flags
LDFLAGS		:= -lSDL2 -lGL -lGLEW -ldl -lm -lstdc++

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) $(WFLAGS) -$(STDFLAGS) -o $@ $(LDFLAGS)
	cp $(TARGET) ./RunTime/$(TARGET)
	
# C++ Source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<



.PHONY: clean

clean:
	$(RM) -r $(TARGET)
	$(RM) .objs/*

-include $(DEPS)

MKDIR_P ?= mkdir -p
