# VSD Squadron Mini — Week 1

Bare-metal RISC-V programming using PlatformIO and the VSD Squadron Mini.

## Objectives
- Set up PlatformIO toolchain
- Verify board programming
- GPIO register programming
- LED blinking
- Digital input handling

## Hardware
- VSD Squadron Mini
- CH32V003F4U6 (RISC-V MCU)

## Software
- VS Code
- PlatformIO
- NoneOS-SDK

## Implementations

### 1. Basic Firmware Verification
Minimal startup program to verify compilation and upload.

### 2. LED Blink
Direct register-level GPIO output control.

Concepts:
- Clock enable
- GPIO configuration
- Register bit manipulation
- Software delay loops

### 3. Digital Input Read
Reads GPIO input and controls LED state.

Concepts:
- Input configuration
- Reading INDR register
- Conditional hardware control

## Key Learnings
- Bare-metal embedded programming
- Register-level hardware control
- GPIO input/output configuration
- Firmware flashing workflow

## Build

```bash
pio run
```

## Upload

```bash
pio run --target upload
```

## Author

Rushil Rai
Physics Undergraduate | RISC-V Embedded Systems Intern