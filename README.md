# Slang

Slang is a lightweight, high-performance programming language designed for audio programming. It follows a buffer-driven computation model, where audio buffers are directly calculated or modified from within the code. Slang gets interpreted at runtime, making it suitable for embedded systems and real-time audio processing.

Slang is widely adopted in embedded systems, particularly for writing firmware for Eurorack modules developed by PhiLabs. The entire Slang ecosystem is written in pure C with no external dependency, making it portable across virtually all platforms.


## Features

- Minimal and fast execution model  
- Buffer-based signal processing  
- Designed for embedded and real-time environments  
- ANSI C based – portable and lightweight  
- Used in professional modular synthesizer firmware
- Interpreter integrates with C/C++ projects easily


## Quickstart

To build and run the Slang interpreter:

### Prerequisites

- A C compiler (e.g., `gcc`, `clang`)
- Meson
- Optional: `sudo` (for installing system-wide)

### Build Instructions

```bash
# Clone the repository (if not already done)
git clone https://github.com/gespel/Slang.git
cd Slang

meson setup build
ninja -C build
```
### Run an Example
Once compiled, you can run a Slang example like this: 
```bash
./slang examples/synths.slang
```

## Examples

The `examples/` directory includes several demo scripts to help you get started:

- `basics.slang` – Basic syntax and operations
- `functions.slang` – Function definitions and usage
- `logic.slang` – Logical operations and control flow
- `synths.slang` – Simple oscillator examples

## Integrate Interpreter
The Slang interpreter can be very easily integrated into existing C/C++ projects.
To do that include the `slang-lib.h` header and link against the compiled Slang library at `build/libslang.a`. Here's a simple example of how to initialize the interpreter:

```c
#include "slang-lib.h"

int main() {
    char* p = "x = 1 + 2; y = x * 3;";
    int length;

    Token* tokens = tokenize(p, &length);
    SlangInterpreter* interpreter = createSlangInterpreter(tokens, length);
    interpret(interpreter);
    return 0;
}
```
The interpreter can be used to execute the language constructs defined in the Slang language. However, if audio processing is needed, the buffer core must be defined in the host application.
This can be achieved by defining the `SlangBufferCore` structure and passing the interpreter to it. This can be seen in the following example:
```c
#include "slang-lib.h"

int main() {
    char* p = "x = 1 + 2; y = x * 3;";
    int length;

    Token* tokens = tokenize(p, &length);
    SlangInterpreter* interpreter = createSlangInterpreter(tokens, length);

    SlangBufferCore* sbc = createBufferCore(interpreter, 48000, 32);
    
    interpret(interpreter);
    float* buf = renderBuffer(sbc);

    return 0;
}
```
## Platform Support

Slang is known to work on:

- Linux (x86_64, ARM)
- macOS
- Windows (via WSL)
- Embedded systems (e.g., STM32 via cross-compilation, ESP32 with ESP-IDF)


## License

Slang is released under the [MIT License](LICENSE).


## Contributing

Contributions are welcome!  
Feel free to open a pull request or start a discussion in the issues section.