# 🌞 Light Sensor Project – STM32 + VEML7700

### STM32 NUCLEO-L152RE + 2× VEML7700 (Dual I²C)

Projekt demonštruje použitie **dvoch digitálnych svetelných senzorov VEML7700**, z ktorých každý je pripojený na **samostatnú I²C zbernicu** mikrokontroléra **STM32L152RE (NUCLEO-L152RE)**.  
Na základe nameraných hodnôt systém riadi **krokový motor**, ktorý sa natáča smerom k najsilnejšiemu svetlu.
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
- STM32 **NUCLEO-L152RE**
- 2× **VEML7700 Ambient Light Sensor**    
- 2× I²C zbernica (I²C1, I²C2)
- 3.3 V napájanie
- Prepojovacie káble

---

## 🔌 Zapojenie (Dual I²C)

### VEML7700 – ľavý senzor (I²C1)

|VEML7700|STM32|
|---|---|
|VCC|3.3 V|
|GND|GND|
|SCL|PB6 (I²C1_SCL)|
|SDA|PB7 (I²C1_SDA)|
|ADDR|GND|

---

### VEML7700 – pravý senzor (I²C2)

|VEML7700|STM32|
|---|---|
|VCC|3.3 V|
|GND|GND|
|SCL|PB10 (I²C2_SCL)|
|SDA|PB11 (I²C2_SDA)|
|ADDR|GND|

> Každý senzor má **vlastnú I²C zbernicu**, takže oba môžu používať rovnakú **7-bit adresu 0x10**.  
> I²C piny sú nakonfigurované ako **AF Open-Drain s Pull-Up**.

---

### 📐 Schematický diagram

![Circuit Diagram](circuit_image.svg)

---

## 🧠 Ako to funguje
1. STM32 inicializuje **I²C1 a I²C2**
2. Oba senzory VEML7700 sú nakonfigurované (Gain 1×, Integration Time 100 ms)
3. Periodicky sa čítajú ALS registre:
    - ľavý senzor cez I²C1
    - pravý senzor cez I²C2
4. Raw hodnoty sa konvertujú na **lux**
5. Hodnota môže byť ďalej použitá (napr. regulácia, rozhodovanie, logovanie)

---

## 📁 Štruktúra projektu
Core/\
├── Src/\
│ ├── main.c\
│ ├── i2c.c\
│ ├── gpio.c\
│ └── veml.c\
├── Inc/\
  ├── i2c.h\
  ├── gpio.h\
  └── veml.h\
LightFolower.ioc\
README.md
---

## ▶️ Spustenie projektu
1. Otvor `LightFolower.ioc` v **STM32CubeIDE**
2. Klikni **Generate Code**
3. Build & Flash na NUCLEO dosku
4. Sleduj premenné `lux_left` a `lux_right` v debuggeri

---



