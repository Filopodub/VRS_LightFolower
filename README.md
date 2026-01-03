## 🌀 Light-Following Stepper Motor
Projekt využívajúci krokový motor a dva svetelné senzory (LDR) na sledovanie smeru najsilnejšieho svetla.

## ✨ Popis projektu
Pomocou dvoch svetelných senzorov (ľavý a pravý) systém porovnáva intenzitu dopadajúceho svetla a podľa rozdielu otáča krokovým motorom tak, aby sa nasmeroval smerom k vyššej hodnote – teda k svetelnému zdroju.

## 🔧 Použité komponenty
- Krokový motor 
- Driver pre krokový motor 
- 2× svetelný senzor LDR + odporová delička
- Mikroprocesor 
- Zdroj napájania
- Prepojovacie káble

## 🧠 Ako to funguje
Svetelné senzory neustále merajú intenzitu svetla na ľavej a pravej strane.
Ak nieje detekovane žiadne silnejšie svetlo, točí sa vpravo.
Program porovná ich hodnoty:
Ak je ľavý senzor jasnejší, motor sa otočí vľavo.
Ak je pravý senzor jasnejší, motor sa otočí vpravo.
Ak sú hodnoty podobné, motor zostane na mieste.
Algoritmus beží v slučke a motor priebežne reaguje na zmeny svetla.

## ⚠️ Obmedzenia
Pri plnom 360° otáčaní môžu káble prekážať alebo sa skrútiť.
Odporúča sa použiť rotačný spoj (slip ring), alebo obmedziť rozsah pohybu.
