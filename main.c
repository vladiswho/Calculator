#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Braces(char* fixed, int count);

void Insert(int position, char* array, char* result, int len, int count, int count_expression)
{
	int i = 0;
	char* fixed = NULL;
	int count_result = 0;
	fixed = (char*)malloc(sizeof(char) * 1);
	while (i < position)
	{
		fixed[count_result] = array[i];
		count_result++;
		char* error = (char*)realloc(fixed, sizeof(char) * (count_result + 1));
		if (error != NULL) fixed = error;
		error = NULL;
		free(error);
		i++;
	}
	int j = 0;
	while (j < count)
	{
		fixed[count_result] = result[j];
		count_result++;
		char* error = (char*)realloc(fixed, sizeof(char) * (count_result + 1));
		if (error != NULL) fixed = error;
		error = NULL;
		free(error);
		i++;
		j++;
	}
	while (j < count_expression)
	{
		i++;
		j++;
	}
	while (i < len)
	{
		fixed[count_result] = array[i];
		count_result++;
		char* error = (char*)realloc(fixed, sizeof(char) * (count_result + 1));
		if (error != NULL) fixed = error;
		error = NULL;
		free(error);
		i++;
	}
	char* error = (char*)realloc(fixed, sizeof(char) * (count_result));
	if (error != NULL) fixed = error;
	error = NULL;
	free(error);
	Braces(fixed, count_result);
	fixed = NULL; free(fixed);
}

void Mul(char* first, char* second, int one, int two, char* array, int len, int position, char sign)
{
	if (first[1] == '0' && one == 2 || second[1] == '0' && two == 2)
	{
		char* result = NULL;
		result = (char*)malloc(sizeof(char) * 2);
		result[0] = sign; result[1] = '0';
		Insert(position, array, result, len, 2, one + two + 1);
		result = NULL; free(result);
		return 0;
	}
	int count_expression = one + two + 1;
	int count = 0;
	int remains = 0;
	char* result = NULL;
	result = (char*)malloc(sizeof(char) * 1);
	result[0] = '0';
	one--; two--;
	int index, first_digit, second_digit;
	for (int i = one; i > 0; i--)
	{
		index = one - i;
		first_digit = first[i] - '0';
		int number;
		for (int j = two; j > 0; j--)
		{
			second_digit = second[j] - '0';
			number = (result[index] - '0' + first_digit * second_digit + remains);
			result[index] = number % 10 + '0';
			remains = number / 10;
			index++;
			if (index > count)
			{
				count++;
				char* error = (char*)realloc(result, sizeof(char) * (count + 1));
				if (error != NULL) result = error;
				error = NULL;
				free(error);
				result[index] = '0';
			}
		}
		if (remains != 0)
		{
			result[index] = number / 10 + '0';
			remains = 0;
		}
	}
	if (result[count] == '0') result[count] = sign;
	else
	{
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		result[count] = sign;
	}
	count++;
	if (result != NULL)
	{
		for (int i = 0; i < count / 2; i++)
		{
			char symbol = result[i];
			result[i] = result[count - i - 1];
			result[count - i - 1] = symbol;
		}
	}
	Insert(position, array, result, len, count, count_expression);
	result = NULL; free(result);
}

