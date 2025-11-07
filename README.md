# Arduino Alarms: Distance & Temperature

Two small Arduino projects in one repo:

1) **Distance Alarm** — Ultrasonic proximity alert with an LED (and optional piezo buzzer).  
2) **Temperature Alarm** — Two-board setup: one Arduino measures temperature, the other displays state with four LEDs.

---

## Repository Structure
- `distance_alarm1 (1).ino` – Measures distance on **pin 7** (single-wire ultrasonic like Parallax PING))) and lights **LED on pin 10**. Prints distance (cm) to Serial.
- `temperaturni_alarm1.ino` – Reads **TMP36 on A1**, computes °C, sends `'a'|'b'|'c'|'d'` over Serial based on temperature band.
- `temperaturni_alarm2.ino` – Receives one char and blinks the matching LED: **W=4, R=5, Y=6, G=7**.

> Note: The temperature write-up mentions I²C; the sketches here are serial-based. You can keep serial (simplest) or adapt to I²C later.

---

## Hardware

### 1) Distance Alarm
- Arduino (Uno or similar)
- Ultrasonic distance sensor (single-pin type; or adapt for HC-SR04)
- 1× LED + current-limit resistor
- _(Optional)_ Piezo buzzer
- Jumper wires

**Default pins (sketch):**
- `pingPin = 7` (trigger/echo on one pin)
- `Led = 10`

### 2) Temperature Alarm (two Arduinos)
- **Arduino A (Sensor)**: TMP36 (Vout → **A1**, Vcc → 5 V, GND → GND)
- **Arduino B (Display)**: 4× LEDs (with resistors) on **D4 white**, **D5 red**, **D6 yellow**, **D7 green**
- **Serial link** between A and B (common GND, cross TX↔RX)

**Temperature bands (defaults):**
- `< 15 °C` → **Cold** (white LED)
- `15–30 °C` → **Normal** (green LED)
- `30–70 °C` → **Alert** (yellow LED)
- `> 70 °C` → **Danger** (red LED)

---

## Wiring

### Distance Alarm (single-pin ultrasonic)
- Sensor SIG → **D7**
- Sensor Vcc → **5 V**, GND → **GND**
- LED anode → **D10** (through 220 Ω), LED cathode → GND  
- _(Optional)_ Piezo → PWM pin (e.g., D9) + series resistor; GND to GND

> Using an HC-SR04? Replace the single `pingPin` approach with TRIG/ECHO pins and `pulseIn()`.

### Temperature Alarm (two boards)

**Arduino A (Sensor):**
- TMP36 Vout → **A1**
- TMP36 Vcc → **5 V**, GND → **GND**
- **TX** (D1) → Arduino B **RX** (D0)
- **GND ↔ GND**

**Arduino B (Display):**
- LEDs (with resistors) → **D4, D5, D6, D7**
- **RX** (D0) ← Arduino A **TX** (D1)
- **GND ↔ GND**

---

## How It Works

### Distance Alarm
- Sends a short pulse on `pingPin` and measures echo width.
- Converts microseconds to centimeters: `cm = microseconds / 29 / 2`.
- Prints `NNcm` to Serial every ~100 ms.
- If `cm < 50`, LED turns **ON** (and you can beep a piezo).

### Temperature Alarm
- Arduino A reads analog voltage from TMP36, converts to °C.
- Chooses a band and writes one character over Serial:
  - `'a'` = Cold, `'b'` = Normal, `'c'` = Alert, `'d'` = Danger
- Arduino B waits on Serial, blinks the corresponding LED and prints the label.

---

## Quick Start

### Prereqs
- [Arduino IDE](https://www.arduino.cc/en/software)
- Two USB cables (for the temp alarm), jumpers, LEDs, resistors.

### 1) Distance Alarm
1. Open **`distance_alarm1 (1).ino`**.
2. Verify pins, upload to your board.
3. Open **Serial Monitor @ 9600** baud to see `cm` readings.
4. Place an object closer than **50 cm** → LED should turn on.

### 2) Temperature Alarm
1. Open **`temperaturni_alarm1.ino`** and upload to **Arduino A** (sensor).
2. Open **`temperaturni_alarm2.ino`** and upload to **Arduino B** (display).
3. Cross-wire **TX(A) → RX(B)** and tie grounds.
4. Heat/cool the sensor and watch LEDs change state.

---

## Configuration

- **Distance threshold**: adjust in `distance_alarm1 (1).ino` where LED logic compares `cm < 50`.
- **Pins**: change `pingPin`, `Led`, LED pins (W/R/Y/G), and TMP36 analog pin if needed.
- **Temperature bands**: tweak the four ranges in `temperaturni_alarm1.ino`.
- **Piezo** (optional): add a buzzer pin and `tone()`/`noTone()` calls on proximity or “alert/danger”.



