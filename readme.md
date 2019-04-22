## General info
This project was created to understand how discrete PID controlers work. Microcontroller ATmega8 was working with electronic circuit which is depicted in diagram below.
Its task was controling temerature of heater using fan despite changes of outside temperature and power of heater.
The most challenging thing was tunning of controler. I had tried to use Zigler-Nicolson method, but parameters identification was hard. From the following equation follows that 
we can make unit jump by giving 1W(in some work point-fan working) to the heater or decrease recived power form heater by 1W. But 1W of recived power is not the same as 1W of fan power.
and also fan characteristic is not linear.

##Used libraries:
*Peter Dannegger's onewire liblaries. I added the function wich can change resolution of sensros(It's helpful because it change  measure time.
*Miroslaw Karda� liblaries for LCD HD44780 and UART(I used it when plotting the answer to the unit jump).


	Projekt ten zosta� stworzony w celach edukacyjnych przeze mnie.
Pom�g� mi zrozumie� zasad� dzia�ania oraz zasade strojenia regulator�w PID w oparciu o uk�ad mikroprocesorowy ATmega8.
Mikrokontroler wsp�pracowa� z uk�adem zamieszczonym na poni�szym zdj�ciu. Jego zadaniem by�o utrzymywanie sta�ej temperatury mimo zmian temperatury zewn�trznej i mocy grza�ki.
Du�ym wyzwaniem okaza�o si� strojenie uk�adu. 
	Poczatkowo chcia�em wykorzysta� metode Zieglera-Nicolsona. Jednak identyfikacja parametr�w uk��du okaza�a si� niebanalna.
Z poni�szego r�wnania wynika, �e skok jednostkowy mo�emy uzyska� podaj�c 1W mocy na grza�k�, lub zmniejszaj�c o 1W moc odbieran� przez wiatrak. Jednak 1W mocy odbieranej nie jest
tym samym co 1W mocy przy�o�onej do wiatraka, poza tym uk�ad wiatraka wykazuje nieliniowo��.

