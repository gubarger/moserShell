# moserShell
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)]()
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)]()
[![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)]()
[![macOS](https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=apple&logoColor=white)]()
[![VIM](https://img.shields.io/badge/VIM-%2311AB00.svg?style=for-the-badge&logo=vim&logoColor=white)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)]()

## 🚀 About the project
***moserShell* is a lightweight, cross-platform command-line interpreter developed in `C++` for educational purposes. The project demonstrates the fundamentals of systems programming and implements key features of modern shell environments.**

## 🛠️&📦 Build and Run
**Prerequisites**  
- C++ compiler (GCC/Clang/MSVC)
- CMake ≥ 3.10  

1) Clone the repository:
```bash
git clone https://github.com/gubarger/moserShell.git
cd moserShell
```

2) Build with CMake:
```bash
mkdir build && cd build
cmake ..
cmake --build . # or use 'make' on Unix-like systems.
```

3) Run the shell:
```bash
./moser
```
### Custom configuration
There is a shared one in the repository `.gitignore` is for everyone. **If you need a personal one, then follow this example**:
```bash
cp .gitignore.example .gitignore.local # edit to suit your needs.
```

## 🎯 Usage examples
```bash
# Basic navigation
$ cd ~/projects
$ ls -la

# Output redirection
$ echo "Hello World" > output.txt
$ cat < input.txt

# Conveyors
$ ps aux | grep python | wc -l

# Background processes
$ sleep 10 &
```

## ✨ Chips and Possibilites
- ✅❌❌ Cross-platform (Linux, Windows, macOS)
- ✅ Executing basic commands
- ✅ Custom prompt
- ✅ Built-in commands (`cd`, `exit`, `alias`)
- ❌ I/O redirection (`>`, `<`, `>>`)
- ❌ Pipes (`|`)
- ❌ Background processes (`&`)
- ✅ Command history support
- ✅ Command completion

`**and more...**`
# 🚧 Project Status
**Active development** - pull requests and suggestions are welcome & Contributions are welcome!  

## 📊 Development status
**Functionality Status**:  
Basic Commands - ✅ Done
I/O Redirection - ⏳ In Progress
Pipelines - ⏳ In Progress
Background Processes - ⏳ In Progress
Command History - ✅ Done
Scripting - ⏳ In Progress

# 🧠 Educational Value
- During the development of this project, the following topics were covered:
- POSIX/Windows API system calls
- Process and memory management
- Interprocess communication
- Command parsing and interpretation
- Cross-platform development

# 📄 License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)  
- This project is licensed under the MIT License - see the LICENSE file for details.
