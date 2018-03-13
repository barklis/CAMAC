.TH ANALIZATOR 1
.SH NAME
analizator \- Przetwarza zadaną bitmapę i zwraca ilość wystąpień okręgów(śladów)
.SH SYNOPSIS
.B analizator
[\fB\-o\fR \fINAME\fR]
[\fB\-jpg\fR \fINAME\fR]
.IR file ...
.SH DESCRIPTION
.B analizator
 W oparciu o bibliotekę OpenCV rozpoznaje i zlicza ślady w kształcie okręgów a także zwraca plik tekstowy bądź binarny z uzyskanymi zliczeniami. Program umożliwia także podgląd obrazu z kamery i wykonywanie wykrywania okręgów w czasie rzeczywistym.
.SH OPTIONS
.TP
.BR \-jpg " "  \fINAME\fR
Zwraca plik obrazu z naniesionymi wykryciami śladów.
.TP
.BR \-o " "  \fINAME\fR
Zwraca plik tekstowy z ilością zliczeń i promieniami śladów gdy zdefiniowana nazwa ma rozszerzenie ".txt" lub plik binarny jeśli nazwa ma rozszerzenie ".dat"
.TP
.BR \-s
Wyświetla uzyskany obraz w oknie.
.TP
.BR \-v
Przechwytuje obraz dostępnej kamery i wyświetla pogdląd obrazu wraz z wyświetlaniem znalecionych śladów.

.SH AUTHOR
Bartłomiej Kliś, Wydział Fizyki Politechnika Warszawska 2017-2018
