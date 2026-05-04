This repository is a static archive of my early, raw memory-mapped C code for the STM32F302R8 (Nucleo-64). 

## Purpose
This code was written to test basic hardware peripherals before I built a proper hardware abstraction layer. It relies entirely on raw pointers and hardcoded memory addresses to verify clock configurations and register behaviors.

I will not be updating this repository or uploading any new code here. It exists strictly as a historical record of my learning process and to show progression.

## Contents
Raw ADC Test: Initial proof-of-concept for ADC conversions using direct register manipulation.
Raw GPIO Test (Jan 2026): Early pin toggling and setup with SYSTICK Blocking led blink

## Main Project
If you are looking for my actual, production-ready hardware abstraction layer, please visit my main repository. It contains clean, struct-based drivers for GPIO, SysTick, and ADC:
https://github.com/AgamyaSharma/stm32f302xx_drivers
