# Makefile for Weather API Demo
# This file simplifies the compilation process

# Compiler
CXX = g++

# Compiler flags
# -std=c++11: Use C++11 standard
# -Wall: Enable all warnings
# -o: Specify output file name
CXXFLAGS = -std=c++11 -Wall

# Linker flags
# -lcurl: Link against the curl library for HTTP requests
LDFLAGS = -lcurl

# Target executable name
TARGET = weather_api

# Source files
SOURCES = weather_api.cpp

# Default target - builds the program
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Clean up compiled files
clean:
	rm -f $(TARGET)
	@echo "Clean complete!"

# Help target - shows available commands
help:
	@echo "Available targets:"
	@echo "  make        - Build the weather API program"
	@echo "  make clean  - Remove compiled files"
	@echo "  make help   - Show this help message"
