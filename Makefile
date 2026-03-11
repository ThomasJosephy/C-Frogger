# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -MMD -MP

# Directories
SRC_DIR = ./src
BUILD_DIR = ./obj

# Sources
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

# Output binary
TARGET = frogger.exe

# Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ -lfltk

-include $(DEPENDS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc Makefile
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET)# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -MMD -MP

# Directories
SRC_DIR = ./src
BUILD_DIR = ./obj

# Sources
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

# Output binary
TARGET = frogger.exe

# Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ -lfltk

-include $(DEPENDS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc Makefile
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(TARGET)" del /Q "$(TARGET)"
