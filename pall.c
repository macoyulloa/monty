#include "monty.h"
/**
 * pall_m - prints all the values, starting from the top of the stack
 * @stack: is the doubly linked list.
 * @line_number: line of the file.
 *
**/
void pall_m(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void) line_number;

	if (current != NULL)
	{
		while (current->next)
		{
			printf("%d\n", current->n);
			current = current->next;
		}
		printf("%d\n", current->n);
	}
}
