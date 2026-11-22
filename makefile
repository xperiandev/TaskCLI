CXX ?= g++
CXXFLAGS = -Wall -O2

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    TARGET = task-cli.exe
else
    RM = rm -f
    TARGET = task-cli
endif

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	-$(RM) $(TARGET)

.PHONY: all clean   