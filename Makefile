CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc

TARGET = my_program

SRC_DIR = src

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/lexer.cpp $(SRC_DIR)/parser.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	@echo "Builded. Executable file: $(TARGET)"

$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleanup..."
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
	@echo "Rebuild process started"

.PHONY: all clean rebuild