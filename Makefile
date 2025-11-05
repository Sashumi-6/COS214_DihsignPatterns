# === Compiler and flags ===
CXX = clang++        # macOS uses clang by default
CXXFLAGS = -std=c++11 -Wall -I./src/headers

# === Directories ===
SRC_DIR = src/cpp
TEST_DIR = src/tests
OBJ_DIR = build
BIN_DIR = bin

# === Files ===
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

APP_MAIN = $(SRC_DIR)/main.cpp
TEST_MAIN = $(TEST_DIR)/testingmain.cpp

APP_TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/tests

# === Default rule ===
all: run

# ============================================================
# === Build and Run Normal Application (main.cpp) ============
# ============================================================
run: $(APP_TARGET)
	@echo "Running normal program..."
	@./$(APP_TARGET)

$(APP_TARGET): $(OBJS) $(APP_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(APP_MAIN) -o $(APP_TARGET)
	@echo "Build complete: $(APP_TARGET)"

# ============================================================
# === Build and Run Tests (testingmain.cpp with doctest) =====
# ============================================================
test: $(TEST_TARGET)
	@echo "Running doctest suite..."
	@./$(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_MAIN) -o $(TEST_TARGET)
	@echo "Build complete: $(TEST_TARGET)"

# ============================================================
# === Compile Object Files (shared by both builds) ============
# ============================================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $<"

# ============================================================
# === Memory Tools ===========================================
# ============================================================
leaks: test
	@echo "Checking for memory leaks (macOS 'leaks' tool)..."
	@leaks --atExit -- ./$(TEST_TARGET)

sanitize:
	@echo "Rebuilding with AddressSanitizer..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -fsanitize=address -g $(SRCS) $(TEST_MAIN) -o $(TEST_TARGET)_asan
	@echo "Built: $(TEST_TARGET)_asan"
	@echo "Running with AddressSanitizer..."
	@./$(TEST_TARGET)_asan

# ============================================================
# === Clean Build Files ======================================
# ============================================================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned build and bin directories."