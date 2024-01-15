---
title: "Ćwiczenie 4: Multipleksowanie wyświetlacza siedmiosegmentowego"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
...

> If the comment and code disagree, both are probably wrong.
>
> — _Bjarne Stroustrup_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* wykorzystaniem rejestru przesuwnego,
* definiowaniem cyfr na wyświetlaczu siedmiosegmentowym,
* multipleksowaniem wyświetlacza siedmiosegmentowego,
* precyzyjną regulacją częstotliwości pracy timera.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Na kolejnych polach wyświetlacza LED powinny wyświetlać się cyfry.

Multipleksowanie polega na tym, że np. czterocyfrowy wyświetlacz złożony łącznie z $8\cdot4=32$ segmentów (wliczając kropki dziesiętne) można obsłużyć za pomocą znacznie mniejszej liczby pinów mikrokontrolera. W przypadku wyświetlaczy siedmiosegmentowych LED na ogół wykorzystuje się część pinów do włączania na krótki czas pojedynczych cyfr i 8 pinów do włączania segmentów w&nbsp;aktualnie wybranej cyfrze, co w&nbsp;naszym przykładzie oznacza zapotrzebowanie na $8+4=12$ pinów.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Poprzez multipleksowanie obsługiwane są różne rodzaje wyświetlaczy, a także klawiatur.}

![Sterowanie wyświetlaczem siedmiosegmentowym](display.png)

Zapotrzebowanie to można jeszcze znacząco zmniejszyć używając rejestru przesuwnego. Jest to układ cyfrowy, który posiada jedno wejście danych i wiele wyjść. Dane wprowadzane są szeregowo, w takt sygnału zegarowego, a po podaniu sygnału zatrzaskującego _latch_ przepisywane są na wyjścia.

Przykładowo, jeżeli rejestr przesuwny ma 8 wyjść, należy podać 8 taktów zegara, by wprowadzić pełny zestaw danych. Rejestr przesuwny posiada wyjście przeniesienia, które można podłączyć do wejścia kolejnego rejestru, dzięki czemu podając 16 taktów zegara możemy wprowadzić łącznie 16 bitów danych do obu rejestrów i wysterować 16 wyjść po podaniu sygnału zatrzaskującego.

\awesomebox[gray]{2pt}{\faMonument}{gray}{Pierwsze rejestry przesuwne zostały skonstruowane w latach 40. XX wieku na lampach elektronowych. Używane są do dzisiaj w szczególności w obwodach SerDes (\textit{Serializer/Deserializer}), obsługujących magistrale komunikacyjne, np. Ethernet i HDMI.}

![Schemat blokowy rejestru przesuwnego MC74HC595A](shift-register.png){width=10cm}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Połączenie multipleksowania oraz rejstrów przesuwnych pozwala obsłużyć $8\cdot4=32$ segmenty wyświetlacza za pomocą zaledwie 3 pinów procesora. Oczywiście, ceną za to jest konieczność oprogramowania całego procesu, który trwa co najmniej kilkadziesiąt taktów zegara mikrokontrolera.}

# Zadanie podstawowe

Celem zadania podstawowego jest uruchomienie wyświetlania multipleksowanego i uzyskanie odmierzania czasu z rozdzielczością 1&nbsp;s.

## Wymagania funkcjonalne

1. Częstotliwość multipleksowania wynosi 200&nbsp;Hz, a wyświetlane liczby zmieniają dokładnie co sekundę.
1. Wszystkie cyfry są wyświetlane prawidłowo.

## Wymagania jakości kodu

1. Wartość rejestru `OCR1A` powinna być zdefiniowana w sposób zależny od częstoliwości taktowania mikrokontrolera `F_CPU` i&nbsp;stałej `TIMER_FREQUENCY`, określającej żądaną częstotliwość multipleksowania 200&nbsp;Hz.

\awesomebox[teal]{2pt}{\faCode}{teal}{Dzięki uzależnieniu nastaw timera od stałych zdefiniowanych w kodzie można zarówno łatwo zmienić częstotliwość uzyskiwaną z timera, jak i zachować dotychczasową częstotliwość po zmianie taktowania całego mikrokontrolera (np. w celu obniżenia poboru prądu).}

## Modyfikacja programu

Aby precyzyjnie ustawić częstotliwość pracy timera, wykorzystano tryb CTC (_Clear Timer on Compare Match_), który pozwala regulować górną granicę odliczania timera za pomocą rejestru `OCR1A`. W tym trybie wykorzystujemy nie przerwanie przepełnienia timer (`TIMER_OVF`), ponieważ nie dochodzi do przepełnienia timera, ale przerwanie komparatora (`TIMER1_COMPA` w pliku `main.cpp`).

Wzór na częstotliwość przebiegu uzyskiwanego w timerze:

\begin{equation}
f = \frac{f_{clkI/O}}{N(1 + OCR1A)}
\end{equation}

Należy go przekształcić tak, by uzyskać wzór na wartość rejestru $OCR1A$. Żądana częstotliwość $f$ jest zdefiniowana w stałej `TIMER_FREQUENCY`, $N$ to wartość dzielnika preskalera, zaś częstotliwość zegara systemowego $f_{clkI/O}$ --- w&nbsp;stałej `F_CPU`.

\awesomebox[teal]{2pt}{\faCode}{teal}{W zadaniu podstawowym należy wprowadzić zmiany w pliku \lstinline{timer.cpp} w obrębie funkcji \lstinline{timerInitialize()}.}

\awesomebox[violet]{2pt}{\faBook}{violet}{Opis trybu CTC znajduje się w rozdziale \textit{16-bit Timer/Counter1 with PWM} w sekcji \textit{Clear Timer on Compare Match (CTC) Mode} dokumentacji mikrokontrolera.}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest odmierzanie czasu z dokładnością do 0,1&nbsp;s.

## Wymagania funkcjonalne

1. Liczby są inkrementowane co 0,1&nbsp;s.
1. Zaświecona jest kropka między pierwszą a drugą liczbą (licząc od prawej).

## Modyfikacja programu

Aby zwiększyć częstotliwość odliczania należy zmodyfikować funkcję `stopwatchTick()` w pliku `stopwatch.cpp`. Jest ona wywoływana w przerwaniu timera, a więc z częstotliwością 250&nbsp;Hz.

W celu włączenia kropki dziesiętnej na odpowiednim wyświetlaczu należy zmodyfikować funkcję `timeToDisplay()` w pliku `stopwatch.cpp`.
