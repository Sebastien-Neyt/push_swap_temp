/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:30:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/07/02 13:18:34 by sneyt            ###   ########.fr       */
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

int	operations = 0;


typedef struct	s_stack{
	int	size;
	int	count;
	int	*arr;
	char name;
}	t_stack;

//UTILS/////////////////////////////////////////////////////////////////////////////
void	visualize_stack(t_stack *stack)
{
	int	i;

	i = stack->count - 1;
	while (i >= 0)
	{
		printf("[%d]\n", stack->arr[i]);
		i--;
	}
	printf(CYAN"\n###INFO ABOUT THE STACK###\n");
	printf("--[STACK_%c]--\n", stack->name);
	printf("TOP of the stack : %d\n", stack->arr[stack->count - 1]);
	printf("Count of the stack : %d\n", stack->count);
   	printf("Size of the stack: %d\n\n---------------------------\n"RESET_COLOR, stack->size);
}

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
	stack->name = 'b';
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
	stack->name = 'a';
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
	stack->name = 'a';
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
	while (i < stack->count - 1)
	{
		if (stack->arr[i] < stack->arr[i + 1])
		{
			printf(RED"\n[The stack is NOT sorted]\n\n"RESET_COLOR);
			return (0);
		}
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
	printf(YELLOW"OPERATION -> s%c\n"RESET_COLOR, stack->name);
	operations++;
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
	printf(YELLOW"OPERATION -> rr%c\n"RESET_COLOR, stack->name);
	operations++;
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
	printf(YELLOW"OPERATION -> r%c\n"RESET_COLOR, stack->name);
	operations++;
}

void	pop_element(t_stack *stack_1, t_stack *stack_2)
{
	int	element;

	element = stack_2->arr[stack_2->count - 1];
	stack_2->count--;
	stack_1->arr[stack_1->count] = element;
	stack_1->count++;
	printf(YELLOW"OPERATION -> p%c\n"RESET_COLOR, stack_1->name);
	operations++;
}

///SORTING ALGORITHMS/////////////////////////////////////////////

void	sort_three(t_stack *stack)
{
	if (check_if_sorted(stack))
		return ;
	else if (stack->arr[2] > stack->arr[1] && stack->arr[1] < stack->arr[0]) 
	{	
		if(stack->arr[0] > stack->arr[2])
			swap(stack);
		else if (stack->arr[0] < stack->arr[2])
			reverse(stack);
	}
	else if (stack->arr[2] < stack->arr[1] && stack->arr[1] > stack->arr[0])
	{
		if (stack->arr[0] < stack->arr[2])
			reverse_reversed(stack);
		else
		{
			swap(stack);
			reverse(stack);
		}
	}
	else
	{
		swap(stack);
		reverse_reversed(stack);
	}
}

void	check_if_rev(t_stack *stack)
{
	int	i;

	i = 0;
	
}

void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	int	i_a;
	int	top;

	check_if_rev(stack_a);

	pop_element(stack_b, stack_a);
	pop_element(stack_b, stack_a);
	sort_three(stack_a);
	//sort stack b
	if (stack_b->arr[0] > stack_b->arr[1])
		swap(stack_b);
	
	pop_element(stack_a, stack_b);
	while (stack_b->count > 0 || stack_a->size == stack_a->count)
	{
		i_a = stack_a->count;
		top = stack_a->arr[i_a - 1];
		
		if (top < stack_a->arr[i_a - 2])
		{
			if (stack_a->size == stack_a->count)
				break;
		}	
		else if (top > stack_a->arr[0])
			reverse(stack_a);
		else if (top < stack_a->arr[2])
			swap(stack_a);
		else
		{
			swap(stack_a);
			if (!check_if_sorted(stack_a))
			{	
				reverse(stack_a);
				swap(stack_a);
				if (stack_a->arr[3] > stack_a->arr[2])
				{
					reverse(stack_a);
					swap(stack_a);
					reverse_reversed(stack_a);
				}
				reverse_reversed(stack_a);
			}
		}

		if (stack_a->size != stack_a->count)
			pop_element(stack_a, stack_b);	
	}
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
		printf(RED"ERROR: NO INPUT\n"RESET_COLOR);
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

	//checking for duplicates
	int	x = 0;
	int	y;
	while(x <= stack_a->size - 2)
	{
		y = stack_a->count - 1;
		while (y > x)
		{
			if (stack_a->arr[x] == stack_a->arr[y])
			{	
				printf(RED"ERROR: DUPLICATE FOUND!\n"RESET_COLOR);
				return (1);
			}
			y--;
		}
		x++;
	}

	visualize_stack(stack_a);
		
	// initializing stack_b
	stack_b = init_stack_b(stack_a);
	
	if (check_if_sorted(stack_a))
		exit(1);
	else if (stack_a->count == 5)
		sort_five(stack_a, stack_b);
	else if (stack_a->count == 3)
		sort_three(stack_a);
	visualize_stack(stack_a);
	visualize_stack(stack_b);
	check_if_sorted(stack_a);
	printf(GREEN"OPERATIONS : %d\n"RESET_COLOR, operations);

}
