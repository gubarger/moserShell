# moserShell
Shell programm for linux, Windows  
> [!NOTE]
> **A lightweight, cross-platform command shell interpreter written in C++ for educational purposes, focusing on the fundamentals of systems programming.**.  

`Used for development:`  
![Vim Badge](https://img.shields.io/badge/VIM-%2311AB00.svg?&style=for-the-badge&logo=vim&logoColor=white)
![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## OC support
![Linux Badge](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![MacOS Badge](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

## 📦 Build and Run
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

There is a shared one in the repository `.gitignore` is for everyone. **If you need a personal one, then follow this example**:
```bash
cp .gitignore.example .gitignore.local # edit to suit your needs.
```

## ✨ Chips and Possibilites
- Cross-platform support (Linux, Windows)
- Basic shell commands execution
- Custom command prompt
- Executing external programs and built-in commands (`cd`, `exit`, `alias`)
- Input/output redirection (`>`, `<`, `>>`)
- Conveyors (Pipes, `|`)
- Managing background processes (`&`)

`**and more...**`
# 🚧 Project Status
Active Development. Contributions are welcome!

# 📄 License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)  
- This project is licensed under the MIT License - see the LICENSE file for details.
