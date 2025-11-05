# COS214_DihsignPatterns

Short nursery/shop simulation implemented in C++ for COS214 (Design Patterns). The project demonstrates several object-oriented and design-pattern concepts (see the UML diagrams in `UML_Diagrams/`) and provides a small TUI-based simulator.

## Contents
- Source: `src/cpp/` (implementation .cpp files)
- Headers: `src/headers/` (public headers)
- Object files: `build/` (compiled `*.o` files)
- Binaries: `bin/` (built executables)
- UML diagrams: `UML_Diagrams/` (design diagrams used in the course)

## Quick summary
The Makefile builds object files under `build/` and places executables in `bin/`.
- `bin/app` — the interactive TUI application (main program)
- `bin/tests` — test executable (uses the provided doctest header)

There are no external data files required by the current implementation — plant data is compiled in (`src/cpp/plantDatabase.cpp` uses a static map). If you add external data files later, place them under a `data/` directory at the repository root (or update the code to point to a different path).

## Prerequisites
- A C++ toolchain (the Makefile defaults to `clang++`, but `g++` also works) with support for C++11
- make (GNU make)

## Build & run
The Makefile's default target runs the app. From the repository root:

```bash
make
```

This will build and run `bin/app` (because `all: run`). If you prefer to only build the executable without running it, invoke the target directly:

```bash
make bin/app
# or build tests only
make bin/tests
```

You can also use the provided helper targets:

```bash
make run    # builds (if needed) and runs bin/app which runs the simulation
make test   # builds (if needed) and runs bin/tests which runs the doc test
```

Override the compiler or flags by setting environment variables when calling make. Examples:

```bash
# use g++ instead of the default clang++
CXX=g++ make

# change/add flags (e.g. enable debug symbols)
CXXFLAGS='-std=c++11 -g -Wall -I./src/headers' make
```

## Memory and sanitizers
The Makefile includes helpers for leak checking and AddressSanitizer (macOS/tooling dependent):

```bash
make leaks      # runs tests and then macOS 'leaks' tool (if available)
make sanitize   # rebuilds tests with ASan and runs them
```

## Run (manual)
After building you can run the app directly:

```bash
./bin/app
```

Run tests directly:

```bash
./bin/tests
```

## Clean
To remove build artifacts:

```bash
make clean
```

## Project layout / important files
- `src/cpp/main.cpp` — program entry; constructs `TUI` and starts the console. The main executable is `bin/app`.
- `src/cpp/tui.cpp`, `src/headers/tui.h` — text-based user interface logic.
- `src/cpp/plantDatabase.cpp`, `src/headers/plantDatabase.h` — plant data (currently embedded in code, no external data files needed).
- `Makefile` — primary build orchestration. Defaults: `CXX=clang++`, `CXXFLAGS='-std=c++11 -Wall -I./src/headers'`.

## Notes & next steps
- Currently plant data is embedded in code. If you'd like to load plants from a file, add a `data/` folder and update `PlantDatabase` to parse your format (CSV/JSON/text).
- Suggested small improvements: add a sample data file in `data/`, add CI to build & run tests, and add a brief CONTRIBUTING.md.

## Bugfixes
### In `plant.h`

#### Line 24, 32 & 40:
- Change the `kLossAmount` by adding a 0 in front of the decimal to make it 0.01, 0.025 & 0.035 respectively

#### Line 60:
- Chnage the `kWaterDose` to 0.035

### In `plant.cpp`

#### Line 6 (in the constructor):
- Change the init of `waterLevel` from 1 to 0


## Credits
See `LICENSE.txt` in the project root for licensing information.

This project uses the following GitHub Actions:
[actions/cpp-linter](https://github.com/cpp-linter)

#### Contributors
- Daniel Cohen, u24772756