
#include "des_c_dll.h"

int initial_permutation_table[] =	{58,50,	42,	34,	26,	18,	10,	2,	60,	52,	44,	36,	28,	20,	12,	4,
									62,54, 46,38,	30,	22,	14,	6,	64,	56,	48,	40,	32,	24,	16,	8,
									57,49,	41,	33,	25,	17,	9,	1,	59,	51,	43,	35,	27,	19,	11,	3,
									61,53,	45,	37,	29,	21,	13,	5,	63,	55,	47,	39,	31,	23,	15,	7};

int p_permutation_table[32] = {16,	7,	20,	21,
							29,	12,	28,	17,
							1,	15,	23,	26,
							5,	18,	31,	10,
							2,	8,	24,	14,
							32,	27,	3,	9,
							19,	13,	30,	6,
							22,	11,	4,	25};

int expand_permutation_table[] = {32,	1,	2,	3,	4	,5,
									4,	5,	6,	7,	8,	9,
									8,	9,	10,	11,	12,	13,
									12,	13,	14,	15,	16,	17,
									16,	17,	18,	19,	20,	21,
									20,	21,	22,	23,	24,	25,
									24,	25,	26,	27,	28,	29,
									28,	29,	30,	31,	32,	1};



int final_permutation_table[64] = {40,	8,	48,	16,	56,	24,	64,	32,	39,	7,	47,	15,	55,	23,	63,	31,
									38,6,	46,	14,	54,	22,	62,	30,	37,	5,	45,	13,	53,	21,	61,	29,
									36,4,	44,	12,	52,	20,	60,	28,	35,	3,	43,	11,	51,	19,	59,	27,
									34,2,	42,	10,	50,	18,	58,	26,	33,	1,	41,	9,	49,	17,	57,	25};


int pc_1[] = {57,	49,	41,	33,	25,	17,	9,
				1,	58,	50,	42,	34,	26,	18,
				10,2,	59,	51,	43,	35,	27,
				19, 11, 3,	60,	52,	44,	36,
				63, 55, 47,	39,	31,	23,	15,
				7,	62,	54,	46,	38,	30,	22,
				14, 6,	61,	53,	45,	37,	29,
				21, 13,	5,	28,	20,	12,	4};

int pc_2[] = {14,	17,	11,	24,	1,	5,
				3,	28,	15,	6,	21,	10,
				23,	19,	12,	4,	26,	8,
				16,	7,	27,	20,	13,	2,
				41,	52,	31,	37,	47,	55,
				30,	40,	51,	45,	33,	48,
				44,	49,	39,	56,	34,	53,
				46,	42,	50,	36,	29,	32};

int s1_table[][16] = {{14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7},
					{0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8},
					{4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0},
					{15, 12,8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13}};

int s2_table[][16] = {{15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10},
					{3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5},
					{0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15},
					{13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9}};

int s3_table[][16] = {{10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8},
					{13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1},
					{13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7},
					{1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12}};

int s4_table[][16] = {{7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15},
					{13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9},
					{10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4},
					{3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14}};

int s5_table[][16] = {{2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9},
					{14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6},
					{4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14},
					{11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3}};

int s6_table[][16] = {{12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11},
					{10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8},
					{9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6},
					{4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13}};

int s7_table[][16] = {{4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1},
					{13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6},
					{1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2},
					{6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12}};

int s8_table[][16] = {{13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7},
					{1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2},
					{7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8},
					{2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11}};



//Instructions to generate the next values of key
long long int generate_mask(int amount, int level)
{
	long long int value = 0x1; // 1 on 64th position
	int counter;
	
	/*We have to "rotate" the bits. First bit in algorithm is first from left ( the oldest ) */
	if (level == 1)
		amount = 64-amount;
	else if(level == 2)
		amount = 56-amount;
	else
		amount = 32-amount;

	for(counter=0; counter<amount; counter++)
	{
		value *= 2;
	}
	return value;
}

