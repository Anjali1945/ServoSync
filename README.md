# ServoSync — STM32F407 Joystick Servo Controller

A personal embedded systems project I built to learn STM32 peripheral interfacing. It uses a joystick to control a servo motor with 3 switchable modes, a 16x2 LCD showing live data, and onboard LEDs indicating the current mode.

---

## Demo
[ Watch Demo Video ](https://drive.google.com/file/d/1DuN2PxBKbbIHbC2F84Cu0Z6TDQnD-h6N/view?usp=drivesdk) 

---

## What it does

- Move the joystick and the servo follows in real time
- Press a button to switch between 3 control modes
- LCD displays the current mode, joystick value, and servo position live
- Different onboard LED lights up for each mode

---

## The 3 Modes

|   Mode   |      LED       |              Behavior                              |
|   ---    |      ---       |                ---                                 |
| Manual   | Green (PD12)   | Joystick controls servo freely across full range   |
| Limit    | Orange (PD13)  | Servo movement restricted to center range only     |
| Reverse  | Red (PD14)     | Joystick direction is inverted for servo control   |

---

## Hardware

- STM32F407G Discovery Board
- HW-504 Analog Joystick Module
- SG90 Servo Motor (90° travel)
- QA-PASS 1602A 16×2 LCD (4-bit parallel mode)
- Push button with pull-up resistor
- 10kΩ potentiometer for LCD contrast
- Onboard Discovery LEDs

---

## Wiring

### Joystick
| Joystick Pin | STM32 Pin |
|     ---      |    ---    |
| VCC          | 3.3V      |
| GND          | GND       |
| VRx          | PA3       |
| VRy          | PA2       |

### Servo
|        Wire       |  STM32 Pin  |
|        ---        |     ---     |
| Red (VCC)         | 5V          |
| Brown (GND)       | GND         |
| Orange (Signal)   | PA6         |

### LCD 1602A — 4-bit parallel
| LCD Pin |    Name   |        Connected To       |
|   ---   |    ---    |            ---            |
| 1       | VSS       | GND                       |
| 2       | VDD       | 5V                        |
| 3       | V0        | Potentiometer middle pin  |
| 4       | RS        | PB0                       |
| 5       | RW        | GND                       |
| 6       | E         | PB1                       |
| 7–10    | D0–D3     | Not connected             |
| 11      | D4        | PB4                       |
| 12      | D5        | PB5                       |
| 13      | D6        | PB6                       |
| 14      | D7        | PB7                       |
| 15      | A         | 5V via 220Ω               |
| 16      | K         | GND                       |

### Button
|      Pin     |    Connected To    |
|      ---     |       ---          |
| One leg      | PB10               |
| Other leg    | GND                |

---

## Peripherals Used

|       Peripheral       |                 How I used it                  |
|          ---           |                      ---                       |
| ADC1 CH2, CH3          | Read joystick VRx and VRy analog values        |
| TIM3 CH1 PWM           | Generate 50Hz servo control signal on PA6      |
| GPIO Output            | LCD data/control pins and LED indicators       |
| GPIO Input             | Button polling with internal pull-up           |

---

## How the PWM works

The servo needs a 50Hz signal where pulse width determines angle.

```
TIM3 clock     = 84MHz / 83+1 = 1MHz (1 tick = 1 microsecond)
Timer period   = 20000 ticks = 20ms = 50Hz

Servo positions:
  250  µs pulse → 0°
  750  µs pulse → 90°
  1250 µs pulse → 180°
```

---

## Joystick to servo mapping

```c
// Map joystick ADC (0–4095) to servo PWM range (250–1250)
servoVal = ((vrx + vry) / 2 * 1000 / 4095) + 250;
```

Both axes are averaged so diagonal joystick movement also affects the servo smoothly.

---

## Mode switching logic

```
Power ON → Mode 0 Manual (green LED)
              ↓ button press
           Mode 1 Limit (orange LED)
              ↓ button press
           Mode 2 Reverse (red LED)
              ↓ button press
           Mode 0 Manual ← cycles back
```

Button uses software debounce — waits 50ms and confirms press before changing mode.

---

## File structure

```
ServoSync/
├── Core/
│   ├── Src/
│   │   ├── main.c       — main application, state machine, loop
│   │   └── lcd.c        — custom 4-bit LCD driver I wrote
│   └── Inc/
│       └── lcd.h        — LCD pin definitions and function prototypes
```

---

## What I learned

- How to read analog sensors using STM32 ADC with manual channel switching
- How to generate PWM signals using hardware timers for servo control
- How to write a peripheral driver from scratch (lcd.c — no library used)
- How to implement a state machine for multi-mode embedded control
- How to debounce a button in software
- Debugging hardware issues — loose connections, wrong pin conflicts, pulse range calibration

---

## Tools

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL Library
- Language: C (GNU11)

---

## Author
Anjali Thaware,
B.Tech - Electronics and Communication Engg.,
GitHub - [github.com/Anjali1945](https://github.com/Anjali1945)

