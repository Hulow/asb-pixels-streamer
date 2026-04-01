# ASB Pixels streamer

`asb-pixels-streamer` is a LED motion control application running on an ESP32 Wroom 32 microcontroller. It controls real-time LED effects and animations with an asynchronous execution logic.

I built this project to have full control over my LED strips, so I can create more complex lighting installations for underground, under the radar electronic music events I organize with my friends in Berlin.

The system controls 12V `WS2815` LED strips, which require a precise signal using the `NZR protocol`. This protocol imposes strict timing constraints specified by the manufacturer.

The ESP32 uses its `RMT (Remote Control Transceiver)` peripheral, which generates the modulated signal sent to the LEDs. The signal characteristics include:
- Frequency
- Amplitude
- Phase

# Overview

This architecture separates domain logic, effect processing, and hardware control, making the system extensible and maintainable.

```

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

```

## Domain

- `Pixel`: a value object and characterized by the `GRB color`. 
- `Frame`: an aggregate of pixels representing a snapshot of the LED strip at a specific moment in time.

Frames are the core data structure used to produce animations and effects.

## Command Handler

- The command handler is responsible for:
    - Orchestrating frames in combination with filters.
    - streaming pixels via a consumer interface (`IConsumer`).

It acts as the bridge between the application logic and low-level drivers.

## Filters

Filters implement the `Decorator Pattern` to process frames dynamically.
- Each filter implements the `IConsumer` interface.
- They wrap each other to form a decorator chain.
- Each filter modifies or enriches the frame before passing it downstream.
- Filters can implement effects such as Chasing or Fading.

This design allows flexible composition of visual effects without modifying core logic.

## Drivers

The driver layer handles low-level communication with the LED.

Responsible for:
- Configuring DMA Channels.
- Converting `time-based pixel` values into `waveform signals`.
- Streaming waveforms to the LED strips.

The driver implements the `IConsumer` interface, enabling whatever new filters and command handlers.


# Decorator Pattern

Filters are implemented using the Decorator Pattern, allowing dynamic composition of frame-processing logic.

```
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

```

The abstract filter is the interface implementing `IConsumer`. 
The concrete filters implement specific effects.

This approach provides flexibility (runtime composition of effects), extensibility and separation of concerns.

# Getting Started.

## Prerequisites

PlatformIO (VS Code extension recommended).

## Build

```shell
pio run
```

## Flash

```shell
pio run --target upload
```

## Monitor

```shell
pio run -t monitor
```