long long int permute_key(long long int mainKey, int level)
{
	long long int tempKey = 0;
	int matrixPointer = 0;
	int matrixSize = 0;
	int* permutation_table;

	if(level == 1)
	{
		permutation_table = pc_1;
		matrixSize = 56;
	}
	else
	{
		permutation_table = pc_2;
		matrixSize = 48;
	}


	for(matrixPointer=0; matrixPointer<matrixSize; matrixPointer++)
	{
		tempKey *= 2; // left shift, to make place for another bit
		if( mainKey&generate_mask(permutation_table[matrixPointer],level) ) //x-bit is 1
			tempKey+=1;
	}
	return tempKey;
}

void dived_key(long long int key, int* c_Key, int* d_Key)
{
	long long int d_key_mask = 0x0000000FFFFFFF;
	long long int c_key_mask = 0xFFFFFFF0000000;

	*d_Key = key&d_key_mask;
	*c_Key = (key&c_key_mask) >> 28;

}

int rotate_dived_key(int key, int positions)
{
	int counter;

	for(counter=0; counter<positions; counter++)
	{
		//key = key << positions;
		key = key << 1;
		if( key&0x10000000 ) // mask 29th bit, to add or not( if 29th bit == 0 ) it to end of key.
			key += 1;

		key&=0xFFFFFFF; //mask all 28 bits of key without 29th.
	}
	return key;
}

long long int concatenate_keys(long long int c_key, int d_key)
{
	return (c_key << 28) | d_key;
}

long long int generate_key(long long int start_key, int number)
{
	int c_key, d_key;
	int counter;

	if(number > 16 || number < 1)//input data check
		return 0;

	start_key = permute_key(start_key,1);
	dived_key(start_key,&c_key,&d_key);

	for(counter=1; counter<=number; counter++)
	{
		if(counter == 1 || counter == 2 || counter == 9 ||counter == 16)
		{
			c_key = rotate_dived_key(c_key,1);
			d_key = rotate_dived_key(d_key,1);
		}
		else
		{
			c_key = rotate_dived_key(c_key,2);
			d_key = rotate_dived_key(d_key,2);
	
		
		}
	}

	start_key = concatenate_keys(c_key,d_key);
	start_key = permute_key(start_key,2);
	return start_key;
}

// Instructions for data manipulating
long long int initial_data_permute(long long int data)
{
	long long int tempKey = 0;
	int matrixPointer = 0;
	int matrixSize = 64;
	

	for(matrixPointer=0; matrixPointer<matrixSize; matrixPointer++)
	{
		tempKey *= 2; // left shift, to make place for another bit
		if( data&generate_mask(initial_permutation_table[matrixPointer],1) ) //x-bit is 1
			tempKey+=1;
	}
	return tempKey;
}

long long int expand_data_permute(int data)
{
	long long int tempKey = 0;
	int matrixPointer = 0;
	int matrixSize = 48;
	

	for(matrixPointer=0; matrixPointer<matrixSize; matrixPointer++)
	{
		tempKey *= 2; // left shift, to make place for another bit
		if( data&generate_mask(expand_permutation_table[matrixPointer],3) ) //x-bit is 1
			tempKey+=1;
	}
	return tempKey;
}

long long int xor_data(long long int data1, long long data2)
{
	return data1 ^ data2;
}

void split_data(long long int data,long long int* left,long long int* right)
{
	long long int right_mask = 0x00000000FFFFFFFF;
	long long int left_mask =  0xFFFFFFFF00000000;

	*right = data&right_mask;
	*left = (data&left_mask) >> 32;

}

int get_s_value(int number, int row, int column)
{
	
	switch(number)
	{
	case 1: return s1_table[row][column];
	case 2: return s2_table[row][column];
	case 3: return s3_table[row][column];
	case 4: return s4_table[row][column];
	case 5: return s5_table[row][column];
	case 6: return s6_table[row][column];
	case 7: return s7_table[row][column];
	case 8: return s8_table[row][column];
	}
	
}

