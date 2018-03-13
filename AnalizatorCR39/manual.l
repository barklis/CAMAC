.TH ANALIZATOR 1
.SH NAME
analizator \- process jpg file and output how many circles are on bitmap
.SH SYNOPSIS
.B analizator
[\fB\-b\fR \fIBINARY_NAME\fR]
[\fB\-o\fR \fINAME\fR]
.IR file ...
.SH DESCRIPTION
.B analizator
Using OpenCV algorithm recognize circles on input jpg and create binary file with vector of counts, minimum radius and bin width.
.SH OPTIONS
.TP
.BR \-o "," \-\-name =\fINAME\fR
Create jpg file with marks around searched circles.
Default jpg name is out.jpg
.SH AUTHOR
Bartłomiej Kliś, Wydział Fizyki Politechnika Warszawska 2017-2018
