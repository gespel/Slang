# Slang

**Slang** is a lightweight, high-performance programming language designed for **audio programming** and **multimedia applications**. It follows a buffer-driven computation model, where audio and multimedia buffers are directly calculated or modified from within the code.

Slang is widely adopted in embedded systems, particularly for writing **firmware** for **Eurorack modules** developed by **PhiLabs** and **GouodModules**. The entire Slang ecosystem is written in **ANSI C**, making it portable across virtually all platforms.


## Features

- Minimal and fast execution model  
- Buffer-based signal processing  
- Designed for embedded and real-time environments  
- ANSI C based – portable and lightweight  
- Used in professional modular synthesizer firmware  


## Quickstart

To build and run the Slang interpreter:

### Prerequisites

- A C compiler (e.g., `gcc`, `clang`)
- CMake (`>= 3.5`)
- Make
- Optional: `sudo` (for installing system-wide)

### Build Instructions

```bash
# Clone the repository (if not already done)
git clone https://github.com/gespel/Slang.git
cd Slang

# Create a build directory and configure the project
mkdir build
cd build
cmake ..

# Compile and optionally install
make
sudo make install

# Return to root and build the Slang interpreter
cd ..
make
```
### Run an Example
Once compiled, you can run a Slang example like this: 
```bash
./slang example/test1.slang
```

## Examples

The `example/` directory includes several demo scripts to help you get started:

- `test1.slang` – Basic signal processing
- `test2.slang` – Buffer manipulation
- `synth_example.slang` – Simple synthesizer logic


## Platform Support

Slang is known to work on:

- Linux (x86_64, ARM)
- macOS
- Windows (via WSL or MinGW)
- Embedded systems (e.g., STM32 via cross-compilation)


## License

Slang is released under the [MIT License](LICENSE).


## Contributing

Contributions are welcome!  
Feel free to open a pull request or start a discussion in the issues section.