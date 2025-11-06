CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iinclude
TARGET = build/linter

SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Cross-platform commands
MKDIR_P = mkdir -p
RM_F = rm -f
RM_RF = rm -rf

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM_RF) $(BUILD_DIR)
	$(RM_F) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild