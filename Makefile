CC := g++
WARN := -Wall -Wextra -Wpedantic
DEBUG := -g
INC := -Isrc -I/usr/include/opencv4 -I$(dir $(abspath $(lastword $(MAKEFILE_LIST)))) $(shell find src -type d -printf '-I%p ')
LIB := /usr/lib
LIBS := -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_imgcodecs -lopencv_videoio
BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/pfloop

SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(patsubst src/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(WARN) $(DEBUG) $(INC) -L$(LIB) $(LIBS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(WARN) $(DEBUG) $(INC) -L$(LIB) $(LIBS) -c $< -o $@

build: $(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

rebuild: 
	make clean
	make

.PHONY: clean
