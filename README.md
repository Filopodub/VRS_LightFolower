# 🌞 Light Sensor Project – STM32 + VEML7700

Projekt demonštruje použitie digitálneho svetelného senzora **VEML7700** pripojeného
cez **I²C** k mikrokontroléru **STM32F303K8 (NUCLEO-F303K8)**.
Cieľom je inicializácia senzora, čítanie dát a výpočet intenzity osvetlenia v luxoch.

---

## ✨ Popis projektu
Senzor VEML7700 meria intenzitu okolitého svetla s vysokou presnosťou.
Mikrokontrolér STM32 komunikuje so senzorom pomocou rozhrania **I²C** a získané
dáta spracúva do fyzikálnej jednotky **lux**.

Projekt je postavený na **STM32CubeIDE** a využíva **HAL knižnicu**.
Kód je rozdelený do samostatných modulov:
- `i2c` – konfigurácia I²C
- `gpio` – základná inicializácia GPIO
- `veml` – driver pre VEML7700

---

## 🔧 Použité komponenty
- STM32 NUCLEO-F303K8
- VEML7700 Ambient Light Sensor
- I²C zbernica (SCL, SDA)
- 3.3 V napájanie
- Prepojovacie káble

---

## 🔌 Zapojenie (I²C)
| VEML7700 | STM32 |
|--------|-------|
| VCC    | 3.3 V |
| GND    | GND   |
| SCL    | PB6   |
| SDA    | PB7   |

> I²C piny sú nakonfigurované ako **AF Open-Drain s Pull-Up**.

---

## 🧠 Ako to funguje
1. STM32 inicializuje I²C perifériu
2. VEML7700 je nakonfigurovaný (Gain 1×, Integration Time 100 ms)
3. Periodicky sa číta ALS register
4. Raw hodnota sa konvertuje na lux podľa datasheetu
5. Hodnota môže byť ďalej použitá (napr. regulácia, rozhodovanie, logovanie)

---

## 📁 Štruktúra projektu
Core/
├── Src/
│ ├── main.c
│ ├── i2c.c
│ ├── gpio.c
│ └── veml.c
└── Inc/
├── i2c.h
├── gpio.h
└── veml.h
LightFolower.ioc
README.md
---

## ▶️ Spustenie projektu
1. Otvor `LightFolower.ioc` v **STM32CubeIDE**
2. Klikni **Generate Code**
3. Build & Flash na NUCLEO dosku
4. Sleduj hodnoty v debuggeri (premenná `lux`)

---

## ⚠️ Poznámky
- VEML7700 používa **7-bit I²C adresu (0x10)**  
- Pull-up rezistory sú povinné (interné alebo externé)
- I²C Timing je generovaný pomocou CubeMX

---

## 📜 Licencia
Projekt je určený na študijné a vzdelávacie účely.

