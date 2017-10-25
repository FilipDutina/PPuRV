/*Filip Dutina ra43-2014*/

/************************************************************************************/

/*OPIS ZADATKA*/

/*Zadatak je da se napravi modul koji predstavlja dvostruko spregnutu listu. Dati modul
 * treba da je izveden kao dinamicka biblioteka. Oslanjajuci se na taj modul treba
 * napraviti novi modul koji predstavlja red. Deljeni objekat koji sadrzi dvostruko
 * spregnutu listu treba dinamicki povezati tokom izvrsavanja.*/

/************************************************************************************/

/*IDEJA I REALIZACIJA*/

/**/

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

					(*push)(&head, 1000000000000000);

					(*printList)(head);

					(*push)(&head, 1000000000000000.0);

					(*printList)(head);

					(*push)(&head, -1000000000000000.0);

					(*printList)(head);
				}
			}
		}
	}

	dlclose(handle);
}


