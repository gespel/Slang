# Slang Language
Slang's syntax is inspired by languages like Rust, Python, and C, making it easy to learn for developers and artists familiar with these languages.
Central to Slang's design is its declarative approach to audio programming, where users define how audio buffers are processed rather than detailing step-by-step instructions. This allows for more intuitive and efficient audio programming.
## Variables
Slang only supports floating-point numbers as the primary data type. Variables can be defined as follows:
```slang
x = 1;
y = x * 2;
```
If you want to output a variable to stdout you can simply type:
```slang
x;
```
This will print the value of `x` to the console.
## Functions
Functions are defined using the `fn` keyword. Here's an example of a simple function that adds two numbers:
```slang
fn add(a, b) {
    return a + b;
}
result = add(3, 4);
result; // This will print 7
```
## Control Flow
Slang supports only the `if` statement for control flow. Here's an example:
```slang
x = 10;
if (x > 5) {
    y = x * 2;
} 
if (x <= 5) {
    y = x / 2;
}
y; // This will print 20
```
Additional control flow constructs like loops are not supported in Slang to maintain its declarative nature.
## Audio Objects
Slang provides built-in audio objects for common audio processing tasks. 
### Oscillators
For example, you can create an sine wave oscillator like this:
```slang
osc = sineosc(440);
```
This oscillator is now in the buffer core struct and will output to the generated audio buffer.
The typical oscillators available are:
- `sineosc(frequency);`
- `sawtoothosc(frequency);`
- `squareosc(frequency);`
> Note that the sine oscillator is implemented using a wavetable for efficiency. If you want to create a real sine oscillator using the `sin` function, you can do it like this: `truesineosc(440);`

### Wavetable Oscillator
You can also create a wavetable oscillator using a custom waveform. Here's an example:
```slang
osc = wavetableosc(strangeone, 110);
```
Where `strangeone` corresponds to a predefined wavetable in a file located in the `waves` directory relative to the `slang` executable.
You can also create your own wavetables by creating a `.swave` file and placing it in the `waves` directory. The format of the `.swave` file is a simple text file with one floating-point number per line representing the waveform samples.
```slang
0.0
0.5
1.0
0.5
0.0
-0.5
-1.0
-0.5
```

### Note to Frequency Conversion
You can use the classic note to frequency conversion using the following:
```slang
x = $c4; // This will set x to 261.63
```


