# ASB Pixels streamer

`asb-pixels-streamer` is a LED motion control application running on an ESP32 Wroom 32 microcontroller. It controls real-time LED effects and animations with an asynchronous execution logic.

I built this project to have good control over my LED strips and create interesting lighting installations for the underground electronic music scene in Berlin.

The system controls 12V `WS2815` LED strips, which require a precise input signal using the `NZR protocol`. This protocol imposes strict timing constraints specified by the manufacturer.

The ESP32 uses its `RMT (Remote Control Transceiver)` peripheral, which generates the modulated signal sent to the LEDs. The signal characteristics include:
- Amplitude fixed by the GPIO voltage (~3.3V)
- Phase
- Frequency defined by the pulse timings from the LED requirements. The resolution (clock + divider) defines how precise this timing is generated...

# Overview

This architecture separates domain logic, effect processing, and hardware control, making the system extensible and maintainable.

```
                                     INFRA                   PRESENTATION                 APPLICATION                  DOMAIN
              +--------+    +--------------------+    +-----------------------+    +---------+-------------+    +-------------------+  
              | Pixel  | -> |     Drivers        | -> |        Filters        | -> |        Command        | -> |   Frame & Pixel   | 
              |        |    | (RMT Transmitter)  |    | (Effects & Animation) |    |       (Handler)       |    |                   |
              +--------+    +--------------------+    +-----------------------+----+-----------------------+    +-------------------+ 
            /
   +-------+
   | main  |
   +-------+
            \                     INFRA 
              +--------+    +--------------+
              | Shared | -> | Timer & Task |
              |        |    |              |
              +--------+    +--------------+

```

## Domain

- `Pixel`: a value object and characterized by the `GRB color`. 
- `Frame`: an aggregate of pixels representing a snapshot of the LED strip at a specific moment in time.

Frames are the core data structure used to produce animations and effects.


## Command Handler

Part of the application layer and responsible for:
- Generating frames.
- Orchestrating the streaming loop.
- Delegating rendering/effects to the filter chain (`IConsumer` implementation)

It acts as the bridge between the application logic and the low-level driver.


## Filters

Part of the Presentation / Effect Layer and responsible for:
- Applying visual transformations to frames.
- Delegating processing to the next consumer in the chain.

They are implemented using the `Decorator Pattern` and rely on polymorphism (`IConsumer`) enabling a flexible composition of effects.


## Drivers

Part of the infrastructure layer, the RMT transceiver is responsible for:
- Configuring DMA Channels.
- Converting `time-based pixel` values into `waveform signals`.
- Streaming waveforms to the LED strips.

By implementing the `IConsumer` interface, the Transmitter can be easily integrated into the filters chain, enabling flexible composition of new filters and good chaining of effects :) :) 


# Decorator Pattern

Filters are implemented using the `Decorator Pattern` to dynamically compose visual effects.
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
    ---------------------------------------------------------------------------------
         |          |           |           |          |          |          |
   +-----------+ +--------+ +-----------+ +--------+ +--------+ +----------+ +-------+
   | Brightness| |  Blink | | Sparkling | | Fading | | Chasing| | Blackout | |  ...  |  <- concrete decorators
   +-----------+ +--------+ +-----------+ +--------+ +--------+ +----------+ +-------+

```
## Concept 

- `Filter` is an abstract decorator for all filters.
- It allows filter to wrap another consumer and build a chain of responsibility.
- Every filter is also an `IConsumer` because Filter inherits from `IConsumer`.


## Example of decorating effects on a LED strip

```
Fading* fading = new Fading(*transmitter);
Chasing* chasingAndFading = new Chasing(*fading);
Blinking* chasingAndFadingAndBlinking = new Blinking(*chasingAndFading);
CommandHandler* handler = new CommandHandler(*chasingAndFadingAndBlinking, *timer);
```

# Getting Started

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