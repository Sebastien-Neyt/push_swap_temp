/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <sneyt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:30:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/07/04 18:33:18 by sneyt            ###   ########.fr       */
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
	int	*chunks;
	int	chunk_count;
	int	chunk_number;
	char name;
}	t_stack;

//UTILS/////////////////////////////////////////////////////////////////////////////
void	visualize_stack(t_stack *stack)
{
	int	i;

	i = stack->count - 1;
	while (i >= 0)
	{
		printf("          [ %d ]\n", stack->arr[i]);
		i--;
	}
	//printf(CYAN"\n###INFO ABOUT THE STACK###\n");
	printf(CYAN"\n    ----[STACK_%c]----\n", stack->name);
	printf("TOP of the stack : %d\n", stack->arr[stack->count - 1]);
	printf("Count of the stack : %d\n", stack->count);
   	printf("Size of the stack: %d\n\n---------------------------\n"RESET_COLOR, stack->size);
}

void	visualize_chunks(t_stack *stack)
{
	int	i;

	i = stack->chunk_count - 1;
	while (i >= 0)
	{
		printf("          [ %d ]\n", stack->chunks[i]);
		i--;
	}
	printf("Chunk_count of the chunksstack : %d\n", stack->chunk_count);
	printf("Chunk_number of the chunksstack : %d\n", stack->chunk_number);
	printf("---------------------------------------------------\n");
}

void	set_chunks(t_stack *stack, int	sizeofchunk)
{
	int	i;
	i = 0;
	while (i < sizeofchunk)
	{
		stack->chunks[stack->chunk_count] = stack->chunk_number;
		stack->chunk_count++;
		i++;
	}
	stack->chunk_number++;
}

int	count_chunk_size(t_stack *stack)
{
	int	i;
	int x;
	x = 0;
	i = stack->chunk_count - 1;
	//printf(YELLOW"###chunk_number == %d######################\n"RESET_COLOR, stack->chunk_number);
	if (stack->chunk_count == 0)
		return (0);
	//else if (stack->chunk_count == 1)
	//{
		//stack->chunk_number--;
//		return (1);
//	}
	else if (stack->chunk_number != 0)
	{	
		while (stack->chunk_number - 1 == stack->chunks[i] && i >= 0)
		{
		
			//printf("%d \n", stack->chunks[i]);
			i--;
			x++;
		}
		stack->chunk_number--;
		return (x);
	}
	else
		return (i + 1);
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
	stack->chunk_count = 0;
	stack->arr = malloc(sizeof(int) * stack->size);
	if (!stack->arr)
		return (0);
	stack->chunks = malloc(sizeof(int) * stack_a->size);
	if (!stack->chunks)
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
	stack->chunks = malloc(sizeof(int) * size);
	if (!stack->chunks)
		return (0);
	i = 1;
	stack->count = 0;
	stack->chunk_count = 0;
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
	stack->chunks = malloc(sizeof(int) * stack->size);
	if (!stack->chunks)
		return (0);
 	i = 0;
	stack->count = 0;
	stack->chunk_count = 0;
	stack->name = 'a';
	stack->size = size;
	while (i < size)
	{
		push(stack, ft_atoi(argv[i]));
		i++;
	}
	return (stack);
}

int	check_if_sorted_2(t_stack *stack)
{
	int	i;

	i = stack->chunk_count - 1;
	if (stack->chunks[i] > stack->chunks[i - 1])
		return (1);
	return (0);
}

