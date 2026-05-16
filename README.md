# VSD Squadron Mini — RISC-V Internship Repository

A complete embedded systems learning and development repository documenting weekly progress during my RISC-V internship using the VSD Squadron Mini and PlatformIO.

# VSD Squadron Mini — RISC-V Firmware Internship

4-week internship building firmware APIs on the VSD Squadron Mini using bare-metal C and PlatformIO.

**Board:** CH32V003F4U6 (32-bit RISC-V)  
**Toolchain:** PlatformIO + NoneOS-SDK

---

## Repository Structure

```
├── include/     
├── src/          
├── task1/         
├── task2/         
├── task3/         
└── platformio.ini
```

---

## Task 1 — Firmware Library Development

### What is a Library?
A library is a collection of reusable functions written once and used across every project. Instead of rewriting hardware register code for every task, you call a function and the library handles it internally. This is called a **Hardware Abstraction Layer (HAL)**.

### What is an API?
An API (Application Programming Interface) is the set of functions a library exposes. It hides the complexity underneath — you don't need to know how `gpio_write()` works internally, just that it sets a pin HIGH or LOW.

### How .h and .c files work together
Every library is split into two files:
- **`.h` (header)** — the menu. Lists what functions exist, their names, and what arguments they take. Any file that wants to use the library includes this.
- **`.c` (source)** — the kitchen. Contains the actual code inside each function — register writes, bit manipulation, hardware logic.

`main.c` only ever sees the `.h` file. The compiler links everything together behind the scenes.

---

### GPIO Library

| File | Purpose |
|---|---|
| `include/gpio.h` | Declares functions, pin modes, port aliases |
| `src/gpio.c` | Implements register-level GPIO operations |

Supports all 3 GPIO ports (GPIOA, GPIOC, GPIOD) and four pin modes:
`GPIO_OUTPUT`, `GPIO_INPUT`, `GPIO_INPUT_PU`, `GPIO_INPUT_PD`

```c
gpio_init(PORT_D, 6, GPIO_OUTPUT);   // configure pin
gpio_write(PORT_D, 6, GPIO_HIGH);    // set HIGH or LOW
gpio_toggle(PORT_D, 6);              // flip current state
gpio_read(PORT_D, 0);                // returns 1 or 0
```

### UART Library

| File | Purpose |
|---|---|
| `include/uart.h` | Declares serial functions |
| `src/uart.c` | Implements USART1 at configurable baud rate (TX = PD5) |

```c
uart_init(115200);          // setup serial
uart_print("text");         // send string
uart_println("text");       // send string + newline
uart_print_num(millis);     // send unsigned integer
uart_print_int(-42);        // send signed integer
```

**Output**

<!-- Insert output image here -->

```


## Author
Rushil Rai — Physics Undergraduate

