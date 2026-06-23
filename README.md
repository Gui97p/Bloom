# Bloom

Bloom is the userspace environment for the Sekura operating system.

Built entirely from scratch, Bloom provides the runtime libraries, shell, graphical framework, input system, applications, and developer APIs that run on top of the Sekura kernel.

The project serves both as a learning experience and as the foundation for a future desktop-oriented operating system environment.

> Bloom is not a Linux distribution and does not depend on Linux userspace components. Most of its runtime, libraries, drivers, and applications are implemented from scratch.

---

## Features

### Runtime

* Custom x86-64 CRT
* Custom syscall interface
* Freestanding userspace environment
* Custom linker scripts and build system

### LibC

* `stdio`
* `stdlib`
* `string`
* `unistd`
* `dirent`
* `fcntl`
* POSIX-inspired file APIs
* Buffered streams
* Directory traversal support

### Graphics (GLib)

* Framebuffer rendering
* Surface abstraction
* Primitive drawing APIs
* Font rendering
* Theme support
* Input abstraction

### Input

* Keyboard support
* Mouse support
* Unified event system
* Event queue abstraction

### Applications

* Interactive shell
* Graphical console
* Built-in command set
* Command history

---

## Project Structure

```text
userland/
├── arch/          # Architecture-specific code
├── crt/           # Runtime startup code
├── drivers/       # Userspace-facing device abstractions
├── include/       # Public headers
├── libs/
│   ├── libc/      # Standard library implementation
│   └── glib/      # Graphics and UI framework
├── src/
├── bin/           
│   ├── console/   # Console application
│   ├── shell/     # Shell implementation
│   └── ...
└── build/         # Build artifacts
```

---

## Event System

Bloom exposes hardware input through a unified event queue.

Applications receive generic events rather than interacting directly with keyboard or mouse drivers.

Example:

```c
event_t ev;

while (eventPoll(&ev)) {
    switch (ev.type) {
        case EVENT_KEY_DOWN:
            break;

        case EVENT_MOUSE_MOVE:
            break;
    }
}
```

---

## Graphics Framework

GLib is Bloom's native graphics framework.

Current functionality includes:

* Framebuffer drawing
* Surface management
* Font rendering
* Input events
* Theme support

Future goals include:

* Window manager
* Desktop environment
* Widget toolkit
* Graphical applications

---

## Building

```bash
make
```

The resulting userspace image can be loaded directly by the Sekura kernel.

---

## Relationship with Sekura

```text
Applications
     │
     ▼
   Bloom
     │
     ▼
   Sekura
     │
     ▼
 Hardware
```

Sekura provides the kernel, memory management, scheduling, filesystems, drivers, and system calls.

Bloom provides the userspace runtime, libraries, shell, graphical framework, and applications.

---

## Current Focus

* Event system
* Graphics framework
* Desktop environment foundations
* Performance improvements
* Filesystem APIs
* GUI application support

---
