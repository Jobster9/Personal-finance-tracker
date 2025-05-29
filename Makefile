# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = finance.exe
SRCDIR = .
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files in obj directory
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir $(OBJDIR)

# Clean up build files
clean:
	rmdir /S /Q $(OBJDIR) 2>nul || true
	del /Q $(TARGET) 2>nul || true

# Clean and rebuild
rebuild: clean all

# Install/copy to a bin directory (optional)
install: $(TARGET)
	copy $(TARGET) C:\bin\ 2>nul || echo "Install directory not found"

# Show help
help:
	@echo Available targets:
	@echo   all      - Build the program
	@echo   clean    - Remove build files
	@echo   rebuild  - Clean and build
	@echo   install  - Copy to bin directory
	@echo   help     - Show this help

.PHONY: all clean rebuild install help