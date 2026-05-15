# VSD Squadron Mini — RISC-V Internship Repository

A complete embedded systems learning and development repository documenting weekly progress during my RISC-V internship using the VSD Squadron Mini and PlatformIO.

# VSD Squadron Mini — RISC-V Firmware Internship

4-week internship building firmware APIs on the VSD Squadron Mini using bare-metal C and PlatformIO.

**Board:** CH32V003F4U6 (32-bit RISC-V)  
**Toolchain:** PlatformIO + NoneOS-SDK

---

## Repository Structure

```
├── include/       # Header files (.h)
├── src/           # Source files (.c) + main.c
├── week1/         # Week 1 exercises
├── week2/         # Week 2 exercises
├── week3/         # Week 3 exercises
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

---

## Task 2 — Week 1: Board Bring-up and GPIO

Three exercises covering GPIO fundamentals in bare-metal C.

- **`broad_bringup/`** — first firmware flashed. Turns LED ON to confirm the board boots.
- **`led_blink/`** — toggles onboard LED (PD6) with a blocking delay. Introduces `CFGLR`, `OUTDR`, and clock enable registers.
- **`input_read/`** — reads a push button on PD0, controls LED on PD6. Introduces `INDR` and input pin configuration.

---

## Week 2 — Timing Patterns

- **`blocking_delay/`** — LED blink with busy-wait loop. CPU is stuck during delay.
- **`counter/`** — LED toggles based on even/odd counter value.
- **`noblocking_led/`** — LED blink using SysTick interrupt and `millis` counter. CPU stays free between toggles.



## Author
Rushil Rai — Physics Undergraduate

