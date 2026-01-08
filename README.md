# STM32 Embedded JSON Serialization Library

**Author:** Shrestha Srivastav
**Target Role:** Embedded / Firmware Developer Intern

---

## Project Overview

This project implements a lightweight, embedded-friendly C library that serializes structured meter data into a fixed JSON format suitable for smart-meter or w-M-Bus gateway pipelines.

The focus is on writing firmware-style code: predictable, memory-safe, easy to integrate, and easy to maintain. All communication, encryption, and protocol logic is intentionally out of scope. The project concentrates purely on **data modeling and JSON serialization**.

---

## Platform and Language

* **Platform:** STM32 (STM32CubeIDE)
* **Language:** C

STM32 platforms are widely used in industrial gateways and metering systems. C was chosen to ensure full control over memory usage, execution flow, and dependencies. The code is HAL-compatible and does not rely on any platform-specific peripherals.

---

## Design Principles

* **No dynamic memory allocation**
  All buffers are caller-provided for predictable behavior.

* **No external JSON libraries**
  JSON is generated using a small streaming writer to keep the implementation transparent and lightweight.

* **Deterministic and safe**
  Data is written sequentially into a fixed buffer with strict bounds checking.

* **Transport-agnostic**
  The core logic does not depend on UART, radio, MQTT, or logging.

* **Clear separation of concerns**
  Data models, JSON writer utilities, serialization logic, and application usage are kept separate.

---

## Project Structure (STM32CubeIDE)

```
Core/
├── Inc/
│   ├── meter_model.h
│   └── json_writer.h
└── Src/
    ├── json_writer.c
    ├── meter_serializer.c
    └── main.c
```

---

## Public API

```c
bool serialize_to_json(const GatewayPayload* input,
                       char* output_buffer,
                       size_t buffer_size);
```

### Behavior

* Writes JSON into a caller-provided buffer
* Returns `true` on success, `false` on failure
* Prevents buffer overflows
* Performs no I/O and no memory allocation

---

## JSON Output

* Outer element is always an array
* Field names and structure match the specification exactly
* Numeric values are serialized as numbers
* No additional fields are added

This ensures compatibility with downstream gateway and backend systems.

---

## Assumptions and Notes

* Input strings are valid and null-terminated
* Floating-point formatting uses standard `printf` behavior
* Example output uses `printf`; real firmware would use UART or SWO

---

## Possible Extensions

* Compile-time JSON size estimation
* Support for multiple gateway entries
* Fixed-point number formatting
* Unit testing with golden JSON output
* Integration with RTOS-based systems

---

## Closing Note

This project was written with real embedded firmware constraints in mind rather than as a desktop-style solution. The emphasis is on clarity, robustness, and maintainability—qualities expected in long-running embedded systems.

— **Shrestha Srivastav**
