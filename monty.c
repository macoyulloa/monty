#include "monty.h"
int value;
/**
 * main - Main proyect monty
 * @ac: Number of arguments
 * @av: Arguments
 * Return: Errors
 **/
int main(int ac, char **av)
{
	FILE *fp;
	int i;
	stack_t *head = NULL;
	char *token, *argumts[1024], delimit[] = "/\n";
	int countargt = 0;

	if (ac == 2)
	{
		fp = fopen(av[1], "r");
		if (fp == NULL)
		{
			token = strtok(av[1], delimit);
			while (token != NULL)
			{
				argumts[countargt] = token;
				token = strtok(NULL, delimit);
				countargt++;
			}
			for (i = 0; argumts[i] != NULL; i++)
				;
			fprintf(stderr, "Error: Can't open file %s\n", argumts[i - 1]);
			exit(EXIT_FAILURE);
		}
		callfunc(fp, head);
		fclose(fp);
	}
	else
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * callfunc - call the function
 * @fp: file already open
 * @head: the head of the doubly linked list
 * Return: void function
 */
void callfunc(FILE *fp, stack_t *head)
{
	char *bufferc = NULL, *token = NULL, *argumts[1024], delimit[] = " \n";
	size_t bufsize = 32;
	unsigned int countargt = 0, line = 0;
	void (*exec)(stack_t **stack, unsigned int line_number);

	bufferc = (char *)malloc(bufsize * sizeof(char));
	if (!bufferc)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	while (getline(&bufferc, &bufsize, fp) >= 0)
	{
		line++;
		token = strtok(bufferc, delimit);
		if (!token)
			continue;
		while (token != NULL)
		{
			argumts[countargt] = token, token = strtok(NULL, delimit), countargt++;
		}
		if (countargt >= 1 && strcmp(argumts[0], "pall") != 0)
			ifnumber(fp, &head, argumts[1], bufferc, line);
		countargt = 0;
		exec = get_op_func(argumts[0]);
		if (exec == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line, argumts[0]);
			fclose(fp), free(head);
			exit(EXIT_FAILURE);
		}
		exec(&head, line);
	}
	free(bufferc);
	freemalloc(&head);
}
/**
 * freemalloc - Free memory
 * @stack: address of memory to clean
**/
void freemalloc(stack_t **stack)
{
	stack_t *tmp = NULL;

	tmp = *stack;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	while (tmp->prev)
	{
		tmp = tmp->prev;
		free(tmp->next);
	}
	free(tmp);
}

/**
 * ifnumber - check numbers
 * @fp: File pointer
 * @stack: head pointer
 * @argumts: arguments
 * @bufferc: data buffer
 * @line: numer line
**/
void ifnumber(
FILE *fp, stack_t **stack, char *argumts, char *bufferc, unsigned int line)
{
	unsigned int i = 0, j = 0;

	for (i = 0; i < strlen(argumts); i++)
		if ((argumts[i] > 47 && argumts[i] < 58) || argumts[i] == 45)
			j++;
	if (i == j)
		value = atoi(argumts);
	if (i != j || *argumts == 0 || *argumts == ' ')
	{
		fclose(fp);
		free(bufferc);
		freemalloc(stack);
		fprintf(stderr, "L%d: usage: push integer\n", line);
		exit(EXIT_FAILURE);
	}
	*argumts = ' ';
	j = 0;
}