void Div(char* first, char* second, int one, int two, char* array, int len, int position, char sign)
{
	int count_expression = one + two + 1;
	int result_int = 0;
	int f = 1, i;
	int const_two = two;
	if (two == 2 && second[1] == '0')
	{
		printf_s("ERROR DIV!");
		return 0;
	}
	while (f == 1)
	{
		if (one < two)
		{
			f = 0;
			break;
		}
		else if (one == two)
		{
			for (i = 1; i < one; i++)
			{
				if (first[i] > second[i])
				{
					f = 1;
					break;
				}
				if (first[i] < second[i])
				{
					f = 0;
					break;
				}
			}
		}
		if (f == 1)
		{
			int count_expression_result = one + two;
			int count = 0;
			int remains = 0; // îñòàòîê 
			char* result = NULL;
			result = (char*)malloc(sizeof(char) * 1);
			one--; two--;
			while (two > 0)
			{
				int first_digit = first[one] - '0';
				int second_digit = second[two] - '0';
				int result_digit = first_digit - second_digit;
				if (result_digit < 0)
				{
					int i = one - 1;
					for (i; i >= 0; i--)
					{
						if (first[i] != '0') break;
						else first[i] = '9';
					}
					first[i] -= 1;
					result_digit += 10;
				}
				result[count] = result_digit + '0';
				count++;
				char* error = (char*)realloc(result, sizeof(char) * (count + 1));
				if (error != NULL) result = error;
				error = NULL;
				free(error);
				one--;
				two--;
			}
			while (one > 0)
			{
				result[count] = first[one];
				count++;
				char* error = (char*)realloc(result, sizeof(char) * (count + 1));
				if (error != NULL) result = error;
				error = NULL;
				free(error);
				one--;
			}
			count--;
			while (result[count] == '0')
			{
				count--;
			}
			count += 2;
			if (count == 1) count++;
			char* resultOK = NULL;
			resultOK = (char*)malloc(sizeof(char) * count);
			resultOK[0] = sign;
			if (resultOK != NULL && result != NULL)
			{
				int j = 1;
				for (int i = count - 2; i >= 0; i--)
				{
					resultOK[j] = result[i];
					j++;
				}
			}
			first = (char*)malloc(sizeof(char) * count);
			first = resultOK;
			resultOK = NULL; free(resultOK);
			result = NULL; free(result);
			one = count;
			two = const_two;
			result_int++;
			if (result_int > 1000000)
			{
				printf_s("MEMORY OVERFLOW! ADD");
				return 0;
			}
		}
	}
	int konechnaya = 1;
	char* NuVse = NULL;
	NuVse = (char*)malloc(sizeof(char) * 1);
	NuVse[0] = sign;
	if (result_int == 0)
	{
		char* error = (char*)realloc(NuVse, sizeof(char) * (konechnaya + 1));
		if (error != NULL) NuVse = error;
		error = NULL;
		free(error);
		*(NuVse + konechnaya) = '0';
		konechnaya++;
	}
	else
	{
		char* flipped = NULL;
		flipped = (char*)malloc(sizeof(char) * 1);
		int count = 0;
		while (result_int != 0)
		{
			char* error = (char*)realloc(flipped, sizeof(char) * (count + 1));
			if (error != NULL) flipped = error;
			error = NULL;
			free(error);
			*(flipped + count) = result_int % 10 + '0';
			count++;
			result_int /= 10;
		}
		konechnaya = count + 1;
		char* error = (char*)realloc(NuVse, sizeof(char) * konechnaya);
		if (error != NULL) NuVse = error;
		error = NULL;
		free(error);
		i = 1;
		while (count != 0)
		{
			*(NuVse + i) = *(flipped + count - 1);
			count--;
			i++;
		}
		flipped = NULL; free(flipped);
	}
	Insert(position, array, NuVse, len, konechnaya, count_expression);
	NuVse = NULL; free(NuVse);
}

void Add(char* first, char* second, int one, int two, char *array, int len, int position, char sign)
{
	int count_expression = one + two;
	int count = 0;
	int remains = 0; // îñòàòîê 
	char *result = NULL;
	result = (char*)malloc(sizeof(char) * 1);
	one--; two--;
	while (one > 0 && two > 0)
	{
		int first_digit = first[one] - '0';
		int second_digit = second[two] - '0';
		result[count] = (first_digit + second_digit + remains) % 10 + '0';
		remains = (first_digit + second_digit + remains) / 10;
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		one--;
		two--;
	}
	while (one > 0)
	{
		int first_digit = first[one] - '0';
		result[count] = (first_digit + remains) % 10 + '0';
		remains = (first_digit + remains) / 10;
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		one--;
	}
	while (two > 0)
	{
		int second_digit = second[two] - '0';
		result[count] = (second_digit + remains) % 10 + '0';
		remains = (second_digit + remains) / 10;
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		two--;
	}
	if (remains != 0)
	{
		result[count] = remains + '0';
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
	}
	result[count] = sign;
	count++;
	if (result != NULL)
	{
		for (int i = 0; i < count / 2; i++)
		{
			char symbol = result[i];
			result[i] = result[count - i - 1];
			result[count - i - 1] = symbol;
		}
	}
	Insert(position, array, result, len, count, count_expression);
	result = NULL; free(result);
}

void Sub(char* first, char* second, int one, int two, char* array, int len, int position, char sign)
{
	int count_expression = one + two;
	int count = 0;
	int remains = 0; // îñòàòîê 
	char* result = NULL;
	result = (char*)malloc(sizeof(char) * 1);
	one--; two--;
	while (two > 0)
	{
		int first_digit = first[one] - '0';
		int second_digit = second[two] - '0';
		int result_digit = first_digit - second_digit;
		if (result_digit < 0)
		{
			int i = one - 1;
			for (i; i >= 0; i--)
			{
				if (first[i] != '0') break;
				else first[i] = '9';
			}
			first[i] -= 1;
			result_digit += 10;
		}
		result[count] = result_digit + '0';
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		one--;
		two--;
	}
	while (one > 0)
	{
		result[count] = first[one];
		count++;
		char* error = (char*)realloc(result, sizeof(char) * (count + 1));
		if (error != NULL) result = error;
		error = NULL;
		free(error);
		one--;
	}
	count--;
	while (result[count] == '0')
	{
		count--;
	}
	count += 2;
	if (count == 1) count++;
	char* resultOK = NULL;
	resultOK = (char*)malloc(sizeof(char) * count);
	resultOK[0] = sign;
	if (resultOK != NULL && result != NULL)
	{
		int j = 1;
		for (int i = count - 2; i >= 0; i--)
		{
			resultOK[j] = result[i];
			j++;
		}
	}
	Insert(position, array, resultOK, len, count, count_expression);
	result = NULL; free(result);
	resultOK = NULL; free(resultOK);
}

