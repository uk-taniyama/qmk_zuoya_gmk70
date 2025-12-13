[Japanese](README.ja.md)

# ZUOYA GMK70 — QMK Firmware (Custom Build)

- This is a custom QMK Firmware source for the ZUOYA GMK70.  
- The firmware builds and works with USB wired connection testing.  
- It is compatible with **qmk_firmware up to version 0.26.11**.

> ⚠️ **Note:**  
> Wireless / Bluetooth functionality has **not** been verified.

---

## Overview

This project is based on the publicly available firmware for the GMK70.  
It merges portions of the `tri-mode` branch of `qmk_firmware` and source files from **epomaker split keyboards**, then applies adjustments to make the GMK70 buildable and usable.

The goal is to create a **QMK firmware environment for GMK70 that compiles and basically works**.

---

## Base Sources

1. Download and extract the archive:  
   - `http://www.mathewkb.com/wp-content/uploads/2024/11/ZUOYA-GMK70.7z`

2. Place the extracted data under:  
   ```
   keyboards/zouya/gmk70
   ```

3. Clone tri-mode compatible QMK Firmware:  
   ```
   git clone https://github.com/hangshengkeji/qmk_firmware.git qmk_wk
   ```

4. Checkout the `tri-mode` branch:  
   ```
   cd qmk_wk
   git checkout tri-mode
   ```

5. Copy the following components from `qmk_wk`:  
   - `keyboard/linker`
   - All files under `keyboard/epomaker_split65`

6. Merge and adjust the source from `epomaker_split65`  
   → Integrate and modify for GMK70

---

## Build Instructions

> This project uses simple Makefile commands instead of standard QMK tooling.

| Command | Description |
|--------|-------------|
| `make build` | Build the firmware |
| `make clean` | Clean build files |
| `make rebuild` | Clean and then build |

---

## Differences from the Original Firmware

- **Bootloader entry:**  
  Long-press the **encoder** to enter boot mode
- **Layout change:**  
  Keycodes in the number row have been rearranged

---

## Current Status

### ✔ Working

- Firmware builds successfully
- Basic USB wired operation confirmed

### ❔ Unknown

- Wireless / Bluetooth functionality

### ⚠️ Known Issues / Suspected Problems

- After being idle for some time, the **right side stops responding**  
  → Split communication seems unstable (cause unknown)

---

## Notes

This project aims to investigate GMK70 firmware and port it into QMK.  
It is intended for people who want something that **builds and mostly works on their own keyboard**.

Contributions, investigation, and fixes are welcome.

