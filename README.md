# ASB Pixels streamer

`asb-pixels-streamer` is a LED motion control application running on an ESP32 Wroom 32 microcontroller. It controls real-time LED effects and animations with an asynchronous execution logic.

I built this project to have full control over my LED strips, so I can create more complex lighting installations for underground, under the radar electronic music events I organize with my friends in Berlin.

The system controls 12V `WS2815` LED strips, which require a precise input signal using the `NZR protocol`. This protocol imposes strict timing constraints specified by the manufacturer.

The ESP32 uses its `RMT (Remote Control Transceiver)` peripheral, which generates the modulated signal sent to the LEDs. The signal characteristics include:
- Amplitude fixed by the GPIO voltage (~3.3V)
- Phase
- Frequency defined by the pulse timings from the LED requirements. The resolution (clock + divider) defines how precise this timing is generated...

# Overview

This architecture separates domain logic, effect processing, and hardware control, making the system extensible and maintainable.

```

              +--------+    +--------------------+    +-----------------------+    +---------+-------------+    +-------------------+  
              | Pixel  | -> |     Drivers        | -> |        Filters        | -> |        Command        | -> |       Domain      | 
              |        |    | (RMT Transmitter)  |    | (Effects & Animation) |    |       (Handler)       |    |  (Frame & Pixel)  |
              +--------+    +--------------------+    +-----------------------+----+-----------------------+    +-------------------+ 
            /
   +-------+
   | main  |
   +-------+
            \   
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
- Orchestrating streaming.
- Delegating rendering/effects to the filter chain (`IConsumer` implementation)

It acts as the bridge between the application logic and the low-level driver.

## Filters

Part of the Presentation / Effect Layer and responsible for:
- Modifying frames visually.
- Delegating the frame to the next consumer in the chain.

This follows the Decorator Pattern. This design allows flexible composition of visual effects without modifying core logic.

## Drivers

Part of the infrastructure layer, the RMT transceiver is responsible for:
- Configuring DMA Channels.
- Converting `time-based pixel` values into `waveform signals`.
- Streaming waveforms to the LED strips.

By implementing the `IConsumer` interface, the Transmitter can be easily integrated into the filters chain, enabling flexible composition of new filters and good chaining of effects :) :) 


# Decorator Pattern

Filters are implemented using the `Decorator Pattern`, enabling dynamic composition of effects on frames & pixels. 

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

- `Filter` is an abstract decorator for all filters.
- It allows filter to wrap another consumer and build a chain of responsibility.
- Every filter is also an `IConsumer` because Filter inherits from `IConsumer`.

## Example

- Wrap in Fading 
```Fading* fadingEffect = new Fading(*transmitter);```

- Wrap in Chasing
```Chasing* chasingAndFadingEffects = new Chasing(*fadingEffect);```

- Wrap in Blinking
```Blinking* chasingAndFadingAndBlinkingEffects = new Blinking(*chasingAndFadingEffects);```

- Use the chain in command handler
```CommandHandler* handlerTwo = new CommandHandler(*chasingAndFadingAndBlinkingEffects, *timer);```


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
