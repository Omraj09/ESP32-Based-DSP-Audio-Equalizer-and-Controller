# ESP32-Based DSP Audio Equalizer and Controller

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Framework](https://img.shields.io/badge/Framework-PlatformIO-orange)
![License](https://img.shields.io/badge/License-MIT-green)

## 📌 The Concept
A complete, high-fidelity firmware and hardware architecture for an ESP32. This system handles Bluetooth A2DP audio routing, real-time Digital Signal Processing (DSP) for dynamic equalization, and communication with a premium DAC and Class-D amplifier over I2S. 

This is not a basic Arduino speaker box. This is a mechatronics-grade audio controller utilizing **FreeRTOS** to manage audio streaming and a real-time web interface without blocking or stuttering.

## ⚙️ Core Architecture
* **Bluetooth Audio Sink:** Intercepts high-quality A2DP streams from any mobile device.
* **Dual-Core FreeRTOS:** Core 0 handles the asynchronous web UI and Wi-Fi stack. Core 1 is dedicated to the high-speed I2S DMA transfers and audio math.
* **Real-Time DSP:** Implements Infinite Impulse Response (IIR) Biquad filters in embedded C++ to manipulate frequency bands dynamically without phase distortion.
* **I2S Digital Output:** Bypasses the internal DACs, outputting a pristine digital bitstream directly to an external, dedicated audio decoder.

## 🛠️ Hardware Requirements
To make this system bulletproof, the following components are strictly required. Cheap silicon will bottleneck the DSP architecture.

1. **Microcontroller:** ESP32 Development Board (WROOM-32)
2. **DAC:** Texas Instruments PCM5102A (I2S, 32-bit/384kHz, Internal PLL)
3. **Amplifier:** Texas Instruments TPA3255 Class-D (2x260W)
4. **Primary Power:** 48V 10A Switch Mode Power Supply (SMPS)
5. **Digital Power:** Isolated 48V-to-5V DC-DC Converter + 3.3V Low-Dropout Regulator (LDO)

### ⚡ Critical Power Topology Warning
**DO NOT** run the 32-bit DAC and the 260W Class-D amplifier off an unisolated power supply. The switching noise from the amplifier will feed back into the logic stage, resulting in a high noise floor and catastrophic digital jitter. An isolated DC-DC converter must be used to break the ground loop between the high-power analog stage and the sensitive digital logic stage.

## 📂 Repository Structure
This project is built using **PlatformIO**. It will not compile correctly in the standard Arduino IDE without manual library management.

```text
├── platformio.ini              # Build configurations and dependencies
├── include/
│   ├── dsp_biquad.h            # DSP filter logic headers
│   └── web_server.h            # Async web server headers
├── src/
│   ├── main.cpp                # Core RTOS tasks, I2S setup, and A2DP routing
│   ├── dsp_biquad.cpp          # DSP mathematics and Peaking EQ formulas
│   └── web_server.cpp          # Web UI routing
└── data/
    └── index.html              # Frontend UI for the equalizer
