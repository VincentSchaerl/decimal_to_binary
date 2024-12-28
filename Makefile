CXX = g++
CXX_LINUX_32 = g++ -m32
CXX_LINUX_64 = g++ -m64
CXX_WINDOWS_32 = i686-w64-mingw32-g++
CXX_WINDOWS_64 = x86_64-w64-mingw32-g++
CXXFLAGS = -I$(INCLUDE_DIR) -MMD -MP
CXXFLAGS_RELEASE = -I$(INCLUDE_DIR) -static

INCLUDE_DIR = inc
OBJ_DIR = out/obj
RELEASE_DIR = out/release

SRC = src/main.cpp src/decimal_to_binary.cpp src/evaluate_input.cpp
OBJ = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DEPS = $(OBJ:.o=.d)

PROGRAM_NAME = decimal_to_binary
TARGET = out/$(PROGRAM_NAME)
LINUX_32 = $(RELEASE_DIR)/$(PROGRAM_NAME)_linux_32_bit
LINUX_64 = $(RELEASE_DIR)/$(PROGRAM_NAME)_linux_64_bit
WINDOWS_32 = $(RELEASE_DIR)/$(PROGRAM_NAME)_windows_32_bit.exe
WINDOWS_64 = $(RELEASE_DIR)/$(PROGRAM_NAME)_windows_64_bit.exe

####################################################################################################

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(CXX) $^ -o $@

-include $(DEPS)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

####################################################################################################

release:
	mkdir -p $(RELEASE_DIR)
	$(CXX_LINUX_32) $(SRC) -o $(LINUX_32) $(CXXFLAGS_RELEASE)
	$(CXX_LINUX_64) $(SRC) -o $(LINUX_64) $(CXXFLAGS_RELEASE)
	$(CXX_WINDOWS_32) $(SRC) -o $(WINDOWS_32) $(CXXFLAGS_RELEASE)
	$(CXX_WINDOWS_64) $(SRC) -o $(WINDOWS_64) $(CXXFLAGS_RELEASE)

####################################################################################################

all: $(TARGET) release

run: $(TARGET)
	$(TARGET)

####################################################################################################

clean:
	rm -rf out/*