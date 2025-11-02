CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iinclude
TARGET = my_program

# Директории
SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Создаем папку build если её нет
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^  # Оставляем $^, но меняем рабочий каталог

# Правило компиляции
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild