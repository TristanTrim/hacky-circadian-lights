# hacky-circadian-lights
Old lighting setup. It's pretty aweful, but strangely still seems better to me than iot solutions. Bah.

This project uses a old pc power supply to power strips of leds, and a teensy2.0 to turn them on and off at the right times of day.

There are many things that make this project garbage. The time is set by when you turn the thing on, so, you need to recompile if you want to turn it on some other time of day. Everything is hard coded in fact, so if you want to change the settings you need to edit the code, recompile, and then turn it on when you said you would in the code. Yes, this means the time maintained by the internal clock of the teensy! (This is bad. You should know that) However, experimental data shows that it only drifts by a minute or two over many months of usage, and when your simulated sunrise lasts for an hour it doesn't matter that much.

I'll document the circuit if anyone cares, but otherwise I'm thinking this project is likely permenently abandoned.
