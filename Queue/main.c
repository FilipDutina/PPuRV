/*Filip Dutina ra43-2014*/

/************************************************************************************/

/*OPIS ZADATKA*/

/*Zadatak je da se napravi modul koji predstavlja dvostruko spregnutu listu. Dati modul
 * treba da je izveden kao dinamicka biblioteka. Oslanjajuci se na taj modul treba
 * napraviti novi modul koji predstavlja red. Deljeni objekat koji sadrzi dvostruko
 * spregnutu listu treba dinamicki povezati tokom izvrsavanja.*/

/************************************************************************************/

/*IDEJA I REALIZACIJA*/

/*Najpre sam napravio dinamicku biblioteku u kojoj se nalaze "dll.h" i "dll.c" fajlovi.
 * U "dll.h" fajlu se nalazi struktura koja predstavlja jedan element dvostruko
 * spregnute liste i deklaracije funkcija. U "dll.c" fajlu se nalaze definicije
 * funkcija. Nakon toga sam napravio "main.c" fajl koji sam uvezao sa DLL dinamickom
 * bibliotekom i omogucio dinamicko povezivanje prilikom izvrsavanja. U "main.c" fajlu
 * se nalaze visestruki pozivi funkcija koje oslikavaju red kao strukturu podataka
 * i omogucavaju testiranje.*/

/************************************************************************************/

/*NAPOMENE*/

/*U DLL modulu od MISRA pravila sam prekrsio pravilo 20.4 koje se tice dinamickog
 * zauzimanja memorije. Ostala pravila sam ispostovao. Sto se tice "main.c" fajla,
 * vise MISRA pravila sam prekrsio i razlozi su navedeni iznad datih linija koda.
 * Pri pisanju ovog programa trudio sam se da u sto vecoj meri cuvam resurse i stoga
 * sam izabrao da mi tip podataka u dvostruko spregnutoj listi (redu) bude int_least32_t
 * (velicinu sam izabrao po sopstvenom nahodjenju jer nisam siguran za kakav sistem
 * pisem program, a dati izbor mi je delovao kao logican korak). Teoretski, velicina
 * same liste (reda) moze da bude neogranicena, odnosno onolika koliko je velika
 * memorija (naravno, ovde treba voditi racuna i koristiti samo onoliko resursa koliko
 * nam je neophodno). Takodje sam uveo makroe u svoj program radi lakse kontrole i
 * postovanja MISRA pravila.*/

/************************************************************************************/

/*TESTIRANJE*/

/*Sto se testiranja tice, prvo sam izveo neke jednostavnije provere, cisto da budem
 * siguran da je program u potpunosti funkcionalan. Nakon toga sam pokusavao da
 * ubacujem tipove podataka koji ne bi smeli da se pojave u listi (redu). Takodje sam
 * unosio validan tip podataka ali veci od dozvoljenog pa dolazi do "overflow-a". S
 * obzirom da sam koristo oznaceni tip podataka, vrednost na izlazu prelazi u suprotan
 * znak od unetog kada dodje do granice (kriticne vrednosti).*/

/************************************************************************************/

#if 0
	#define FPUTS(a) fputs a
#else
	#define FPUTS(a) (void)0
#endif


#if 0
	#define STDERR stderr
#else
	#define STDERR (void)0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <dlfcn.h>

void main(void);

void main(void)
{
	struct Node* head = (struct Node*)NULL;
	int_least8_t retVal1 = 0;
	int_least8_t retVal2 = 0;

	void* handle;

	void(*push)(struct Node** headNode, int_least32_t newData);
	void(*pop)(struct Node** headNode);
	void(*printList)(struct Node* headNode);

	char* error;

	handle = dlopen("/home/filip/workspace/DLL/Release/libDLL.so", RTLD_LAZY);

	if(handle == NULL)
	{
		FPUTS((dlerror(), STDERR));
		retVal1 = 1;
	}
	else
	{
		if(retVal1 != 1)
		{
			/*Ovde za sve tri funkcije dobijam upozorenja od MISRE, medjutim u
			 * "MISRA-C:2004 Guidelines for the use of the C language in critical
			 * systems" ne postoji ovaj tip upozorenja pa ga nisam mogao resiti*/
			/*warning: A value of type "void *" cannot be assigned to an entity
			 * of type "void (*)*/
			push = dlsym(handle, "push");
			pop = dlsym(handle, "pop");
			printList = dlsym(handle, "printList");

			error = dlerror();

			if(error != NULL)
			{
				FPUTS((error, STDERR));
				retVal2 = 1;
			}
			else
			{
				if(retVal2 != 1)
				{
					(*printList)(head);

					(*pop)(&head);

					(*push)(&head, 1);
					(*push)(&head, 2);
					(*push)(&head, 3);

					(*printList)(head);

					(*push)(&head, 4);
					(*push)(&head, 5);
					(*push)(&head, 6);

					(*printList)(head);

					(*pop)(&head);

					(*printList)(head);

					(*pop)(&head);

					(*printList)(head);

					(*push)(&head, 7);

					(*printList)(head);

					(*push)(&head, 8.66740213);
					(*push)(&head, 'a');

					(*printList)(head);

					(*pop)(&head);
					(*pop)(&head);
					(*pop)(&head);
					(*pop)(&head);
					(*pop)(&head);
					(*pop)(&head);

					(*printList)(head);

					(*pop)(&head);

					(*printList)(head);

					(*pop)(&head);
					/*Sledece vrednosti su namerno van opsega radi testiranja, pa
					 * su MISRA upozorenja zanemarena*/
					(*push)(&head, 1000000000000000);

					(*printList)(head);

					(*push)(&head, 1000000000000000.0);

					(*printList)(head);

					(*push)(&head, -1000000000000000.0);

					(*printList)(head);

					(*push)(&head, 's');
					/*Overflow*/
					(*push)(&head, 2147483647);
					(*push)(&head, 2147483648);

					(*printList)(head);
				}
			}
		}
	}

	dlclose(handle);
}


