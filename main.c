/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:30:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/07/01 17:35:50 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

#define RESET_COLOR	"\e[m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define PURPLE  "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"


typedef struct	s_stack{
	int	size;
	int	count;
	int	*arr;
}	t_stack;

//INITIALIZING STACKS////////////////////////////////////////////////////////////////
void	push(t_stack *stack, int element)
{
	stack->arr[stack->count] = element;
	stack->count++;
}

t_stack *init_stack_b(t_stack *stack_a)
{
	t_stack *stack;

	stack = malloc(sizeof(*stack));
	if (!stack)
		return (0);
	stack->count = 0;
	stack->size = stack_a->size;
	stack->arr = malloc(sizeof(int) * stack->size);
	if (!stack->arr)
		return (0);
	return (stack);
}

t_stack *init_stack(char *argv[], int size)
{
	int	i;
	t_stack *stack;

	stack = malloc(sizeof(*stack));
	if (!stack)
		return (0);
	stack->arr = malloc(sizeof(int) * (size));
	if (!stack->arr)
		return (0);
	i = 1;
	stack->count = 0;
	stack->size = size;
	while (i <= size)
	{
		push(stack, ft_atoi(argv[i]));
		i++;
	}
	return (stack);
}


t_stack *init_stack_1arg(char *argv[], int size)
{
	int	i;
	t_stack *stack;

	stack = malloc(sizeof(*stack));
	if (!stack)
		return (0);
	stack->arr = malloc(sizeof(int) * (size));
	if (!stack->arr)
		return (0);
	i = 0;
	stack->count = 0;
	stack->size = size;
	while (i < size)
	{
		push(stack, ft_atoi(argv[i]));
		i++;
	}
	return (stack);
}

int	check_if_sorted(t_stack *stack)
{
	int	i;

	i = 0;
   	printf("size of the stack: %d\n", stack->size);
	while (i < stack->size - 1)
	{
		if (stack->arr[i] < stack->arr[i + 1])
			return (0);
		i++;
	}
	printf(GREEN"\n[The stack is sorted!]\n\n"RESET_COLOR);
	return (1);
}

//OPERATIONS/////////////////////////////////////////////////////////
void	swap(t_stack *stack)
{
	int	i;
	int	temp;

	i = stack->count - 1;
	temp = stack->arr[i];
	stack->arr[i] = stack->arr[i - 1];
	stack->arr[i - 1] = temp;
}

void	reverse_reversed(t_stack *stack)
{
	int	i;
	int	x;
	int	temp;
	
	x = 0;
	i = stack->count - 1;
	temp = stack->arr[x];
	while (x < stack->count)
	{
		stack->arr[x] = stack->arr[x + 1];
		x++;
	}
	stack->arr[i] = temp;
}

void	reverse(t_stack *stack)
{
	int	i;
	int	x;
	int temp;
	
	i = stack->count - 1;
	temp = stack->arr[i];
	x = 0;
	while (i > 0)
	{
		stack->arr[i] = stack->arr[i - 1];
		i--;
	}
	stack->arr[0] = temp;
}

void	pop_element(t_stack *stack_1, t_stack *stack_2)
{
	int	element;

	element = stack_2->arr[stack_2->count - 1];
	stack_2->count--;
	stack_1->arr[stack_1->count] = element;
	stack_1->count++;
}

//////////////////////////////////////////////////////////////////////

int	main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;
	char **elements;
	int i;
	i = 0;

	if (argc < 2)
	{
		printf("ERROR");
		return (1);
	}

	//check if the argument is a string
	else if (argc == 2)
	{
		elements = ft_split(argv[1], ' ');
		while (elements[i])
			i++;
		stack_a = init_stack_1arg(elements, i);
	}
	else
		stack_a = init_stack(argv, argc - 1);	

	//visualizing stack_a
	i = stack_a->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_a->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_a->arr[stack_a->count - 1]);
	
	/* checking if already sorted
	if (check_if_sorted(stack_a) == 1)
		printf(GREEN"\n[The stack is already sorted!]\n\n"RESET_COLOR);
	else
		printf(RED"\n[The stack has NOT yet been sorted!]\n\n"RESET_COLOR);
	*/
	
	check_if_sorted(stack_a);

	// initializing stack_b
	stack_b = init_stack_b(stack_a);
	printf("Malloced amount for stack_b: %d\n", stack_b->size);


	/* CHECKING IF THE SWAP WORKS
	swap(stack_a);

	i = stack_a->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_a->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_a->arr[stack_a->count - 1]);
	*/

	
	/*CHECKING IF REVERSE_REVERSED WORKS
	reverse_reversed(stack_a);
	i = stack_a->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_a->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_a->arr[stack_a->count - 1]);
	
	check_if_sorted(stack_a);
	*/
	

	/*CHECKING IF REVERSE WORKS
	reverse(stack_a);
	i = stack_a->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_a->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_a->arr[stack_a->count - 1]);
	
	check_if_sorted(stack_a);
	*/


	/*CHECKING IF POP WORKS
	pop_element(stack_b, stack_a);

	printf("STACK_A\n");	
	i = stack_a->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_a->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_a->arr[stack_a->count - 1]);


	printf("STACK_B\n");	
	i = stack_b->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack_b->arr[i]);
		i--;
	}
	printf("TOP of the stack : %d\n", stack_b->arr[stack_b->count - 1]);
	
	check_if_sorted(stack_b);
	*/
	
}
