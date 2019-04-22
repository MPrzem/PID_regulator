## General info
This project was created to understand how discrete PID controlers work. Microcontroller ATmega8 was working with electronic circuit which is depicted in diagram below.
Its task was controling temerature of heater using fan despite changes of outside temperature and power of heater.
The most challenging thing was tunning of controler. I had tried to use Zigler-Nicolson method, but parameters identification was hard. From the following equation follows that 
we can make unit jump by giving 1W(in some work point-fan working) to the heater or decrease recived power form heater by 1W. But 1W of recived power is not the same as 1W of fan power.
and also fan characteristic is not linear.

##Used libraries:
*Peter Dannegger's onewire liblaries. I added the function wich can change resolution of sensros(It's helpful because it change  measure time.
*Miroslaw Kardaœ liblaries for LCD HD44780 and UART(I used it when plotting the answer to the unit jump).


	Projekt ten zosta³ stworzony w celach edukacyjnych przeze mnie.
Pomóg³ mi zrozumieæ zasadê dzia³ania oraz zasade strojenia regulatorów PID w oparciu o uk³ad mikroprocesorowy ATmega8.
Mikrokontroler wspó³pracowa³ z uk³adem zamieszczonym na poni¿szym zdjêciu. Jego zadaniem by³o utrzymywanie sta³ej temperatury mimo zmian temperatury zewnêtrznej i mocy grza³ki.
Du¿ym wyzwaniem okaza³o siê strojenie uk³adu. 
	Poczatkowo chcia³em wykorzystaæ metode Zieglera-Nicolsona. Jednak identyfikacja parametrów uk³¹du okaza³a siê niebanalna.
Z poni¿szego równania wynika, ¿e skok jednostkowy mo¿emy uzyskaæ podaj¹c 1W mocy na grza³kê, lub zmniejszaj¹c o 1W moc odbieran¹ przez wiatrak. Jednak 1W mocy odbieranej nie jest
tym samym co 1W mocy przy³o¿onej do wiatraka, poza tym uk³ad wiatraka wykazuje nieliniowoœæ.