void MaxMin(char* first, char* second, int one, int two, char* array, int len, int position)
{
	if (one > two) Sub(first, second, one, two, array, len, position, '+');
	if (two > one) Sub(second, first, two, one, array, len, position, '-');
	if (two == one)
	{
		int f = -1;
		for (int i = 1; i < one; i++)
		{
			if (first[i] > second[i])
			{
				f = 1;
				break;
			}
			else if (first[i] < second[i])
			{
				f = 2;
				break;
			}
		}
		if (f == -1 || f == 1) Sub(first, second, one, two, array, len, position, '+');
		else Sub(second, first, two, one, array, len, position, '-');
	}
}

void Order(char *array, int position, int count) // Ïîðÿäîê âûïîëíåíèÿ äåéñòâèé â íàéäåííîé ñêîáêå
{
	int i = position + 1;
	int number_one = i;
	int number_two = 0;
	char sign = 'f';
	while (array[i] != ')')
	{
		if (array[i] == '*' || array[i] == '/')
		{
			sign = array[i];
			if (number_two == 0) number_two = i + 1;
			else
			{
				number_one = number_two;
				number_two = i + 1;
			}
			break;
		}
		else if (array[i] == '+' || array[i] == '-')
		{
			sign = array[i];
			if (number_two == 0) number_two = i;
			else
			{
				number_one = number_two;
				number_two = i;
			}
		}
		i++;
	}
	if (number_one != number_two)
	{
		char* first = NULL;
		char* second = NULL;
		int count_one = 1;
		first = (char*)malloc(sizeof(char) * 2);
		first[0] = array[number_one];
		number_one++;
		while (array[number_one] != '+' && array[number_one] != '-' && array[number_one] != '*' && array[number_one] != '/' && array[number_one] != ')')
		{
			if (first != NULL)
			{
				*(first + count_one) = array[number_one];
				count_one++;
				char* error = (char*)realloc(first, sizeof(char) * (count_one + 1));
				if (error != NULL) first = error;
			}
			number_one++;
		}
		int count_two = 1;
		second = (char*)malloc(sizeof(char) * 2);
		second[0] = array[number_two];
		number_two++;
		while (array[number_two] != '+' && array[number_two] != '-' && array[number_two] != '*' && array[number_two] != '/' && array[number_two] != ')')
		{
			if (second != NULL)
			{
				*(second + count_two) = array[number_two];
				count_two++;
				char* error = (char*)realloc(second, sizeof(char) * (count_two + 1));
				if (error != NULL) second = error;
			}
			number_two++;
		}
		char* error = (char*)realloc(first, sizeof(char) * count_one);
		if (error != NULL) first = error;
		error = NULL;
		free(error);
		error = (char*)realloc(second, sizeof(char) * count_two);
		if (error != NULL) second = error;
		error = NULL;
		free(error);
		if (first[0] == '+' && second[0] == '+' && sign != '*' && sign != '/') Add(first, second, count_one, count_two, array, count, number_one - count_one, '+');
		if (first[0] == '-' && second[0] == '-' && sign != '*' && sign != '/') Add(first, second, count_one, count_two, array, count, number_one - count_one, '-');
		if (first[0] == '+' && second[0] == '-' && sign != '*' && sign != '/') MaxMin(first, second, count_one, count_two, array, count, number_one - count_one);
		if (first[0] == '-' && second[0] == '+' && sign != '*' && sign != '/') MaxMin(second, first, count_two, count_one, array, count, number_one - count_one);
		if (sign == '*' && (first[0] == '-' && second[0] == '-' || first[0] == '+' && second[0] == '+')) 
			Mul(first, second, count_one, count_two, array, count, number_one - count_one, '+');
		if (sign == '*' && (first[0] == '+' && second[0] == '-' || first[0] == '-' && second[0] == '+')) 
			Mul(first, second, count_one, count_two, array, count, number_one - count_one, '-');
		if (sign == '/' && (first[0] == '-' && second[0] == '-' || first[0] == '+' && second[0] == '+'))
			Div(first, second, count_one, count_two, array, count, number_one - count_one, '+');
		if (sign == '/' && (first[0] == '+' && second[0] == '-' || first[0] == '-' && second[0] == '+'))
			Div(first, second, count_one, count_two, array, count, number_one - count_one, '-');
		first = NULL; free(first);
		second = NULL; free(second);
	}
	else
	{
		char* fixed = NULL;
		fixed = (char*)malloc(sizeof(char) * (count - 2));
		i = 0;
		while (i < position - 1)
		{
			if (fixed != NULL) fixed[i] = array[i];
			i++;
		}
		if (i != 0)
		{
			if (array[i] == array[i + 2])
			{
				fixed[i] = '+';
				i += 2;
				while (array[i + 1] != ')')
				{
					if (fixed != NULL) fixed[i - 1] = array[i + 1];
					i++;
				}
				i++;
				while (i + 1 != count)
				{
					if (fixed != NULL) fixed[i - 2] = array[i + 1];
					i++;
				}
				Braces(fixed, count - 3);
			}
			else if (array[i] != '*' && array[i] != '/')
			{
				fixed[i] = '-';
				i += 2;
				while (array[i + 1] != ')')
				{
					if (fixed != NULL) fixed[i - 1] = array[i + 1];
					i++;
				}
				i++;
				while (i + 1 != count)
				{
					if (fixed != NULL) fixed[i - 2] = array[i + 1];
					i++;
				}
				Braces(fixed, count - 3);
			}
			else
			{
				fixed[i] = array[i];
				i++;
				while (array[i + 1] != ')')
				{
					if (fixed != NULL) fixed[i] = array[i + 1];
					i++;
				}
				i++;
				while (i + 1 != count)
				{
					if (fixed != NULL) fixed[i - 1] = array[i + 1];
					i++;
				}
				Braces(fixed, count - 2);
			}
		}
		else
		{
			i++;
			while (array[i] != ')')
			{
				if (fixed != NULL) fixed[i - 1] = array[i];
				i++;
			}
			i++;
			while (i != count)
			{
				if (fixed != NULL) fixed[i - 2] = array[i];
				i++;
			}
			Braces(fixed, count - 2);
		}
		fixed = NULL; free(fixed);
	}
}

