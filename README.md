# Personal-finance-tracker

A C++ personal finance management application with google test v1.15.2

## Requirements

- C++ Compiler: GCC 7+ or MSVC 2017+
- CMake: Version 3.14 or higher
- Git

## Initial Setup

After cloning project input following cmake commands to configure the project.

```bash
mkdir build #create build folder
cd build #route into folder
cmake ..  # Autodetect your c++ compiler, specify if necessary

```

## Build Commands

### Build everything (main application + tests)

`cmake --build .`

### Build specific targets

```bash
cmake --build . --target finance # Main application only`
cmake --build . --target tests # Tests only
```

## Running the application

```bash
# Run main application
./finance.exe    # Windows
./finance        # Linux/Mac

# Run all tests
./tests.exe      # Windows
./tests          # Linux/Mac

# Run specific test types only

./tests.exe --gtest_filter="*Unit*" # Run only unit tests
./tests.exe --gtest_filter="*Integration*" # Run only integration tests
./tests.exe --gtest_filter="Account*" # Example: Run only Account tests
```

## Development

```bash
# Make changes, then build and test
cmake --build . && ./tests.exe

# Clean rebuild if needed
cd .. && rm -rf build && mkdir build && cd build
cmake .. -G "MinGW Makefiles" && cmake --build .
```
