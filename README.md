# Saumix OS

Saumix is a custom operating system designed for the Raspberry Pi 3. It is primarily written in C and Assembly, with plans to integrate C++ support in the future.
To streamline development, Saumix offloads complex networking tasks to external ESP microcontrollers. By delegating the Bluetooth and WLAN stacks to the ESPs, the OS focuses on the core communication logic between the Pi and the ESP, allowing for faster prototyping of wireless features.
# VfR (Virtual Function Register)

VfR is a hardware abstraction layer designed for intuitive peripheral control. Instead of navigating deep file structures (e.g., /src/dev/gpio/led.c) or using complex function calls, VfR maps hardware actions directly to register-like variables.

How it works:
You can define a function that triggers automatically when a specific value is assigned to a VfR. For example, simply writing rLED = 1; will execute the underlying code to turn on the LED. This makes the code more readable and mimics the direct feel of low-level register programming.


