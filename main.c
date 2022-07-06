/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <sneyt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:30:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/07/06 11:49:48 by sneyt            ###   ########.fr       */
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
	int  from_bottom;
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
	//printf("Chunk_count of the chunksstack : %d\n", stack->chunk_count);
	//printf("Chunk_number of the chunksstack : %d\n", stack->chunk_number);
	//printf("---------------------------------------------------\n");
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
	
	if (stack->chunk_count == 0)
		return (0);
	else if (stack->chunk_number != 0)
	{	
		while (stack->chunk_number - 1 == stack->chunks[i] && i >= 0)
		{
		
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
	stack->from_bottom = 0;
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
	stack->from_bottom = 0;
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
	stack->from_bottom = 0;
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
				//printf(RED"\n[The stack is NOT sorted]\n\n"RESET_COLOR);
				return (0);
			}
			i++;
		}
		//printf(GREEN"\n[The stack is sorted!]\n\n"RESET_COLOR);
		return (1);
	}
	else
	{
		while (i < stack->count - 1)
		{
			if (stack->arr[i] > stack->arr[i + 1])
			{
				//printf(RED"\n[The stack is NOT sorted]\n\n"RESET_COLOR);
				return (0);
			}
			i++;
		}
		//printf(GREEN"\n[The stack is sorted!]\n\n"RESET_COLOR);
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
int find_midpoint_chunk2(t_stack *stack, int resting_chunksize)
{
	int	temp[resting_chunksize];
	int	value;
	int	i;
	int	a = 0;
	int x = 0;
	i = stack->count - 1;
	//printf("this is the CHUNKSIZE; %d\n", chunksize);
	while (x < resting_chunksize)
	{
		temp[x] = stack->arr[i];
		i--;
		x++;
	}
	//printf("%d %d %d\n", temp[0], temp[1], temp[2]);	
	
	x = resting_chunksize;
	
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
	value = temp[resting_chunksize / 2 ];
	//printf("%d %d %d %d %d %d \n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);	
	return (value);
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
	//printf("%d %d %d\n", temp[0], temp[1], temp[2]);	
	
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
	//printf("%d %d %d %d %d %d \n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);	
	return (value);
}

int	check_top2(t_stack *stack)
{
	if (stack->arr[stack->count - 1] > stack->arr[stack->count - 2])
		return (1);
	return (0);
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

int	check_if_bigger(t_stack *stack_b, int midvalue, int chunksize)
{
	int	i = 0;
	while (i < chunksize)  // 0 < 2
	{
		if (stack_b->arr[stack_b->count - 1 - i] > midvalue)
		{
			//printf("found bigger one!!\n");
			return (1);
		}
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
	//printf("THIS IS THE MIDVALUE: %d\n", midvalue);
	visualize_stack(stack_a);
	visualize_stack(stack_b);
	//printf("***********************************************************************************\n");
	//check_top(stack_a, stack_b, midvalue);
	//check_bottom(stack_a, stack_b, midvalue);
	
	while (counter < (initial_count / 2) || !check_if_smaller(stack_a, midvalue)) 
	{
		//usleep(100000);
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

int		check_top_second(int midvalue, t_stack *stack_b, int status)
{
	int rb_count;

	rb_count = 0;
	while (midvalue >= stack_b->arr[stack_b->count - 1] && status != 0 && stack_b->count > 0)
	{
		//adding counter to keep  track
		if (stack_b->chunk_number != 0)
			rb_count++;
		reverse(stack_b);
		break ;
	}
	return (rb_count);
}


int check_top_first(int midvalue , t_stack *stack_a, t_stack *stack_b, int chunksize)
{
	int counter;

	counter = 0;
	while (midvalue < stack_b->arr[stack_b->count - 1] && counter <= (chunksize / 2) && stack_b->count > 0)
	{
		visualize_stack(stack_b);
		if (!check_top2(stack_b))
			swap(stack_b);
		pop_element(stack_a, stack_b);				
		counter++;
		printf("COUNTER++\n");
		stack_b->chunk_count--;
		visualize_stack(stack_b);
	}
	return (counter);
}

int	check_bottom_chunk(int midvalue, t_stack *stack_a, t_stack *stack_b, int chunksize)
{
	int counter = 0;
	int x = 1;
	
	while (midvalue < stack_b->arr[stack_b->chunk_count - chunksize + 1] && stack_b->count > 0)
	{
		printf("MIDVALUE ; %d\n", midvalue);
		printf("CHUNKSIZE ; %d\n", chunksize);
		printf("stack_b chunkcount ; %d\n", stack_b->chunk_count);
		int p = 0;
		while (p < chunksize - x)
		{
			reverse(stack_b);
			p++;
		}
		
		pop_element(stack_a, stack_b);
		stack_b->chunk_count--;
		x++;
		counter++;
		
		while (p > 0)
		{
			reverse_reversed(stack_b);
			p--;
		}
	}
	return (counter);
}

int	find_biggest(t_stack *stack_b, int chunksize, int limit)
{
	int i;
	int x;
	int value;
	int from_bottom = stack_b->from_bottom;
	i = 1;
	value = stack_b->arr[stack_b->count - 1];
	x = 1;
	//printf("value : %d, limit : %d, chunksize : %d , frombottom : %d, stackcount: %d\n", value, limit, chunksize, from_bottom, stack_b->count);
	while ((stack_b->count - i - from_bottom) >= limit)
	{
		if (stack_b->arr[stack_b->count - i] > value)
		{
			value = stack_b->arr[stack_b->count - i];
			x = i;
			//printf("value => %d\n", value);
		}
		i++;
	}
	while (from_bottom > 0)
	{
		int a = 0;
		if (from_bottom > stack_b->count)
			a = 1;
		if (stack_b->arr[from_bottom - 1 - a] > value)
		{
			value = stack_b->arr[from_bottom - 1 - a];
			x = -from_bottom - a;
			//printf("value bottom => %d\n", value);
		}
		from_bottom--;
	}
	return (x);
}

void	chunk_sort(t_stack *stack_a, t_stack *stack_b)
{
	// depending on the chunksize, we look for the biggest element inside the chunk and rotate/pop it
	int	chunksize;
	int limit;
	int rotates;
	int i_biggest;
	int from_bottom;
	
	chunksize = count_chunk_size(stack_b);
	limit = stack_b->chunk_count - chunksize;
	//printf("chunksize : %d || limit : %d\n", chunksize, limit);
	
	while (chunksize > 0)
	{
		//printf("#######################################################\n");
		if (chunksize == 1 && stack_b->from_bottom == 0)
		{
			pop_element(stack_a, stack_b);
			chunksize--;
			stack_b->chunk_count--;
			break ;
		}
		i_biggest = find_biggest(stack_b, chunksize, limit); //if 1, means it's the top of the stack
		//printf("i_biggest %d\n", i_biggest);
		
		rotates = i_biggest - 1;
		//printf("rotates : %d\n", rotates);
		if (stack_b->from_bottom == 0)
		{
			while (i_biggest > 1)
			{
				reverse(stack_b);
				stack_b->from_bottom++;
				i_biggest--;	//can check the bottom of the stack for bigger ones and reverse rotate if that's faster
								// if it's the final chunk, we should check from the bottom aswell
			}
			pop_element(stack_a, stack_b);
			chunksize--;
			stack_b->chunk_count--;
		}
		
		i_biggest = find_biggest(stack_b, chunksize, limit);
		//printf("i_biggest second : %d\n", i_biggest);
		if (i_biggest < 0)
		{
			while (i_biggest < 0)
			{
				reverse_reversed(stack_b);
				stack_b->from_bottom--;
				i_biggest++;
			}
			pop_element(stack_a, stack_b);
			chunksize--;
			stack_b->chunk_count--;
		}
		
		if (i_biggest > 0)
		{
			while (i_biggest > 1)
			{
				reverse(stack_b);
				stack_b->from_bottom++;
				i_biggest--;	//can check the bottom of the stack for bigger ones and reverse rotate if that's faster
			}
			pop_element(stack_a, stack_b);
			chunksize--;
			stack_b->chunk_count--;
		}
		//visualize_stack(stack_a);
		//visualize_stack(stack_b);
		/*
		while (rotates > 0)
		{				
			reverse_reversed(stack_b);
			stack_b->from_bottom--;
			rotates--;
		}
		*/
		//printf("THIS IS THE FROM BOTTOM: %d \n", stack_b->from_bottom);
	}
		
}

void	restore_midpoint(t_stack *stack_a, t_stack *stack_b)
{
	int	chunksize;
	int midvalue;
	int status; 
	int rb_count;
	int	limit;
	int counter;
	//visualize_chunks(stack_b);
	while (stack_b->chunk_count > 0)
	{
		status = 0;
		rb_count = 0;
		chunksize = count_chunk_size(stack_b);
		
		
		printf("CHUNKSIZE: %d\n", chunksize);
		limit = stack_b->chunk_count - chunksize;
		printf("THIS IS LIMIT: %d\n", limit);
		if (chunksize == 0)
			break ;
		else if (chunksize == 1)
		{
			pop_element(stack_a, stack_b);
			stack_b->chunk_count--;
		}	
		else if (chunksize == 2)
		{
			if (check_if_sorted_2(stack_b))
				swap(stack_b);
			pop_element(stack_a, stack_b);
			pop_element(stack_a, stack_b);
			stack_b->chunk_count -= 2;
		}
		else
		{
			midvalue = find_midpoint_chunk(stack_b, chunksize);
			printf("MIDVALUE: %d\n", midvalue);
			counter = 0;
			//while (stack_b->chunk_count > 2)
			//if (stack_b->chunk_count > 2)
			//	while (limit <= stack_b->chunk_count && check_if_bigger(stack_b, midvalue, chunksize - counter))
			//	{
			printf("status : %d\n", status);
			printf("counter : %d\n", counter);
			//limit < stack_b->chunk_count
			
			while ((limit <= stack_b->chunk_count) && check_if_bigger(stack_b, midvalue, chunksize - counter) && stack_b->count > 0) 
					//||(limit < stack_b->chunk_count && check_if_bigger(stack_b, midvalue, chunksize - counter)))
			{
				while (check_if_bigger(stack_b, midvalue, chunksize - counter) && stack_b->count > 0)
				{
					
					rb_count += check_top_second(midvalue, stack_b, status);
				
					counter += check_top_first(midvalue, stack_a, stack_b, chunksize);
				
					counter += check_bottom_chunk(midvalue, stack_a, stack_b, chunksize);
					status = 1;
					printf("counter : %d\n", counter);
					printf("chinksize : %d\n", chunksize);
					printf("midvalue %d\n", midvalue);
					printf("stack b count %d\n", stack_b->count);
				}
				//printf("counter : %d\n", counter);
				//printf("chinksize : %d\n", chunksize);
				
				/*checking for 2 left in chunk
				if (chunksize - counter < 3 )
				{
					if (stack_b->arr[stack_b->count - 1] < stack_b->arr[stack_b->count - 2])
						swap(stack_b);
					pop_element(stack_a, stack_b);
					pop_element(stack_a, stack_b);
					counter += 2;
				}
				*/
				//status = 1;
				visualize_stack(stack_a);
				visualize_stack(stack_b);
				
				//if ()
				//{
					while (rb_count != 0)
					{
						reverse_reversed(stack_b);
						rb_count--;
					}
					visualize_stack(stack_b);
				//}
				
				if (chunksize - counter < 3)
				{
					if (stack_b->count == 1)
						{
							pop_element(stack_a, stack_b);
							return ;
						}
					if (stack_b->arr[stack_b->count - 1] < stack_b->arr[stack_b->count - 2])
						swap(stack_b);
					pop_element(stack_a, stack_b);
					pop_element(stack_a, stack_b);
					stack_b->chunk_count -= 2;
					counter += 2;
				}
				visualize_stack(stack_a);
				visualize_stack(stack_b);
				
				midvalue = find_midpoint_chunk2(stack_b, chunksize - counter);
				printf("[ new midvalue: %d ]\n", midvalue);
				
				/*
				if (stack_b->count == 1 && check_if_sorted(stack_a))
				{
					pop_element(stack_a, stack_b);
					break ;
				}
				*/
			}
			/*
			while (rb_count != 0)
			{
				reverse_reversed(stack_b);
				rb_count--;
			}
			*/
			printf("[ Chunk count: %d ]\n", stack_b->chunk_count);
			printf("[ Chunk number: %d ]\n", stack_b->chunk_number);
			printf("[ count: %d ]\n", stack_b->count);	
			printf("[ chunksize: %d ]\n", chunksize);
			printf("[ counter: %d ]\n", counter);
			//midvalue = find_midpoint_chunk2(stack_b, chunksize - counter);
			//printf("[ new midvalue: %d ]\n", midvalue);
		}



		visualize_chunks(stack_b);
		printf(RED"chunk_count : %d ### and chunksize : %d\n"RESET_COLOR, stack_b->chunk_count, chunksize);
				//stack_b->chunk_count -= counter;
		printf(RED"chunk_count : %d ### and chunksize : %d\n"RESET_COLOR, stack_b->chunk_count, chunksize);	
		
	}
	//printf(RED"chunk_count : %d ### and chunksize : %d\n"RESET_COLOR, stack_b->chunk_count, chunksize);
	printf("######################################################################################\n");
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
	
	//visualize_stack(stack_a);
		
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
	//visualize_stack(stack_a);
	//visualize_stack(stack_b);
	if(!check_if_sorted(stack_a))
		swap(stack_a);
	//printf("%d\n", find_midpoint(stack_a));
	//printf(GREEN"OPERATIONS : %d\n"RESET_COLOR, operations);
	
	
	while (stack_b->count > 0)
		chunk_sort(stack_a, stack_b);
	

	
	//restore_midpoint(stack_a, stack_b);	
	
	
	//visualize_chunks(stack_b);
	
	//visualize_stack(stack_a);
	//visualize_stack(stack_b);
	if(check_if_sorted(stack_a))
		printf(GREEN"THE STACK IS SORTED!\n"RESET_COLOR);
	
	printf(GREEN"OPERATIONS : %d\n"RESET_COLOR, operations);
	/*
	printf("this is the first chunksize %d\n", count_chunk_size(stack_b));
	printf("this is the second chunksize %d\n", count_chunk_size(stack_b));
	printf("this is the third chunksize %d\n", count_chunk_size(stack_b));
	*/

	// stack for testing : 11 8 1 4 7 9 6 10 12 5 3 2
}


