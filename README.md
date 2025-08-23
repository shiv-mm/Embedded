Embedded Projects with Vivado, C, and Flash Magic
Overview
This repository houses a collection of embedded-system prototypes that combine FPGA logic (Vivado), bare-metal C applications, and on-chip flashing via Flash Magic. Each project includes HDL sources, C firmware, build scripts, and programming instructions for a seamless hardware-software workflow.

Features
+ Modular Vivado projects with parameterized IP blocks

+ Bare-metal or lightweight RTOS-based C firmware

+ Automated bitstream and ELF generation via shell scripts

+ Flash Magic command-line programming templates

+ Clear directory structure for rapid onboarding

Prerequisites
Tool	Version / Notes
Xilinx Vivado	2018.3 or later
Vivado HLS (optional)	2019.1+ for high-level synthesis
GCC ARM toolchain	arm-none-eabi-gcc for your target device
Flash Magic	2018.11.30 or later; supports scripting via CLI
Python / Bash	For running automation scripts