void Braces(char *fixed, int count)
{
	int braces = 0;
	int i;
	for (i = 0; i < count; i++)
	{
		if (fixed[i] == '(')
		{
			braces = i;
		}
		if (fixed[i] == ')')
		{
			for (int i = 0; i < count; i++) printf_s("%c", fixed[i]);
			printf_s("\n");
			Order(fixed, braces, count);
			break;
		}
	}
	if (fixed[0] != '(') for (i = 0; i < count; i++) printf_s("%c", fixed[i]);
}

void Input()
{
	char symbol;
	char *fixed = NULL;
	int count = 1;
	fixed = (char*)malloc(sizeof(char) * 2);
	if (fixed != NULL) *(fixed + count - 1) = '(';
	do
	{
		scanf_s("%c", &symbol, 1);
		if (symbol >= '0' && symbol <= '9' || symbol == '+' || symbol == '-' || 
			symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')') 
		{
			if (fixed != NULL)
			{
				/*if (symbol == '-' && *(fixed + count - 1) == '(')
				{
					*(fixed + count) = '+';
					count++;
					char* error = (char*)realloc(fixed, sizeof(char) * (count + 1));
					if (error != NULL) fixed = error;
					*(fixed + count) = '0';
					count++;
					error = (char*)realloc(fixed, sizeof(char) * (count + 1));
					if (error != NULL) fixed = error;
				}*/
				if (symbol == '(' && *(fixed + count - 1) == '(')
				{
					*(fixed + count) = '+';
					count++;
					char* error = (char*)realloc(fixed, sizeof(char) * (count + 1));
					if (error != NULL) fixed = error;
					error = NULL;
					free(error);
				}
				if (symbol >= '0' && symbol <= '9' && (*(fixed + count - 1) == '(' || *(fixed + count - 1) == '/' || *(fixed + count - 1) == '*'))
				{
					*(fixed + count) = '+';
					count++;
					char* error = (char*)realloc(fixed, sizeof(char) * (count + 1));
					if (error != NULL) fixed = error;
					error = NULL;
					free(error);
				}
				*(fixed + count) = symbol;
				count++;
				char* error = (char*)realloc(fixed, sizeof(char) * (count + 1));
				if (error != NULL) fixed = error;
				error = NULL;
				free(error);
			}
		}
	} while (symbol != '\n');
	if (fixed != NULL) *(fixed + count) = ')';
	count++;
	if (count > 2)
	{
		char* error = (char*)realloc(fixed, sizeof(char) * count);
		if (error != NULL)
		{
			fixed = error;
			Braces(fixed, count);
		}
		error = NULL;
		free(error);
	}
	else printf_s("ERROR Input!");
	fixed = NULL;
	free(fixed);
}

int main()
{
	Input();
	return 0;
}
