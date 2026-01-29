# KY-037 sound sensor examples (Analog & Digital)
This repository contains two example Arduino programs demonstrating how to use the KY-037 microphone sound sensor module in two different ways:

- Digital output (DO) — simple threshold-based detection

- Analog output (AO) — software-defined threshold with continuous signal monitoring

The goal is to clearly show how the sensor behaves electrically and why you might choose one approach over the other.

## Digital Version (sound_sensor_digital/)
The digital output (DO) uses the onboard comparator (LM393) and potentiometer to generate a HIGH / LOW signal when sound exceeds a hardware-defined threshold.

This version demonstrates:

- Edge detection (LOW → HIGH)

- Time-based debounce

- Clap-controlled LED toggle

## Analog Version (sound_sensor_analog/)
The analog output (AO) provides a raw voltage proportional to sound intensity.
All processing is done in software:

- Baseline tracking

- Software-defined threshold

- Event detection

- Lockout (event debounce)

- Periodic signal logging via Serial

This version demonstrates:

- Analog signal sampling

- DC bias (baseline) tracking

- Software event detection

- Time-based lockout