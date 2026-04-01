# ASB Pixels streamer

## Context

asb-pixels-streamer is a LED motion control application running on an ESP32 Wroom 32 microcontroller. It controls real-time LED effects and animations with an asynchronous execution logic.

This side project is will be my system for dynamic lighting installations, with a focus on supporting the electronic music community in Berlin.

The system controls 12V WS2815 LED strips, which require a precise signal using the NZR protocol. This protocol imposes strict timing constraints specified by the manufacturer.

The ESP32 uses its RMT (Remote Control) peripheral, which generates the modulated signal sent to the LEDs. The signal characteristics include:
- Frequence.
- Amplitude.
- Phase.

## Overview

This application is defined into different components:

              +--------+    +--------------------+    +------------+    +---------+-------------+    +-------------------+  
              | Pixel  | -> |     Drivers        | -> |  Commands  | -> |        Filters        | -> |       Domain      | 
              |        |    | (RMT Transmitter)  |    | (Handler)  |    | (Effects & Animation) |    |  (Frame & Pixel)  |
              +--------+    +--------------------+    +------------+    +-----------------------+    +-------------------+ 
            /
   +-------+
   | main  |
   +-------+
            \   
              +--------+    +--------------+
              | shared | -> | Timer & Task |
              |        |    |              |
              +--------+    +--------------+

This architecture separates domain logic, effect processing, and hardware control, making the system extensible and maintainable.

### Domain

- Pixel: a value object and characterized by the GRB color. 
- Frame: an aggregat of pixels representing a snapshot of the LED strip at a specific moment in time.

Frames are the core data structure used to produce animations and effects.

### Command Handler

- The command handler is responsible for:
    - Orchestrating frames in combination with filters
    - streaming pixels via a consumer interface (IConsumer).

It acts as the bridge between the application logic and low-level drivers.

### Filters

Filters implement the Decorator Pattern to process frames dynamically.
- Each filter implement the IConsumer interface.
- They wrap each other to form a decorator chain.
- Each filter modifies or enriches the frame before passing it downstream.
- Filters can implement effects such as Chasing or Fading.
- Example of effects:
                - Chasing
                - Fading
                - ...

This design allows flexible composition of visual effects without modifying core logic.

### Drivers

The driver layer handles low-level communication with the LED.

Responsable for:
- Configuring DMA Channels.
- Converting time-based pixel values into waveform signals.
- Streaming waveforms to the LED strips.

The driver implements the IConsumer interface, enabling whatever new filters and command handlers.


## Decorator Pattern

Filters are implemented using the Decorator Pattern, allowing dynamic composition of frame-processing logic.

                                    +-----------------+
                                    | RMT Transmitter |  <- concrete consumer
                                    +-----------------+
                                            |
                                    +-----------------+
                                    |   IConsumer     |  <- abstract consumer
                                    +-----------------+
                                            |
                                    +-----------------+
                                    |     Filter      |  <- abstract decorator
                                    +-----------------+
                                            |
    ----------------------------------------------------------------------------------
         |          |           |           |          |          |          |
   +-----------+ +--------+ +-----------+ +--------+ +--------+ +----------+ +-------+
   | Brightness| |  Blink | | Sparkling | | Fading | | Chasing| | Blackout | |  ...  |  <- concrete decorators
   +-----------+ +--------+ +-----------+ +--------+ +--------+ +----------+ +-------+


The abstract filter is the interface implementing IConsumer. 
The concrete filters implement specific effects.

This approach provides flexibility (runtime composition of effects), extensibility and separation of concerns.

## Getting started.

### Prerequisites

Install PlatformIO VS code extension.
### Build

```shell
pio run
```

### Flash

```shell
pio run --target uploadpio
```

### Monitore

```shell
pio run -t monitor
```

