#include <stdio.h>
#include <inttypes.h>
#include <dlfcn.h>

int main()
{
	void* handle;

	void(*push)(struct Node**, int_least32_t);
	void(*pop)(struct Node**);
	void(*printList)(struct Node*);

	char* error;

	struct Node* head = NULL;

	handle = dlopen("/home/filip/workspace/DLL/Release/libDLL.so", RTLD_LAZY);

	if(handle == NULL)
	{
		fputs(dlerror(), stderr);
		exit(1);
	}

	push = dlsym(handle, "push");
	pop = dlsym(handle, "pop");
	printList = dlsym(handle, "printList");

	if((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}


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


	dlclose(handle);


	return 0;
}


