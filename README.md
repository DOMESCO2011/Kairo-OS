=========================================
KairOS --- Originally by domesco --- 2026
=========================================
KairOS is an open source operating system that contains a kernel and the kariopak packets

* Documentation
    General OS Overview: content/KairOS/OS.md       — Detailed description of the Operating System
    Kairopak Subsystem: content/kairopak/desc.md    — Technical details about the modular architecture
    Credits: content/other/cred.md                  — Acknowledgments and contributors

* Main Entry Points & Source Code
    Kernel Main (C Entry Point): src/kernel/main.c              — The primary entry point where the system initializes after the bootloader
    Bootloader (ASM): src/kernel/boot/boot.asm                  — Handles Multiboot headers and stack setup
    System Manager: src/kairopak/kp-manager/manager.c           — The module responsible for orchestrating Kairopak services
    Messaging Interface (Link): src/kairopak/kp-link/link.c     — The layer providing data connection between modules
    System Shell: src/kernel/shell/shell.c                      — The interactive command-line interface

* Build & Configuration
    Makefile                                        — Instructions for compiling and linking the entire project
    Component IDs: src/include/id.h                 — Unique identifiers for system modules