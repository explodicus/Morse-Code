# Morse-Code
Morse Code Encoder/Decoder

Descriere

E un decodificator de cod morse în care introduci un cod morse iar mesajul decodificat apare pe LCD. 
Proiectul face și codificare a unui mesaj care este introdus de utilizator la calculator, iar apoi un led clipește corespunzător mesajului codificat.

Mod de Utilizare

Utilizatorul este intimpinat de un ‘Welcome Screen’.
Dupa ‘Welcome Screen’, un click lung pe buton te duce in modul de codificare, iar unul scurt in modul de decodificare. 
Pentru modul de codificare, se introduce un text format din cifre sau litere majuscule prin serial input (in Arduino). Dupa ce mesajul este trimis, acesta apare pe LCD, iar led-ul incepe sa clipeasca corespunzator codului morse al mesajului.
Pentru modul de decodificare, incepi sa apesi butonul in urmatorul mod: o unitate de timp pentru un punct, 3 unitati de timp pentru o linie, o unitate de timp de pauza (intre apasari de buton) pentru spatiu intre puncte/linii, 3 unitati de pauza pentru spatiu intre litere, 7 unitati de pauza pentru spatii intre cuvinte. 
O unitate de timp dureaza 200 milisecunde.
Dupa 10 secunde de inactivitate, aparatul revine in meniul principal.

Piese folosite:
LCD;
Broadboard;
Buton;
LED;
Fire;
Arduino.
