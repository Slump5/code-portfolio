# VPS Mirror Automation

## Overview
This is a C# application simulating a Virtual Private Server (VPS) mirror system. It implements a main server running multiple threads that generate events and share data in a critical section. A mirror server keeps up with these events via TCP communication, processes incoming data, and maintains synchronization. An automation script (via timer) handles periodic backups of shared data with a simple retention policy (timestamped files). The project includes a PowerPoint presentation on implementation methodologies, a video demonstration of the program running, and a presentation video. It fulfills the requirements for a replacement exam project in systems software, including multi-threading, synchronization, network communication, and automation. Documentation includes the project instructions PDF and source code.

## Features
- **Multi-Threaded Main Server:** Runs at least 4 threads that generate simulated events and add them to shared data.
- **Shared Critical Section:** Uses locking to synchronize access to shared data across threads.
- **Mirror Synchronization:** Mirror server receives and processes events from the main server in real-time via TCP, keeping up with changes.
- **Backup Automation:** Timer-based script triggers backups every 10 minutes, saving shared data to timestamped files (implementing a basic retention policy via file naming).
- **Network Communication:** TCP listener on the mirror server handles incoming connections and data from the main server.
- **Event Generation:** Simulates data events with timestamps for realism.
- **Console Logging:** Outputs processing status, received data, and backup completion for monitoring.
- **Presentation and Demo:** Includes a PowerPoint with code breakdowns, a video showing the program in action (demonstrating synchronization between servers), and a presentation video explaining methodologies.
- **Error Handling:** Basic exception handling during backups and network operations.

## File Structure
- **main-server.cs:** The main C# source code implementing the server, threads, mirror logic, TCP communication, and backup timer.
- **vps-mirror-automation-thomashoerger.pptx:** PowerPoint presentation (15-20 minutes worth) on project implementation methodologies and approach, including code screenshots and explanations.
- **instructions.pdf:** Project requirements document outlining features, scoring, and submission guidelines.
- **vps-mirror-automation-presentation-thomashoerger.mkv:** Video recording of the PowerPoint presentation explaining the project.
- **program-running-in-vps-server.mkv:** Short video demonstrating the program in action, showing main server threads generating events, mirror synchronization, and backup triggering.


## Requirements
- .NET SDK 8.0 or later (or .NET Framework for older compatibility)
- Standard .NET libraries (System, System.Net, System.IO, System.Threading, etc.)
- A C# compiler (via dotnet CLI or Visual Studio)
- Input configuration: Update `mirrorServerAddress` and `mirrorServerPort` in main-server.cs to match your setup (e.g., localhost for testing).
- Video playback: Any media player supporting .mkv (VLC).
- Optional: PowerPoint viewer for .pptx; PDF reader for instructions.pdf.

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program:
	- Using dotnet CLI (cross-platform):
		```bash
		dotnet new console -o VPSMirror
		# Copy main-server.cs into VPSMirror directory and replace Program.cs if needed
		cd VPSMirror
		dotnet build```
	- Using Visual Studio: Open main-server.cs as a new console app project, build the solution.
3. Run the executable:
	- dotnet CLI:
		```bash
		dotnet run```
	- Visual Studio: Run from IDE.
	- Standalone executable (after publish):
		```bash
		dotnet publish -c Release -o out
		./out/VPSMirror``` (Unix-like) or ```cmd out\VPSMirror.exe``` (Windows).

## How to Use
1. Update the mirror server IP and port in main-server.cs (use "127.0.0.1" for local testing).
2. Compile and run the program as described above.
3. The program will:
	- Start 4 main server threads that generate events and add to shared data.
	- Start the mirror server listener on the specified port.
	- Trigger automatic backups every 10 minutes, saving to timestamped .txt files in the current directory.
	- Log events, mirror processing, and received data to the console.
4. Simulate a VPS setup: Run on a cloud VPS for remote mirroring (update addresses accordingly).
5. View the presentation: Open replacement-exam-thomashoerger.pptx and watch replacment-exam-presentation-thomashoerger.mkv.
6. Demo the sync: Watch program-running-in-vps-server.mkv or run the program and observe console output for event generation, mirroring, and backups.
7. Press Enter in the console to exit when done (backups will continue via timer until then).

## Project Notes
- **Threading and Sync:** Main threads use `lock` on a shared object for critical section access to the event list.
- **Mirror Sync:** Events are sent via TCP immediately after generation; mirror processes and logs them in separate threads.
- **Retention Policy:** Backups are timestamped (mirror_backup_YYYYMMDD_HHmmss.txt); no auto-deletion, but policy can be extended to delete old files.
- **Automation:** Uses `System.Threading.Timer` for periodic backups; runs indefinitely until program exit.
- **Network Setup:** Assumes mirror on same machine or network; handle firewalls for remote VPS.
- **Event Data:** Simulated as "Event_{timestamp}" for simplicity; can be extended to real data.
- **Backup Logic:** Copies shared data under lock and writes to file; handles exceptions.
- **Performance:** Threads sleep 1s between events; suitable for demo, not production load.
- **Dependencies:** All standard .NET; no external packages.
- **Testing:** Run locally with localhost; verify console logs for sync and check backup files.
- **Documentation:** PowerPoint covers methodologies; instructions.pdf has full requirements.

## Future Improvements
- Implement actual retention policy (delete backups older than X days).
- Add remote VPS configuration via command-line args or config file.
- Enhance error handling for network failures (retries).
- Use async/await for non-blocking TCP operations.
- Add logging to files instead of just console.
- Integrate with cloud services (AWS/EC2 for real VPS mirroring).
- Support encryption for TCP data transfer.
- Create a full user guide PDF and automated test scripts.
- Optimize for higher thread counts or real-time data sources.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2023 VPS Mirror Automation".