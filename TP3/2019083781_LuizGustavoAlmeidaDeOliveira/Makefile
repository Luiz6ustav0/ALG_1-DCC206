CC = g++
CXXFLAGS = -std=c++14 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# all sources, objs, and header files
MAIN = main.cpp
TEST = test.cpp
TARGET = tp3
TARGET_TEST = test.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	@$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

test: $(OBJ)
	@$(CC) $(CXXFLAGS) -I$(INCLUDE_FOLDER) -o $(BIN_FOLDER)$(TARGET_TEST) $(OBJ) ./tests/test.cpp
	@clear
	@./bin/test.out
	@make clean

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)* ${TEST_DIR}/*.out ${TEST_DIR}/*.o