# Afisare Text Dinamic pe Display 7 Segmente

Proiect realizat in cadrul **Continental Summer Knowledge Hub**, care implementeaza afisarea dinamica a textului pe un display cu 7 segmente, folosind simulatorul online [Wokwi](https://wokwi.com/).

---

## Descriere

Sistemul permite afisarea unui text ce se poate derula (scroll) in diferite directii pe display-ul cu 7 segmente. Controlul directiei de scroll se face prin intermediul unor butoane fizice, oferind o interactiune dinamica si intuitiva.

---

## Cerinte Functionale (Functional Requirements)

- **FR1:** Sistemul trebuie sa poata afisa text in mod scroll stanga (textul intra din dreapta si iese pe stanga).
- **FR2:** Sistemul trebuie sa poata afisa text in mod scroll dreapta (textul intra din stanga si iese pe dreapta).
- **FR3:** Sistemul trebuie sa permita scroll vertical: sus (textul urca) si jos (textul coboara).
- **FR4:** Directia de scroll (orizontala/verticala si sensul) trebuie sa fie selectabila prin intermediul unor butoane.
- **FR5:** Textul afisat poate contine mai multe cuvinte separate prin spatii.

---

## Cerinte Non-Functionale (Non-Functional Requirements)

- **NFR1:** Timpul de reactie la apasarea unui buton pentru schimbarea directiei de scroll nu trebuie sa depaseasca un interval de 200 ms.
- **NFR2:** Se va stabili o prioritate in cazul in care ambele butoane sunt apasate simultan (prioritate pentru butonul stanga/dreapta).
- **NFR3:** Textul afisat trebuie sa fie usor de citit.
- **NFR4:** Codul sursa trebuie sa fie documentat si organizat pentru a facilita intelegerea arhitecturii.
- **NFR5:** Interfata hardware trebuie sa fie robusta si sa raspunda corect la actionarile fizice ale butoanelor.

---

## Utilizare

- Folositi butoanele pentru a schimba directia de scroll a textului.
- Textul poate contine spatii si va fi afisat dinamic pe display-ul cu 7 segmente.
- Proiectul a fost dezvoltat si testat in simulatorul online [Wokwi](https://wokwi.com/).

---

## Componente si Conexiuni Hardware

- **Arduino UNO**
- **Display 7-segmente, 4 digiti**
- **2 butoane**

**Conexiuni:**

- Segmentele A–G + DP ale afișajului sunt conectate la pinii D2–D9.
- DIG1–DIG4 sunt controlati de pinii D10–D13.
- Butonul stanga este conectat la pinul A0, iar butonul dreapta la pinul A1.
- Ambele butoane au rezistente pull-up activate din software, deci sunt active la nivel LOW.

---

## Descriere functionare

### Butoane

- **Butonul stanga (A0):**  
  La fiecare apasare, se activeaza modul scroll orizontal (stanga, dreapta).  
  Directia de scroll se inverseaza succesiv: stanga -> dreapta -> stanga -> dreapta, etc.

- **Butonul dreapta (A1):**  
  La fiecare apasare, se activeaza modul scroll vertical (sus, jos).  
  Directia de scroll se inverseaza succesiv: sus -> jos -> sus -> jos, etc.

### Vizualizare pe display

- Textul implicit este **"HELO"**, reprezentat prin coduri binare pentru segmentele 7-segmente.

#### Scroll orizontal
- Caracterele se deplaseaza pe display de la stanga la dreapta si invers.
- Implementat prin functiile `SchimbPozitieRtoL()` si `SchimbPozitieLtoR()`.
- Creeaza un efect de miscare orizontala fluida, caracterele rotindu-se intr-un ciclu continuu.

#### Scroll vertical
- Segmentele care formeaza caracterele sunt mutate sus sau jos, creand un efect de glisare verticala.
- Implementat prin functiile `shiftareBitiJos()` si `shiftareBitiSus()`.
- Ordinea literelor ramane aceeasi, insa iluminarea segmentelor variaza, simuland urcarea sau coborarea textului.

---
