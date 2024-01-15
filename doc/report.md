---
title: "Ćwiczenie 4: Multipleksowanie wyświetlacza siedmiosegmentowego"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usetikzlibrary{positioning}
...

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

Jaka wartość w rejestrze `OCR1A` zapewnia częstotliwość przebiegu w timerze równą 200&nbsp;Hz?
\vspace{1.5cm}

Jaką największą i najmniejszą częstotliwość przebiegu można uzyskać w trybie CTC w _Timer/Counter1_?
\vspace{1.5cm}

## Zadanie rozszerzone

Odczytaj z dokumentacji rejestru przesuwnego MC74HC595A minimalną szerokość impulsu dla sygnału zegarowego i zatrzaskującego przy napięciu zasilania 5&nbsp;V w temperaturze $\leq 85 ^\circ\text{C}$.
\vspace{1.5cm}

Odczytaj z dokumentacji mikrokontrolera, ile taktów zegara potrzebują instrukcje `SBI` i `CBI` (ustawianie i kasowanie bitu w rejestrze I/O). Jaki najkrótszy impuls za pomocą operacji zapisu do GPIO może wygenerować mikrokontroler taktowany zegarem 16MHz?
\vspace{1.5cm}

\awesomebox[violet]{2pt}{\faBook}{violet}{Skorzystaj z rozdziału \textit{Instruction Set Summary} dokumentacji mikrokontrolera.}
