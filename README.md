STM32 Embedded JSON Serialization Library
Author: Shrestha Srivastav
Target Role: Embedded / Firmware Developer Intern

Project Overview

This project implements a small, embedded-friendly C library that serializes structured meter data into a fixed JSON format. The JSON output is designed to match a typical smart-meter or w-M-Bus gateway data pipeline, where measurement data collected on constrained devices must be forwarded reliably to a backend system.
The goal of this assignment was not only to generate valid JSON, but to design the solution the way it would be written in real firmware: predictable, memory-safe, easy to integrate, and easy to reason about.

All radio communication, encryption, and protocol handling are intentionally kept out of scope. The focus is strictly on data modeling, serialization, and clean embedded software design.
Why STM32 and C
This project targets STM32-class microcontrollers and is written entirely in C.
STM32 platforms are commonly used in industrial gateways and metering devices, and STM32CubeIDE encourages a structured firmware layout with clear separation between application logic and reusable modules. C was chosen because it provides full control over memory usage, execution flow, and dependencies, which is essential in long-running embedded systems.
The code is compatible with STM32 HAL projects generated using STM32CubeIDE and does not rely on any platform-specific peripherals.

Key Design Principles
The implementation follows a few core principles that are typical in production firmware:
No dynamic memory allocation
All memory is caller-provided. This avoids heap fragmentation and unpredictable runtime behavior.

No external JSON libraries

JSON is generated manually using a small streaming writer. This keeps the code lightweight and transparent.
Deterministic behavior
JSON is written sequentially into a fixed buffer with strict bounds checking on every write.

Transport-agnostic core logic
The serialization library does not depend on UART, radio, MQTT, or logging. Output handling is left to the application layer.
Clear separation of concerns
Data models, JSON writing utilities, serialization logic, and application usage are kept separate.
#Project Structure# (STM32CubeIDE)

Core/

├── Inc/
│   ├── meter_model.h        // Data structures
│   └── json_writer.h        // JSON writer interface
│
└── Src/
    ├── json_writer.c        // Minimal JSON writer implementation
    ├── meter_serializer.c  // Serialization logic
    └── main.c               // Example usage (application layer)
Data Model
The internal data model represents:
Gateway-level metadata (ID, date, device type, interval)

A bounded list of devices
For each device, one or more measurement data points
The maximum number of devices and data points is defined at compile time to ensure predictable memory usage. All strings are assumed to be valid and null-terminated.
Public API
The main entry point of the library is:
bool serialize_to_json(const GatewayPayload* input,
                       char* output_buffer,
                       size_t buffer_size);
Behavior
Writes JSON into the provided buffer
Returns true on success
Returns false if the buffer is too small or input cannot be serialized safely
Never allocates memory internally
Never performs I/O operations

JSON Output

The generated JSON strictly follows the required structure:
The outer element is always an array
Field names and hierarchy are preserved exactly
Numeric values are serialized as numbers, not strings
No additional fields are added
This ensures compatibility with downstream gateways or backend systems.
Error Handling and Safety
Every write operation checks remaining buffer space
Buffer overflows are prevented by design
The function fails early if serialization cannot be completed safely
All limits are explicit and visible in the code
This approach favors reliability and predictability over convenience.
Assumptions and Limitations
Input strings are valid and UTF-8 compatible
Floating-point formatting uses standard printf behavior
The example uses printf for demonstration; real firmware would use UART or SWO
The project focuses on single-gateway payloads as defined in the assignment
Possible Extensions
This implementation can be extended in several directions without changing its core structure:
Compile-time JSON size estimation
Support for multiple gateway entries
Optional fixed-point number formatting
Unit tests using golden JSON output comparison
Integration with RTOS tasks or communication stacks
Closing Note
This project was written with real embedded firmware constraints in mind rather than as a desktop or scripting solution. The emphasis was on clarity, robustness, and maintainability — qualities that are important in systems expected to run continuously and interface with larger data pipelines.
I would be happy to discuss the design decisions, trade-offs, and possible improvements during an interview.
— Shrestha Srivastav