int s_box_transform(long long int key)
{
	int* transformation_table;
	int counter;
	int shift_value = 42;
	long long int mask = 0xFC0000000000; //mask first 6 bits ( from right );
	long long int small_word;
	int row_number, column_number;
	int end_data = 0;

	//transformation_table = s1_table;

	// masking and reading next bits ( 6 bits)
	for(counter=0; counter<8; counter++)
	{
		small_word = (key&mask) >> shift_value;
		shift_value -= 6;
		mask = mask >> 6;


		//calculating row number
		row_number = small_word&0x1; // first bit of 6
		if( small_word&0x20 ) // 6th bit of 6
			row_number += 0x2;

		//calculating caolumn number

		column_number = small_word&0x1E; // 4 bits in the middle
		column_number = column_number >> 1;

		//merge end data value

		end_data = end_data << 4;
		end_data += get_s_value(counter+1, row_number, column_number);
		
	}

	return end_data;

}

int p_data_permute(int data)
{
	long long int tempKey = 0;
	int matrixPointer = 0;
	int matrixSize = 32;
	

	for(matrixPointer=0; matrixPointer<matrixSize; matrixPointer++)
	{
		tempKey *= 2; // left shift, to make place for another bit
		if( data&generate_mask(p_permutation_table[matrixPointer],3) ) //x-bit is 1
			tempKey+=1;
	}
	return tempKey;
}

long long int final_permute(long long int data)
{
	long long int tempKey = 0;
	int matrixPointer = 0;
	int matrixSize = 64;
	

	for(matrixPointer=0; matrixPointer<matrixSize; matrixPointer++)
	{
		tempKey *= 2; // left shift, to make place for another bit
		if( data&generate_mask(final_permutation_table[matrixPointer],1) ) //x-bit is 1
			tempKey+=1;
	}
	return tempKey;

}

//END OF BLOCK 
long long int encrypt_message(long long int message, long long int key)
{

	int c0_key = 0, d0_key = 0;
	long long int left_part_message, right_part_message;
	
	long long int next_left_part_message, next_right_part_message;
	int iteration_counter;

	long long int end_data = 0;


	message = initial_data_permute(message);
	split_data(message, &left_part_message, &right_part_message);

	next_left_part_message = left_part_message;
	next_right_part_message = right_part_message;

	//16 Iterations

	for(iteration_counter=1; iteration_counter<=16; iteration_counter++)
	{
		next_right_part_message = expand_data_permute(right_part_message);
		next_right_part_message = xor_data( next_right_part_message, generate_key(key,iteration_counter) );
		next_right_part_message = s_box_transform(next_right_part_message);
		next_right_part_message = p_data_permute(next_right_part_message);
		next_right_part_message = xor_data(left_part_message,next_right_part_message);


		left_part_message = right_part_message &0x00000000FFFFFFFF ; // I masksed last 32 bits, because we don't need this data, but it's not neceseary. However FFFFFFFF on last positions may cause problems
		right_part_message = (next_right_part_message &0x00000000FFFFFFFF);
	}

	//Reverse connecting data
	end_data = (right_part_message << 32) | left_part_message;
	//Final data permutation 
	end_data = final_permute(end_data);
	return end_data;
}

long long int decrypt_message(long long int message, long long int key)
{

	int c0_key = 0, d0_key = 0;
	long long int left_part_message, right_part_message;
	
	long long int next_left_part_message, next_right_part_message;
	int iteration_counter;

	long long int end_data = 0;


	message = initial_data_permute(message);
	split_data(message, &left_part_message, &right_part_message);

	next_left_part_message = left_part_message;
	next_right_part_message = right_part_message;

	//16 Iterations

	for(iteration_counter=16; iteration_counter>=1; iteration_counter--)
	{
		next_right_part_message = expand_data_permute(right_part_message);
		next_right_part_message = xor_data( next_right_part_message, generate_key(key,iteration_counter) );
		next_right_part_message = s_box_transform(next_right_part_message);
		next_right_part_message = p_data_permute(next_right_part_message);
		next_right_part_message = xor_data(left_part_message,next_right_part_message);


		left_part_message = right_part_message &0x00000000FFFFFFFF ; // I masksed last 32 bits, because we don't need this data, but it's not neceseary. However FFFFFFFF on last positions may cause problems
		right_part_message = (next_right_part_message &0x00000000FFFFFFFF);
	}

	//Reverse connecting data
	end_data = (right_part_message << 32) | left_part_message;
	//Final data permutation 
	end_data = final_permute(end_data);
	return end_data;
}

