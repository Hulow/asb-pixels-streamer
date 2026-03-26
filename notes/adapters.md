# Adapters

3. What pattern it is closer to
Facade Pattern:
RmtAdapter hides complexity of multiple components behind a simpler interface (addSymbols(), transmit()).
Users don’t need to know about channel config, encoder, queue, or streamer details.
Strategy Pattern:
You can swap encoders or streamers at runtime (polymorphic ISymbolEncoder / IStreamer), which is classic Strategy.
Dependency Injection / Composition over Inheritance:
You’re “injecting” components rather than inheriting from a big monolithic class.