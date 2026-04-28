# 🌃 Automatic Street Light Control System

**Microcontroller:** ARM Cortex-M3 — NXP LPC1768  
**IDE:** Keil µVision  
**Language:** Embedded C  
**Simulation Tool:** Proteus  

---

## 📌 Project Overview

This project implements an **intelligent, automated street lighting system** using the LPC1768 ARM Cortex-M3 microcontroller. The system reads ambient light intensity via an **LDR sensor** through the onboard **12-bit ADC**, and automatically controls street lights using **GPIO-driven relays/LEDs**. An **IR sensor** detects vehicle/pedestrian presence for smarter switching logic. A **16x2 LCD** displays real-time light intensity values for monitoring.

---

## ⚙️ Hardware Components

| Component | Description |
|---|---|
| LPC1768 | ARM Cortex-M3 Microcontroller @ 100 MHz |
| LDR Sensor | Ambient light detection via ADC Channel AD0.1 (P0.24) |
| IR Sensor 1 | Motion/presence detection on GPIO P1.14 |
| IR Sensor 2 | Motion/presence detection on GPIO P1.17 |
| LED 1 | Street light output on GPIO P1.20 |
| LED 2 | Street light output on GPIO P1.12 |
| 16x2 LCD | Real-time display of light intensity values |

---

## 🔌 Pin Configuration

| Pin | Function |
|---|---|
| P0.24 (AIN1) | ADC input from LDR sensor |
| P1.14 | IR Sensor 1 input |
| P1.17 | IR Sensor 2 input |
| P1.20 | LED 1 / Relay output |
| P1.12 | LED 2 / Relay output |

---

## 🧠 Working Logic

```
1. System initializes LCD, ADC, and GPIO registers
2. ADC continuously reads LDR sensor value (0–4095, 12-bit)
3. LCD displays real-time light intensity
4. If IR sensor detects presence AND ADC value > 3000 (low light):
      → Street light turns ON automatically
5. If light is sufficient (ADC < 3000):
      → Street light stays OFF (energy saving)
```

### ADC Threshold Logic
| ADC Value | Condition | Light State |
|---|---|---|
| > 3000 | Dark / Low light | 💡 ON |
| ≤ 3000 | Sufficient light | ⚫ OFF |

---

## 🔧 Register-Level Configuration

### ADC Setup
```c
LPC_SC->PCONP      |= (1<<12);           // Enable ADC power
LPC_SC->PCLKSEL0   |= (1<<25)|(1<<24);  // Set ADC clock
LPC_PINCON->PINSEL1|= (1<<16);           // P0.24 → AD0.1 (AIN)
LPC_ADC->ADCR       = (1<<1)|(4<<8)|(1<<16)|(1<<21); // ADC control
```

### ADC Reading (Polling Method)
```c
while(!(LPC_ADC->ADGDR & (1<<31)));      // Wait for DONE bit
adc1_value = (LPC_ADC->ADDR1 & (0xFFF<<4)) >> 4;  // Extract 12-bit value
```

---

## 💡 Key Features

- ✅ **Register-level programming** — no HAL/library abstraction
- ✅ **12-bit ADC** polling for accurate light sensing
- ✅ **Dual IR sensor** input for presence-based control
- ✅ **Real-time LCD display** of sensor readings
- ✅ **Energy efficient** — lights ON only when needed
- ✅ **Threshold-based logic** prevents flickering

---

## 📁 File Structure

```
lpc1768-street-light-control/
│
├── main.c          # Main application logic
├── lcd.h           # LCD function declarations
├── lcd.c           # LCD driver implementation
├── lpc17xx.h       # LPC1768 peripheral register definitions
└── README.md       # Project documentation
```

---

## 🚀 How to Run

1. Open **Keil µVision**
2. Load the project file (`.uvprojx`)
3. Build the project (`F7`)
4. Flash to LPC1768 using **Flash Magic** (`.hex` file via UART)
5. Power the board — LCD will display `AUTOMATIC STREET LIGHT CONTROL`
6. Cover the LDR to simulate darkness — LED turns ON automatically

---

## 📊 Output

```
LCD Display:
┌──────────────────┐
│ Light intensity: │
│ 3247             │
└──────────────────┘
→ LED1 ON (IR1 triggered, dark condition)
→ LED2 ON (IR2 triggered, dark condition)
```

---

## 👨‍💻 Author

**Bandi Srinivas Reddy**  
B.Tech ECE — Narasaraopeta Engineering College, JNTU Kakinada  
PG Diploma in Embedded Systems — IIES Bangalore  
📧 bvenkatareddy2003@gmail.com  
🔗 [LinkedIn](https://linkedin.com/in/srinivas-reddy-28479a267)

---

## 📜 License
This project is open source and available under the [MIT License](LICENSE).