int	check_if_sorted(t_stack *stack)
{
	int	i;
	
	i = 0;
	if (stack->name == 'a')
	{
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
	else
	{
		while (i < stack->count - 1)
		{
			if (stack->arr[i] > stack->arr[i + 1])
			{
				printf(RED"\n[The stack is NOT sorted]\n\n"RESET_COLOR);
				return (0);
			}
			i++;
		}
		printf(GREEN"\n[The stack is sorted!]\n\n"RESET_COLOR);
		return (1);
	}
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


void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	int	i_a;
	int	top;


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


void	check_top(t_stack *stack_a, t_stack *stack_b, int midvalue)
{
	int	i;
	i = stack_a->count - 1;
	while (midvalue > stack_a->arr[i] || i == 0)
	{
		pop_element(stack_b, stack_a);
		i--;
	}
}

void	check_bottom(t_stack *stack_a, t_stack *stack_b, int midvalue)
{
	while (midvalue > stack_a->arr[0])
	{
		reverse_reversed(stack_a);
		pop_element(stack_b, stack_a);
	}
}

int copy_arr(int *temp, t_stack *stack_a)
{
	int	i;
	
	i = 0;
	temp = malloc(sizeof(int) * stack_a->count);
	if (!temp)
		return (0);
	while (i < stack_a->count)
	{
		temp[i] = stack_a->arr[i];
		i++;
	}
	return (1);
}

int	find_midpoint_chunk(t_stack *stack, int chunksize)
{
	int	temp[chunksize];
	int	value;
	int	i;
	int	a = 0;
	int x = 0;
	i = stack->count - 1;
	//printf("this is the CHUNKSIZE; %d\n", chunksize);
	while (x < chunksize)
	{
		temp[x] = stack->arr[i];
		i--;
		x++;
	}
	printf("%d %d %d\n", temp[0], temp[1], temp[2]);	
	
	x = chunksize;
	
	while (a < x)
	{
		i = 0;
		while (i < x - 1)
		{
			if (temp[i] > temp[i + 1])
			{
				value = temp[i + 1];
				temp[i + 1] = temp[i];
				temp[i] = value;
			}
			i++;
		}
		a++;
	}
	value = temp[chunksize / 2 ];
	printf("%d %d %d %d %d %d \n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);	
	return (value);
}

int		find_midpoint(t_stack *stack_a)
{
	int	temp[stack_a->count];
	int	i;
	int	count = 0;
	int x = stack_a->count;
	int	tmp;

	//making a copy of the array
	int	y = 0;
	while (y < stack_a->count)
	{
		temp[y] = stack_a->arr[y];
		y++;
	}
	
	while (count < x)
	{
		i = 0;
		while (i < x - 1) 
		{
			if (temp[i] > temp[i + 1])
			{
				tmp = temp[i + 1];
				temp[i + 1] = temp[i];
				temp[i] = tmp;
			}
			i++;
		}
		count++;
	}

	tmp = temp[stack_a->count / 2];
	return (tmp);
}

int	check_if_smaller(t_stack *stack, int midvalue)
{
	int	i = 0;

	while (i < stack->count)
	{
		if (stack->arr[i] == midvalue)
			return (1);
		i++;
	}
	return (0);
}

int		midpointsort(t_stack *stack_a, t_stack *stack_b)
{
	int midvalue;
	int	i;
	int	counter;
	int	initial_count;
	int status;
	
	status = 0;
	initial_count = stack_a->count;
	counter = 0;
	midvalue = find_midpoint(stack_a);
	printf("THIS IS THE MIDVALUE: %d\n", midvalue);
	//check_top(stack_a, stack_b, midvalue);
	//check_bottom(stack_a, stack_b, midvalue);
	
	while (counter < (initial_count / 2) || !check_if_smaller(stack_a, midvalue)) 
	{
		//checking top, if its bigger or equal we reverse it (only the when we have checked the botom)
		while (midvalue <= stack_a->arr[stack_a->count - 1] && status != 0)
		{
			reverse(stack_a);
			break ;
		}
		//as soon as its smaller, we pop
		while (midvalue > stack_a->arr[stack_a->count - 1])
		{
			pop_element(stack_b, stack_a);				
			counter++;
			//status = 1;
		}
		while (midvalue > stack_a->arr[0])
		{
			reverse_reversed(stack_a);
			pop_element(stack_b, stack_a);
			counter++;
		}
		status = 1;
	}
	return (counter);
}

void	restore_midpoint(t_stack *stack_a, t_stack *stack_b)
{
	int	chunksize;
	int midvalue;

	//visualize_chunks(stack_b);
	while (stack_b->chunk_count > 0)
	{
		chunksize = count_chunk_size(stack_b);
		printf("CHUNKSIZE: %d\n", chunksize);
		if (chunksize == 0)
			break ;
		else if (chunksize == 1)
			pop_element(stack_a, stack_b);
		else if (chunksize == 2)
		{
			if (check_if_sorted_2(stack_b))
				swap(stack_b);
			pop_element(stack_a, stack_b);
			pop_element(stack_a, stack_b);
		}
		else
		{
			midvalue = find_midpoint_chunk(stack_b, chunksize);
			printf("MIDVALUE: %d\n", midvalue);
		
			/*
			pop_element(stack_a, stack_b);
			reverse(stack_b);
			pop_element(stack_a, stack_b);
			reverse_reversed(stack_b);
			pop_element(stack_a, stack_b);
			*/

			//DON'T FORGET TO CHECK IF ITS NOT THE LAST CHUNK, YOU HAVE TO COUNT THE Ra's and rra again.
			visualize_stack(stack_a);
			visualize_stack(stack_b);

		}
		visualize_chunks(stack_b);
		//printf(RED"chunk_count : %d ### and chunksize : %d\n"RESET_COLOR, stack_b->chunk_count, chunksize);
		stack_b->chunk_count -= chunksize;
		//printf(RED"chunk_count : %d ### and chunksize : %d\n"RESET_COLOR, stack_b->chunk_count, chunksize);
		printf("######################################################################################\n");
	}

	//	chunksize = count_chunk_size(stack_b);
	//	printf("CHUNKSIZE: %d\n", chunksize);
		//else
	//	{
	//	midvalue = find_midpoint_chunk(stack_b, chunksize);
	//	printf("MIDVALUE: %d\n", midvalue);
		/*
		chunksize = count_chunk_size(stack_b);
		printf("CHUNKSIZE: %d\n", chunksize);
		midvalue = find_midpoint_chunk(stack_b, chunksize);
		printf("MIDVALUE: %d\n", midvalue);
		*/
	//	}	

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
	int size_of_chunk;
	stack_b->chunk_number = 0;
	while (stack_a->count > 2)
	{
		size_of_chunk = midpointsort(stack_a, stack_b);
		set_chunks(stack_b, size_of_chunk);
		//stack_b->chunk_number++;
	}
	//sort_three(stack_a);
		
	//visualize_chunks(stack_b);
	visualize_stack(stack_a);
	visualize_stack(stack_b);
	if(!check_if_sorted(stack_a))
		swap(stack_a);
	//printf("%d\n", find_midpoint(stack_a));
	printf(GREEN"OPERATIONS : %d\n"RESET_COLOR, operations);
	restore_midpoint(stack_a, stack_b);	
	//visualize_chunks(stack_b);
	visualize_stack(stack_a);
	visualize_stack(stack_b);
	/*
	printf("this is the first chunksize %d\n", count_chunk_size(stack_b));
	printf("this is the second chunksize %d\n", count_chunk_size(stack_b));
	printf("this is the third chunksize %d\n", count_chunk_size(stack_b));
	*/

	// stack for testing : 11 8 1 4 7 9 6 10 12 5 3 2
}


