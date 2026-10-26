# ChronoVault — Beginner-Friendly Website OOP Project

ChronoVault is a small website for a fictional time-travel mission centre. The website uses a dark navy and cyan theme. HTML/CSS/JavaScript render the interface, while a C++17 backend performs validation, stores missions in memory, reserves energy, and launches missions.

## Features
- Dashboard with mission count, energy reserve, explorer count and completed missions.
- Mission Control form with validation and launch actions.
- Explorer Registry showing Historian, Engineer and Guardian.
- Mission History table.
- Error messages for invalid energy, insufficient reserve and repeated launches.

## OOP concepts demonstrated
- **Encapsulation:** Mission data is private and accessed through methods.
- **Constructors/destructors:** Mission and ChronoVault initialise and clean up their state.
- **Composition:** ChronoVault owns its explorer objects and mission collection.
- **Dynamic memory management:** `std::unique_ptr<Explorer>` manages polymorphic explorer objects automatically.
- **Inheritance:** Historian, Engineer and Guardian inherit from Explorer.
- **Runtime polymorphism:** the virtual `action()` method runs the selected explorer's behaviour.
- **Operator overloading:** `Mission::operator==` compares missions by ID.

## Requirements
- C++17 compiler (GCC/MinGW recommended on Windows)
- CMake 3.16+

## Build and run (Windows)
1. Install **CMake** and **MSYS2 MinGW-w64 GCC** if not already installed.
2. Open **MSYS2 UCRT64** terminal in this project folder.
3. Run:
   ```bash
   cmake -S . -B build
   cmake --build build
   ./build/ChronoVault public
   ```
4. Open `http://localhost:8099` in a browser.

On Windows PowerShell, if CMake and MinGW are already on PATH, run the same commands with `cmake` and launch `build\ChronoVault.exe public`.

## API
- `GET /api/dashboard` — dashboard counts and recent missions
- `GET /api/missions` — mission list
- `GET /api/explorers` — explorer registry
- `POST /api/missions` — create a mission; JSON keys: `name`, `timeline`, `explorerType`, `energy`
- `POST /api/missions/{id}/launch` — launch a planned mission

Data is intentionally stored in memory and resets when the server stops. This keeps the project understandable and avoids database setup.

## Test checklist
1. Open the dashboard; initial energy should be 500 CU and mission count 0.
2. Create a mission with 50 CU; mission count becomes 1 and energy becomes 450 CU.
3. Launch the mission; status becomes Completed and its result displays the explorer action.
4. Try energy 10 or 250; the backend should reject it.
5. Try a mission requiring more energy than remains; the backend should reject it.
6. Refresh the page; in-memory data should remain while the server runs.
7. Stop and restart the server; data should reset.

## Folder guide
- `include/ChronoVault.h` — OOP class declarations
- `src/ChronoVault.cpp` — mission rules and OOP implementation
- `src/main.cpp` — small HTTP API server
- `public/index.html` — website structure
- `public/css/style.css` — dark navy/cyan visual theme
- `public/js/app.js` — navigation and API calls
- `third_party/` — header-only HTTP and JSON libraries

## Report and screenshots
- `ChronoVault-Project-Report.docx` contains the project explanation, embedded website screenshots, file-structure diagram, and source-code appendices for the project-owned files.
- `docs/screenshots/` contains the screenshot image files used in the report.
- `docs/file-structure-diagram.png` is the folder map included in Appendix A.
