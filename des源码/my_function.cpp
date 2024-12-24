#include "stdafx.h"
#include "my_function.h"
#include "stdio.h"
#include <string.h>
#include <memory.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned char key_layer[768];

const unsigned char  pc_1[56] =
	{
	56, 48, 40, 32, 24, 16,  8,  0,
	57, 49, 41, 33, 25, 17,  9,  1,
	58, 50, 42, 34, 26, 18, 10,  2,
	59, 51, 43, 35, 62, 54, 46, 38,
	30, 22, 14,  6, 61, 53, 45, 37,
	29, 21, 13,  5, 60, 52, 44, 36,
	28, 20, 12,  4, 27, 19, 11,  3,
	};

const unsigned char  ip_tab[64] =
	{
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7,
	56, 48, 40, 32, 24, 16,  8,  0,
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	};


const unsigned char  sbox[8][64] =
	{
		{
		56, 16, 52,  4,  8, 60, 44, 32, 12, 40, 24, 48, 20, 36,  0, 28,
			0, 60, 28, 16, 56,  8, 52,  4, 40, 24, 48, 44, 36, 20, 12, 32,
			16,  4, 56, 32, 52, 24,  8, 44, 60, 48, 36, 28, 12, 40, 20,  0,
			60, 48, 32,  8, 16, 36,  4, 28, 20, 44, 12, 56, 40,  0, 24, 52,
		},

		{
		60,  4, 32, 56, 24, 44, 12, 16, 36, 28,  8, 52, 48,  0, 20, 40,
			12, 52, 16, 28, 60,  8, 32, 56, 48,  0,  4, 40, 24, 36, 44, 20,
			0, 56, 28, 44, 40, 16, 52,  4, 20, 32, 48, 24, 36, 12,  8, 60,
			52, 32, 40,  4, 12, 60, 16,  8, 44, 24, 28, 48,  0, 20, 56, 36,
			},

			{
			40,  0, 36, 56, 24, 12, 60, 20,  4, 52, 48, 28, 44, 16,  8, 32,
				52, 28,  0, 36, 12, 16, 24, 40,  8, 32, 20, 56, 48, 44, 60,  4,
				52, 24, 16, 36, 32, 60, 12,  0, 44,  4,  8, 48, 20, 40, 56, 28,
				4, 40, 52,  0, 24, 36, 32, 28, 16, 60, 56, 12, 44, 20,  8, 48,
			},

			{
			28, 52, 56, 12,  0, 24, 36, 40,  4,  8, 32, 20, 44, 48, 16, 60,
				52, 32, 44, 20, 24, 60,  0, 12, 16, 28,  8, 48,  4, 40, 56, 36,
				40, 24, 36,  0, 48, 44, 28, 52, 60,  4, 12, 56, 20,  8, 32, 16,
				12, 60,  0, 24, 40,  4, 52, 32, 36, 16, 20, 44, 48, 28,  8, 56,
				},

				{
				8, 48, 16,  4, 28, 40, 44, 24, 32, 20, 12, 60, 52,  0, 56, 36,
					56, 44,  8, 48, 16, 28, 52,  4, 20,  0, 60, 40, 12, 36, 32, 24,
					16,  8,  4, 44, 40, 52, 28, 32, 60, 36, 48, 20, 24, 12,  0, 56,
					44, 32, 48, 28,  4, 56,  8, 52, 24, 60,  0, 36, 40, 16, 20, 12,
				},

				{
				48,  4, 40, 60, 36,  8, 24, 32,  0, 52, 12, 16, 56, 28, 20, 44,
					40, 60, 16,  8, 28, 48, 36, 20, 24,  4, 52, 56,  0, 44, 12, 32,
					36, 56, 60, 20,  8, 32, 48, 12, 28,  0, 16, 40,  4, 52, 44, 24,
					16, 12,  8, 48, 36, 20, 60, 40, 44, 56,  4, 28, 24,  0, 32, 52,
					},

					{
					16, 44,  8, 56, 60,  0, 32, 52, 12, 48, 36, 28, 20, 40, 24,  4,
						52,  0, 44, 28, 16, 36,  4, 40, 56, 12, 20, 48,  8, 60, 32, 24,
						4, 16, 44, 52, 48, 12, 28, 56, 40, 60, 24, 32,  0, 20, 36,  8,
						24, 44, 52, 32,  4, 16, 40, 28, 36, 20,  0, 60, 56,  8, 12, 48,
					},

					{
					52,  8, 32, 16, 24, 60, 44,  4, 40, 36, 12, 56, 20,  0, 48, 28,
						4, 60, 52, 32, 40, 12, 28, 16, 48, 20, 24, 44,  0, 56, 36,  8,
						28, 44, 16,  4, 36, 48, 56,  8,  0, 24, 40, 52, 60, 12, 20, 32,
						8,  4, 56, 28, 16, 40, 32, 52, 60, 48, 36,  0, 12, 20, 24, 44,
						}
	};

unsigned char  hex_to_bool_table[64]=
	{
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
	0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1
	};

const unsigned char  qcb[64]=
	{
	0, 16,  1, 17,  2, 18,  3, 19,
	4, 20,  5, 21,  6, 22,  7, 23,
	8, 24,  9, 25, 10, 26, 11, 27,
	12, 28, 13, 29, 14, 30, 15, 31,
	32, 48, 33, 49, 34, 50, 35, 51,
	36, 52, 37, 53, 38, 54, 39, 55,
	40, 56, 41, 57, 42, 58, 43, 59,
	44, 60, 45, 61, 46, 62, 47, 63
	};

void MY_FUNCTION::set_key(unsigned char *key)
	{
	 unsigned char   i,ch,ch1;
	 unsigned char  key_left[28],key_right[28];
	 unsigned char  key_bool[64];
	 unsigned char  *pp;
	 unsigned char  *px;


	for(i=0, pp = key_bool; i<8; i++)
		{
		ch = key[i];

		pp[0] =  ch >> 7;
		pp[1] = (ch >> 6) & 1;
		pp[2] = (ch >> 5) & 1;
		pp[3] = (ch >> 4) & 1;
		pp[4] = (ch >> 3) & 1;
		pp[5] = (ch >> 2) & 1;
		pp[6] = (ch >> 1) & 1;
		pp[7] =  ch & 1;

		pp += 8;
		}

	for (i=0; i<28; i++)
		{
		key_left[i]  = key_bool[pc_1[i]];
		key_right[i] = key_bool[pc_1[28+i]];
		}

	px = key_layer;
	for (i=0; i<16; i++)
		{
		if( (i > 1) && (i != 8) && (i != 15) )
			{
			ch  = key_left[0];
			ch1 = key_left[1];
			key_left[ 0] = key_left[ 2];
			key_left[ 1] = key_left[ 3];
			key_left[ 2] = key_left[ 4];
			key_left[ 3] = key_left[ 5];
			key_left[ 4] = key_left[ 6];
			key_left[ 5] = key_left[ 7];
			key_left[ 6] = key_left[ 8];
			key_left[ 7] = key_left[ 9];
			key_left[ 8] = key_left[10];
			key_left[ 9] = key_left[11];
			key_left[10] = key_left[12];
			key_left[11] = key_left[13];
			key_left[12] = key_left[14];
			key_left[13] = key_left[15];
			key_left[14] = key_left[16];
			key_left[15] = key_left[17];
			key_left[16] = key_left[18];
			key_left[17] = key_left[19];
			key_left[18] = key_left[20];
			key_left[19] = key_left[21];
			key_left[20] = key_left[22];
			key_left[21] = key_left[23];
			key_left[22] = key_left[24];
			key_left[23] = key_left[25];
			key_left[24] = key_left[26];
			key_left[25] = key_left[27];
			key_left[26] = ch;
			key_left[27] = ch1;

			////////////////////////////////////////////////////////
			ch  = key_right[0];
			ch1 = key_right[1];
			key_right[ 0] = key_right[ 2];
			key_right[ 1] = key_right[ 3];
			key_right[ 2] = key_right[ 4];
			key_right[ 3] = key_right[ 5];
			key_right[ 4] = key_right[ 6];
			key_right[ 5] = key_right[ 7];
			key_right[ 6] = key_right[ 8];
			key_right[ 7] = key_right[ 9];
			key_right[ 8] = key_right[10];
			key_right[ 9] = key_right[11];
			key_right[10] = key_right[12];
			key_right[11] = key_right[13];
			key_right[12] = key_right[14];
			key_right[13] = key_right[15];
			key_right[14] = key_right[16];
			key_right[15] = key_right[17];
			key_right[16] = key_right[18];
			key_right[17] = key_right[19];
			key_right[18] = key_right[20];
			key_right[19] = key_right[21];
			key_right[20] = key_right[22];
			key_right[21] = key_right[23];
			key_right[22] = key_right[24];
			key_right[23] = key_right[25];
			key_right[24] = key_right[26];
			key_right[25] = key_right[27];
			key_right[26] = ch;
			key_right[27] = ch1;
			}
		else
			{
			ch = key_left[0];
			key_left[0]  = key_left[1];
			key_left[1]  = key_left[2];
			key_left[2]  = key_left[3];
			key_left[3]  = key_left[4];
			key_left[4]  = key_left[5];
			key_left[5]  = key_left[6];
			key_left[6]  = key_left[7];
			key_left[7]  = key_left[8];
			key_left[8]  = key_left[9];
			key_left[9]  = key_left[10];
			key_left[10] = key_left[11];
			key_left[11] = key_left[12];
			key_left[12] = key_left[13];
			key_left[13] = key_left[14];
			key_left[14] = key_left[15];
			key_left[15] = key_left[16];
			key_left[16] = key_left[17];
			key_left[17] = key_left[18];
			key_left[18] = key_left[19];
			key_left[19] = key_left[20];
			key_left[20] = key_left[21];
			key_left[21] = key_left[22];
			key_left[22] = key_left[23];
			key_left[23] = key_left[24];
			key_left[24] = key_left[25];
			key_left[25] = key_left[26];
			key_left[26] = key_left[27];
			key_left[27] = ch;

			ch = key_right[0];
			key_right[0]  = key_right[1];
			key_right[1]  = key_right[2];
			key_right[2]  = key_right[3];
			key_right[3]  = key_right[4];
			key_right[4]  = key_right[5];
			key_right[5]  = key_right[6];
			key_right[6]  = key_right[7];
			key_right[7]  = key_right[8];
			key_right[8]  = key_right[9];
			key_right[9]  = key_right[10];
			key_right[10] = key_right[11];
			key_right[11] = key_right[12];
			key_right[12] = key_right[13];
			key_right[13] = key_right[14];
			key_right[14] = key_right[15];
			key_right[15] = key_right[16];
			key_right[16] = key_right[17];
			key_right[17] = key_right[18];
			key_right[18] = key_right[19];
			key_right[19] = key_right[20];
			key_right[20] = key_right[21];
			key_right[21] = key_right[22];
			key_right[22] = key_right[23];
			key_right[23] = key_right[24];
			key_right[24] = key_right[25];
			key_right[25] = key_right[26];
			key_right[26] = key_right[27];
			key_right[27] = ch;
			}

		px[0]  = key_left[13];
		px[1]  = key_left[16];
		px[2]  = key_left[10];
		px[3]  = key_left[23];
		px[4]  = key_left[0];
		px[5]  = key_left[4];
		px[6]  = key_left[2];
		px[7]  = key_left[27];
		px[8]  = key_left[14];
		px[9]  = key_left[5];
		px[10] = key_left[20];
		px[11] = key_left[9];
		px[12] = key_left[22];
		px[13] = key_left[18];
		px[14] = key_left[11];
		px[15] = key_left[3];
		px[16] = key_left[25];
		px[17] = key_left[7];
		px[18] = key_left[15];
		px[19] = key_left[6];
		px[20] = key_left[26];
		px[21] = key_left[19];
		px[22] = key_left[12];
		px[23] = key_left[1];
		px[24] = key_right[12];
		px[25] = key_right[23];
		px[26] = key_right[2];
		px[27] = key_right[8];
		px[28] = key_right[18];
		px[29] = key_right[26];
		px[30] = key_right[1];
		px[31] = key_right[11];
		px[32] = key_right[22];
		px[33] = key_right[16];
		px[34] = key_right[4];
		px[35] = key_right[19];
		px[36] = key_right[15];
		px[37] = key_right[20];
		px[38] = key_right[10];
		px[39] = key_right[27];
		px[40] = key_right[5];
		px[41] = key_right[24];
		px[42] = key_right[17];
		px[43] = key_right[13];
		px[44] = key_right[21];
		px[45] = key_right[7];
		px[46] = key_right[0];
		px[47] = key_right[3];

		px += 48;
		}
	}


void MY_FUNCTION::des_crypt(unsigned char crypt_flag, unsigned char *text, unsigned char *result)
	{
	unsigned char   *pc;
	unsigned char   i;
	unsigned char   ch;
	unsigned char   box[8];
	unsigned char  sbox_out[48];
	unsigned char  text_left[32], text_right[32];
	unsigned char  text_bool[64];
	unsigned char  *pp;
	unsigned char  *px;



	for(i=0, pp = text_bool; i<8; i++)
		{
		ch = text[i];

		pp[0] =  ch >> 7;
		pp[1] = (ch >> 6) & 1;
		pp[2] = (ch >> 5) & 1;
		pp[3] = (ch >> 4) & 1;
		pp[4] = (ch >> 3) & 1;
		pp[5] = (ch >> 2) & 1;
		pp[6] = (ch >> 1) & 1;
		pp[7] =  ch & 1;

		pp += 8;

		}

	for (i=0; i<32; i++)
		{
		text_left[i]  = text_bool[ip_tab[i]];
		text_right[i] = text_bool[ip_tab[32+i]];
		}

	if(crypt_flag == ENCRYPT)
		{
		px = key_layer;
		}
	else
		{
		px = key_layer + 720;
		}

	for (i=0; i<16; i++)
		{
		sbox_out[46] = (px[46] ^ text_right[31]) << 1;
		sbox_out[ 0] = (px[ 0] ^ text_right[31]) << 5;
		sbox_out[47] = (px[47] ^ text_right[ 0]);
		sbox_out[ 1] = (px[ 1] ^ text_right[ 0]) << 4;
		sbox_out[ 2] = (px[ 2] ^ text_right[ 1]) << 3;
		sbox_out[ 3] = (px[ 3] ^ text_right[ 2]) << 2;
		sbox_out[ 4] = (px[ 4] ^ text_right[ 3]) << 1;
		sbox_out[ 6] = (px[ 6] ^ text_right[ 3]) << 5;
		sbox_out[ 5] = (px[ 5] ^ text_right[ 4]);
		sbox_out[ 7] = (px[ 7] ^ text_right[ 4]) << 4;
		sbox_out[ 8] = (px[ 8] ^ text_right[ 5]) << 3;
		sbox_out[ 9] = (px[ 9] ^ text_right[ 6]) << 2;
		sbox_out[10] = (px[10] ^ text_right[ 7]) << 1;
		sbox_out[12] = (px[12] ^ text_right[ 7]) << 5;
		sbox_out[11] = (px[11] ^ text_right[ 8]);
		sbox_out[13] = (px[13] ^ text_right[ 8]) << 4;
		sbox_out[14] = (px[14] ^ text_right[ 9]) << 3;
		sbox_out[15] = (px[15] ^ text_right[10]) << 2;
		sbox_out[16] = (px[16] ^ text_right[11]) << 1;
		sbox_out[18] = (px[18] ^ text_right[11]) << 5;
		sbox_out[17] = (px[17] ^ text_right[12]);
		sbox_out[19] = (px[19] ^ text_right[12]) << 4;
		sbox_out[20] = (px[20] ^ text_right[13]) << 3;
		sbox_out[21] = (px[21] ^ text_right[14]) << 2;
		sbox_out[22] = (px[22] ^ text_right[15]) << 1;
		sbox_out[24] = (px[24] ^ text_right[15]) << 5;
		sbox_out[23] = (px[23] ^ text_right[16]);
		sbox_out[25] = (px[25] ^ text_right[16]) << 4;
		sbox_out[26] = (px[26] ^ text_right[17]) << 3;
		sbox_out[27] = (px[27] ^ text_right[18]) << 2;
		sbox_out[28] = (px[28] ^ text_right[19]) << 1;
		sbox_out[30] = (px[30] ^ text_right[19]) << 5;
		sbox_out[29] = (px[29] ^ text_right[20]);
		sbox_out[31] = (px[31] ^ text_right[20]) << 4;
		sbox_out[32] = (px[32] ^ text_right[21]) << 3;
		sbox_out[33] = (px[33] ^ text_right[22]) << 2;
		sbox_out[34] = (px[34] ^ text_right[23]) << 1;
		sbox_out[36] = (px[36] ^ text_right[23]) << 5;
		sbox_out[35] = (px[35] ^ text_right[24]);
		sbox_out[37] = (px[37] ^ text_right[24]) << 4;
		sbox_out[38] = (px[38] ^ text_right[25]) << 3;
		sbox_out[39] = (px[39] ^ text_right[26]) << 2;
		sbox_out[40] = (px[40] ^ text_right[27]) << 1;
		sbox_out[42] = (px[42] ^ text_right[27]) << 5;
		sbox_out[41] = (px[41] ^ text_right[28]);
		sbox_out[43] = (px[43] ^ text_right[28]) << 4;
		sbox_out[44] = (px[44] ^ text_right[29]) << 3;
		sbox_out[45] = (px[45] ^ text_right[30]) << 2;

		box[0] = sbox_out[ 0] | sbox_out[ 1] | sbox_out[ 2] | sbox_out[ 3] | sbox_out[ 4] | sbox_out[5];
		box[1] = sbox_out[ 6] | sbox_out[ 7] | sbox_out[ 8] | sbox_out[ 9] | sbox_out[10] | sbox_out[11];
		box[2] = sbox_out[12] | sbox_out[13] | sbox_out[14] | sbox_out[15] | sbox_out[16] | sbox_out[17];
		box[3] = sbox_out[18] | sbox_out[19] | sbox_out[20] | sbox_out[21] | sbox_out[22] | sbox_out[23];
		box[4] = sbox_out[24] | sbox_out[25] | sbox_out[26] | sbox_out[27] | sbox_out[28] | sbox_out[29];
		box[5] = sbox_out[30] | sbox_out[31] | sbox_out[32] | sbox_out[33] | sbox_out[34] | sbox_out[35];
		box[6] = sbox_out[36] | sbox_out[37] | sbox_out[38] | sbox_out[39] | sbox_out[40] | sbox_out[41];
		box[7] = sbox_out[42] | sbox_out[43] | sbox_out[44] | sbox_out[45] | sbox_out[46] | sbox_out[47];

		pc = &hex_to_bool_table[sbox[0][qcb[box[0]]]];
		sbox_out[0] = pc[0];
		sbox_out[1] = pc[1];
		sbox_out[2] = pc[2];
		sbox_out[3] = pc[3];


		pc = &hex_to_bool_table[sbox[1][qcb[box[1]]]];
		sbox_out[4] = pc[0];
		sbox_out[5] = pc[1];
		sbox_out[6] = pc[2];
		sbox_out[7] = pc[3];

		pc = &hex_to_bool_table[sbox[2][qcb[box[2]]]];
		sbox_out[8]  = pc[0];
		sbox_out[9]  = pc[1];
		sbox_out[10] = pc[2];
		sbox_out[11] = pc[3];

		pc = &hex_to_bool_table[sbox[3][qcb[box[3]]]];
		sbox_out[12] = pc[0];
		sbox_out[13] = pc[1];
		sbox_out[14] = pc[2];
		sbox_out[15] = pc[3];

		pc = &hex_to_bool_table[sbox[4][qcb[box[4]]]];
		sbox_out[16] = pc[0];
		sbox_out[17] = pc[1];
		sbox_out[18] = pc[2];
		sbox_out[19] = pc[3];

		pc = &hex_to_bool_table[sbox[5][qcb[box[5]]]];
		sbox_out[20] = pc[0];
		sbox_out[21] = pc[1];
		sbox_out[22] = pc[2];
		sbox_out[23] = pc[3];

		pc = &hex_to_bool_table[sbox[6][qcb[box[6]]]];
		sbox_out[24] = pc[0];
		sbox_out[25] = pc[1];
		sbox_out[26] = pc[2];
		sbox_out[27] = pc[3];

		pc = &hex_to_bool_table[sbox[7][qcb[box[7]]]];
		sbox_out[28] = pc[0];
		sbox_out[29] = pc[1];
		sbox_out[30] = pc[2];
		sbox_out[31] = pc[3];

		ch  = text_right[0];
		text_right[0] = sbox_out[15] ^ text_left[0];
		text_left[0] = ch;

		ch  = text_right[1];
		text_right[1] = sbox_out[6] ^ text_left[1];
		text_left[1] = ch;

		ch  = text_right[2];
		text_right[2] = sbox_out[19] ^ text_left[2];
		text_left[2] = ch;

		ch  = text_right[3];
		text_right[3] = sbox_out[20] ^ text_left[3];
		text_left[3] = ch;

		ch  = text_right[4];
		text_right[4] = sbox_out[28] ^ text_left[4];
		text_left[4] = ch;

		ch  = text_right[5];
		text_right[5] = sbox_out[11] ^ text_left[5];
		text_left[5] = ch;

		ch  = text_right[6];
		text_right[6] = sbox_out[27] ^ text_left[6];
		text_left[6] = ch;

		ch  = text_right[7];
		text_right[7] = sbox_out[16] ^ text_left[7];
		text_left[7] = ch;

		ch  = text_right[8];
		text_right[8] = sbox_out[0] ^ text_left[8];
		text_left[8] = ch;

		ch  = text_right[9];
		text_right[9] = sbox_out[14] ^ text_left[9];
		text_left[9] = ch;

		ch  = text_right[10];
		text_right[10] = sbox_out[22] ^ text_left[10];
		text_left[10] = ch;

		ch  = text_right[11];
		text_right[11] = sbox_out[25] ^ text_left[11];
		text_left[11] = ch;

		ch  = text_right[12];
		text_right[12] = sbox_out[4] ^ text_left[12];
		text_left[12] = ch;

		ch  = text_right[13];
		text_right[13] = sbox_out[17] ^ text_left[13];
		text_left[13] = ch;

		ch  = text_right[14];
		text_right[14] = sbox_out[30] ^ text_left[14];
		text_left[14] = ch;

		ch  = text_right[15];
		text_right[15] = sbox_out[9] ^ text_left[15];
		text_left[15] = ch;

		ch  = text_right[16];
		text_right[16] = sbox_out[1] ^ text_left[16];
		text_left[16] = ch;

		ch  = text_right[17];
		text_right[17] = sbox_out[7] ^ text_left[17];
		text_left[17] = ch;

		ch  = text_right[18];
		text_right[18] = sbox_out[23] ^ text_left[18];
		text_left[18] = ch;

		ch  = text_right[19];
		text_right[19] = sbox_out[13] ^ text_left[19];
		text_left[19] = ch;

		ch  = text_right[20];
		text_right[20] = sbox_out[31] ^ text_left[20];
		text_left[20] = ch;

		ch  = text_right[21];
		text_right[21] = sbox_out[26] ^ text_left[21];
		text_left[21] = ch;

		ch  = text_right[22];
		text_right[22] = sbox_out[2] ^ text_left[22];
		text_left[22] = ch;

		ch  = text_right[23];
		text_right[23] = sbox_out[8] ^ text_left[23];
		text_left[23] = ch;

		ch  = text_right[24];
		text_right[24] = sbox_out[18] ^ text_left[24];
		text_left[24] = ch;

		ch  = text_right[25];
		text_right[25] = sbox_out[12] ^ text_left[25];
		text_left[25] = ch;

		ch  = text_right[26];
		text_right[26] = sbox_out[29] ^ text_left[26];
		text_left[26] = ch;

		ch  = text_right[27];
		text_right[27] = sbox_out[5] ^ text_left[27];
		text_left[27] = ch;

		ch  = text_right[28];
		text_right[28] = sbox_out[21] ^ text_left[28];
		text_left[28] = ch;

		ch  = text_right[29];
		text_right[29] = sbox_out[10] ^ text_left[29];
		text_left[29] = ch;

		ch  = text_right[30];
		text_right[30] = sbox_out[3] ^ text_left[30];
		text_left[30] = ch;

		ch  = text_right[31];
		text_right[31] = sbox_out[24] ^ text_left[31];
		text_left[31] = ch;

		if(crypt_flag == ENCRYPT)
			px += 48;
		else
			px -= 48;

		}

	result[0] = (text_left[7]<<7)|(text_right[7]<<6)|(text_left[15]<<5)|(text_right[15]<<4)|(text_left[23]<<3)|(text_right[23]<<2)|(text_left[31]<<1)|(text_right[31]);
	result[1] = (text_left[6]<<7)|(text_right[6]<<6)|(text_left[14]<<5)|(text_right[14]<<4)|(text_left[22]<<3)|(text_right[22]<<2)|(text_left[30]<<1)|(text_right[30]);
	result[2] = (text_left[5]<<7)|(text_right[5]<<6)|(text_left[13]<<5)|(text_right[13]<<4)|(text_left[21]<<3)|(text_right[21]<<2)|(text_left[29]<<1)|(text_right[29]);
	result[3] = (text_left[4]<<7)|(text_right[4]<<6)|(text_left[12]<<5)|(text_right[12]<<4)|(text_left[20]<<3)|(text_right[20]<<2)|(text_left[28]<<1)|(text_right[28]);
	result[4] = (text_left[3]<<7)|(text_right[3]<<6)|(text_left[11]<<5)|(text_right[11]<<4)|(text_left[19]<<3)|(text_right[19]<<2)|(text_left[27]<<1)|(text_right[27]);
	result[5] = (text_left[2]<<7)|(text_right[2]<<6)|(text_left[10]<<5)|(text_right[10]<<4)|(text_left[18]<<3)|(text_right[18]<<2)|(text_left[26]<<1)|(text_right[26]);
	result[6] = (text_left[1]<<7)|(text_right[1]<<6)|(text_left[ 9]<<5)|(text_right[ 9]<<4)|(text_left[17]<<3)|(text_right[17]<<2)|(text_left[25]<<1)|(text_right[25]);
	result[7] = (text_left[0]<<7)|(text_right[0]<<6)|(text_left[ 8]<<5)|(text_right[ 8]<<4)|(text_left[16]<<3)|(text_right[16]<<2)|(text_left[24]<<1)|(text_right[24]);

	}


void MY_FUNCTION::Encrypt(unsigned char keyflag, unsigned char *key, int length, unsigned char *text, unsigned char *result)
{
	//keyflag: 1,2,3
	//length should be 8*n

	int i;
	unsigned char *res;

	set_key(key);

	res = result;

	for(i=0; i<length; i+=8)
	{
		des_crypt(ENCRYPT, text, res);
		text += 8;
		res += 8;
	}

	if(keyflag == DES_1)
		return;

	set_key(key+8);
	res = result;

	for(i=0; i<length; i+=8)
	{
		des_crypt(DECRYPT, res, res);
		res += 8;
	}


	if(keyflag == DES_2)
		set_key(key);
	else
		set_key(key+16);

	res = result;
	for(i=0; i<length; i+=8)
	{
		des_crypt(ENCRYPT, res, res);
		res += 8;
	}
				
}



	void MY_FUNCTION::Decrypt(unsigned char keyflag, unsigned char *key, int length, unsigned char *text, unsigned char *result)
	{
	//keyflag : 1,2,3
	//length should be 8*n

	int i;
	unsigned char *res;

	if(keyflag == DES_3)
		set_key(key+16);
	else
		set_key(key);


	res = result;

	for(i=0; i<length; i+=8)
		{
		des_crypt(DECRYPT, text, res);
		text += 8;
		res += 8;
		}

	if(keyflag == DES_1)
		return;

	set_key(key+8);
	res = result;

	for(i=0; i<length; i+=8)
		{
		des_crypt(ENCRYPT, res, res);
		res += 8;
		}


	set_key(key);

	res = result;
	for(i=0; i<length; i+=8)
		{
		des_crypt(DECRYPT, res, res);
		res+=8;
		}
	}


	void MY_FUNCTION::EncryptCBC(unsigned char keyflag, unsigned char* key, unsigned char* iv, int length, unsigned char* text, unsigned char* result)
	{
		//keyflag: 1,2,3
		//length should be 8*n
		int i,j;
		unsigned char* res = result;
		unsigned char* src = text;
		unsigned char temp_data[8];

		for (i = 0; i < length; i += 8)
		{
			if (i == 0)
			{
				for (j = 0; j < 8; j++)
				{
					temp_data[j] = iv[j] ^ src[j];
				}
			}
			else
			{
				for (j = 0; j < 8; j++)
				{
					temp_data[j] = res[j] ^ src[j];
				}
				res += 8;
			}
			Encrypt(keyflag, key, 8, temp_data, res);
			src += 8;
		}
	}



	void MY_FUNCTION::DecryptCBC(unsigned char keyflag, unsigned char* key, unsigned char* iv, int length, unsigned char* text, unsigned char* result)
	{
		//keyflag : 1,2,3
		//length should be 8*n
		int i, j;
		unsigned char* res = result;
		unsigned char* src = text;

		for (i = 0; i < length; i += 8)
		{
			Decrypt(keyflag, key, 8, src, res);
			for (j = 0; j < 8; j++)
			{
				res[j] ^= iv[j];
				iv[j] = src[j];
			}
			res += 8;
			src += 8;
		}
	}
/*--------------------------------做MAC运算----------------------------------------------
本函数可以做64位，128位，192位MAC运算
//keyflag : 1,2,3

-----------------------------------------------------------------------------------------*/
	unsigned char MY_FUNCTION::mac_encrypt_919(unsigned char keyflag, unsigned char *key, int text_bytes,  unsigned char *text,  unsigned char *mac)
	{
	unsigned char  tmp[8];
	unsigned char  i;
	int  len;

	set_key(key);
	memset(mac, 0, 8);
	for(len = 0; len < text_bytes;)
		{
		memset(tmp, 0, 8);
		for(i=0; (i<8)&&(len<text_bytes); i++, len++)
			{
			tmp[i] = *(text++);
			}
		mac[0] ^= tmp[0];
		mac[1] ^= tmp[1];
		mac[2] ^= tmp[2];
		mac[3] ^= tmp[3];
		mac[4] ^= tmp[4];
		mac[5] ^= tmp[5];
		mac[6] ^= tmp[6];
		mac[7] ^= tmp[7];

		des_crypt(ENCRYPT, mac, mac);
		}
	if(keyflag==DES_1){ return 0;}
	else if(keyflag==DES_2)
		{
		set_key(key+8);
		des_crypt(DECRYPT, mac, mac);
		set_key(key);
		des_crypt(ENCRYPT, mac, mac);
		return 0;
		}
	else
		{
		set_key(key+8);
		des_crypt(DECRYPT, mac, mac);
		set_key(key+16);
		des_crypt(ENCRYPT, mac, mac);
		return 0;
		}
	}

	void  MY_FUNCTION::EMacX99(unsigned char keyflag,unsigned char *key, int text_bytes, unsigned char *text, unsigned char *mac)
	{
	unsigned char  tmp[8];
	unsigned char i;
	int  len;

	if(keyflag == DES_1)
		set_key(key);

	memset(mac, 0, 8);
	for(len = 0; len < text_bytes;)
		{
		memset(tmp, 0, 8);

		for(i=0; (i<8)&&(len<text_bytes); i++, len++)
			tmp[i] = *text++;

		mac[0] ^= tmp[0];
		mac[1] ^= tmp[1];
		mac[2] ^= tmp[2];
		mac[3] ^= tmp[3];
		mac[4] ^= tmp[4];
		mac[5] ^= tmp[5];
		mac[6] ^= tmp[6];
		mac[7] ^= tmp[7];

		if(keyflag == DES_1)
			des_crypt(ENCRYPT, mac, mac);
		else
			Encrypt(keyflag, key, 8, mac, mac);

		}

	}

	void MY_FUNCTION::GetCheckValue(unsigned char keyflag, unsigned char *key, unsigned char *check)
	{
	//keyflag = 1/2/3 key长度 = 64/128/192
	unsigned char  zero[8];
	memset(zero, 0, 8);
	Encrypt(keyflag, key, 8, zero, check);
	}



	const int Table_ASC_HEX[]={	
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
		0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		0x40,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f	
		};

		const char HexToAsc[]="0123456789ABCDEF";

	void MY_FUNCTION::Hex2Ascii(int len, unsigned char *InBuf, unsigned char *OutBuf)
	{
		int i;
		
		for(i=0; i<len; i++)
		{
			OutBuf[0] = HexToAsc[InBuf[0]>>4];
			OutBuf[1] = HexToAsc[InBuf[0]&0xf];
			InBuf++;
			OutBuf += 2;
		}

	}

	
const UCHAR ASC2HEX[]=
{	
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x3a,0x3b,
	0x3c,0x3d,0x3e,0x3f,0x40,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
};
void MY_FUNCTION::Ascii2Hex(int len, unsigned char *InBuf, unsigned char *OutBuf)
{
	int i;


	for(i=0; i<len; i += 2)
	{
		*OutBuf = (ASC2HEX[InBuf[0]-'0']<<4)|(ASC2HEX[InBuf[1]-'0']);
		OutBuf++;
		InBuf += 2;		
	}
}

	//BYTE TO STRING
	//examples:0x12,0x34,0x56,0x78,0xab-->“12345678ab”
	//examples:0x12,0x34,0x56,0x78,0xab-->  '1''2''3''4''5''6''7''8''9''a'''b'
	void MY_FUNCTION::Byte2String(short len, unsigned char *InBuf, unsigned char *OutBuf)
	{
		short  i;
		
		for(i=0; i<len; i++)
		{
			OutBuf[0] = HexToAsc[InBuf[0]>>4];
			OutBuf[1] = HexToAsc[InBuf[0]&0xf];
			InBuf++;
			OutBuf += 2;
		}
	}
	//------------------------------------------------------------------------------
	//STRING TO BYTE  
	//examples:“12345678ab”-->0x12,0x34,0x56,0x78,0xab
	//examples: '1''2''3''4''5''6''7''8''9''a'''b'---->0x12,0x34,0x56,0x78,0xab
	//41 31 41 31 30 30 30 30----->A1 A1 00 00
	const unsigned char ASCToHEX[]=
	{	
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x3a,0x3b,
			0x3c,0x3d,0x3e,0x3f,0x40,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
	};
	void MY_FUNCTION::String2Byte(short len, unsigned char *InBuf, unsigned char *OutBuf)
	{
		short  i;
		
		for(i=0; i<len; i += 2)
		{
			*OutBuf = (ASCToHEX[InBuf[0]-'0']<<4)|(ASCToHEX[InBuf[1]-'0']);
			OutBuf++;
			InBuf += 2;		
		}
	}

	unsigned char MY_FUNCTION::key_dive(char unsigned flag, unsigned char keyfalg, unsigned char keylen, unsigned char *key, int datalen, unsigned char *data, unsigned char *resulte)
	{
		unsigned char i, j;
		unsigned char dive_in[16], dive_out[16], key_out[16], key_buff[16];
		unsigned char *p_data, *p_resulte;

		p_data = data;
		p_resulte = resulte;

		//获取密钥
		String2Byte(32, key, key_buff);

		if(flag == BYTE_8)
		{
			for (i=0; i<datalen/16; i++)
			{
				//加密
				String2Byte(16, p_data, dive_in);
				Encrypt(keyfalg,  key_buff, 8, dive_in, key_out);

				//求反加密
				for(j=0; j<8; j++)
				{
					dive_out[j] = ~dive_in[j];
				}
				Encrypt(keyfalg,  key_buff, 8, dive_out, key_out+8);

				//离散结果结果作为下次的密钥
				memset(key_buff, 0, 16);
				memcpy(key_buff, key_out, 16);
				p_data += 16;
			}
		}
		else if (flag == BYTE_16)
		{
			for (i=0; i<datalen/32; i++)
			{
				//加密
				String2Byte(32, p_data, dive_in);
				Encrypt(keyfalg,  key_buff, 16, dive_in, key_out);

				//离散结果结果作为下次的密钥
				memcpy(key_buff, key_out, 16);

				p_data += 16;
			}
		}
		else return -1;

		Byte2String(16, key_out, resulte);

		return TRUE;
	}

	unsigned char MY_FUNCTION::data_en_de(unsigned char flag, unsigned char keyflag, UCHAR *key, int datalen, UCHAR *data, UCHAR *resulte)
	{
		int i;
		UCHAR key_buff[24], datain[8], dataout[8];
		UCHAR *p_data, *p_res;

		p_data = data;
		p_res = resulte;

		String2Byte(keyflag*16, key, key_buff);

		if (flag == ENCRYPT)
		{
			for (i=0; i<datalen/16; i++)
			{
				String2Byte(16, p_data, datain);
				Encrypt(keyflag, key_buff, 8, datain, dataout);
				Byte2String(8, dataout, p_res);
				p_data += 16;
				p_res += 16;
			}
			return TRUE;
		} 
		else if (flag == DECRYPT)
		{
			for (i=0; i<datalen/16; i++)
			{
				String2Byte(16, p_data, datain);
				Decrypt(keyflag,  key_buff, 8, datain, dataout);
				Byte2String(8, dataout, p_res);
				p_data += 16;
				p_res += 16;
			}
			return TRUE;
		} 
		else return FALSE;
	}


	unsigned char MY_FUNCTION::mac_919_cal(unsigned char keyflag, UCHAR *key, UCHAR *begin_vector,int datalen, UCHAR *data, UCHAR *mac)
	{
		int i, j;
		UCHAR key_buff[24], temp_data[8], temp_vector[8], temp_buff[1024], temp[1024];
		UCHAR *p_data;

		memset(temp, '0', 1024);
		memcpy(temp, data, datalen);
		String2Byte(datalen, temp, temp_buff);
		p_data = temp_buff;
		if (datalen%2 != 0)
		{
			datalen++;
		}
		datalen /= 2;

		//获取密钥和初始向量
		String2Byte(keyflag*16, key, key_buff);
		String2Byte(16, begin_vector, temp_vector);		

		set_key(key_buff);

		if (datalen%8 != 0)
		{
			memset(temp_buff+datalen, 0, 8-datalen %8);
			datalen += 8-datalen %8;			
		}

		for (i=0; i<datalen/8;i++)
		{
			memcpy(temp_data, p_data, 8);
			for (j=0; j<8; j++)
			{
				temp_vector[j] ^= temp_data[j];
			}
			des_crypt(ENCRYPT, temp_vector, temp_vector);
			p_data += 8;
		}

		if(keyflag==DES_1)
		{ 
			Byte2String(8, temp_vector, mac);
			return 0;
		}
		else if(keyflag==DES_2)
		{
			set_key(key_buff+8);
			des_crypt(DECRYPT, temp_vector, temp_vector);
			set_key(key_buff);
			des_crypt(ENCRYPT, temp_vector, temp_vector);
			Byte2String(8, temp_vector, mac);
			return TRUE;
		}
		else
		{
			set_key(key_buff+8);
			des_crypt(DECRYPT, temp_vector, temp_vector);
			set_key(key_buff+16);
			des_crypt(ENCRYPT, temp_vector, temp_vector);
			Byte2String(8, temp_vector, mac);
			return TRUE;
		}

		return TRUE;
	}
		
//===================================================================================================
//===================================================================================================
//===================================================================================================
/*
函数功能：密钥分散（HEX格式）	
输入参数：
	flag			分散标志			BYTE_8				分散数据位8字节，内部求反并分散
										BYTE_16				分散数据位16字节， 外部求反，直接分散
	keyfalg			密钥标志			DES_1				密钥为8字节
										DES_2				密钥为16字节
										DES_3				密钥为24字节
	key				密钥
	datalen			分散数据长度
	data			分散数据
输出参数:		
	result			分散结果

*/	
unsigned char MY_FUNCTION::key_dive_hex(char unsigned flag, unsigned char keyfalg, unsigned char *key, int datalen, unsigned char *data, unsigned char *resulte)
{
	unsigned char i, j;
	unsigned char dive_in[16], dive_out[16], key_out[16], key_buff[16];
	unsigned char *p_data, *p_resulte;

	p_data = data;
	p_resulte = resulte;

	//获取密钥
	memcpy(key_buff, key, 16);

	if(flag == BYTE_8)
	{
		for (i=0; i<datalen/8; i++)
		{
			//加密
			memcpy(dive_in, p_data, 8);
			Encrypt(keyfalg,  key_buff, 8, dive_in, key_out);

			//求反加密
			for(j=0; j<8; j++)
			{
				dive_out[j] = ~dive_in[j];
			}
			Encrypt(keyfalg,  key_buff, 8, dive_out, key_out+8);

			//离散结果结果作为下次的密钥
			memset(key_buff, 0, 16);
			memcpy(key_buff, key_out, 16);
			p_data += 8;
		}
	}
	else if (flag == BYTE_16)
	{
		for (i=0; i<datalen/16; i++)
		{
			//加密
			memcpy(dive_in, p_data, 16);
			Encrypt(keyfalg,  key_buff, 16, dive_in, key_out);

			//离散结果结果作为下次的密钥
			memcpy(key_buff, key_out, 16);

			p_data += 16;
		}
	}
	else return -1;

	memcpy(resulte, key_out, 16);

	return TRUE;
}
/*
函数功能：数据加解密（HEX格式）	
输入参数：
	flag			加解密标志			ENCRYPT				
										DECRYPT				
	keyfalg			密钥标志			DES_1				密钥为8字节
										DES_2				密钥为16字节
										DES_3				密钥为24字节
	key				密钥
	datalen			加解密数据长度
	data			加解密数据
输出参数:		
	result			加解密结果
*/	
unsigned char MY_FUNCTION::data_en_de_hex(unsigned char flag, unsigned char keyflag, UCHAR *key, int datalen, UCHAR *data, UCHAR *resulte)
{
	int i;
	UCHAR *p_data, *p_res;

	p_data = data;
	p_res = resulte;

	if (flag == ENCRYPT)
	{
		for (i=0; i<datalen/8; i++)
		{
			Encrypt(keyflag, key, 8, p_data, p_res);
			p_data += 8;
			p_res += 8;
		}
		return TRUE;
	} 
	else if (flag == DECRYPT)
	{
		for (i=0; i<datalen/16; i++)
		{
			Decrypt(keyflag,  key, 8, p_data, p_res);
			p_data += 8;
			p_res += 8;
		}
		return TRUE;
	} 
	else return FALSE;
}
/*
函数功能：数据MAC（HEX格式）	
输入参数：
	keyfalg			密钥标志			DES_1				密钥为8字节
										DES_2				密钥为16字节
										DES_3				密钥为24字节
	key				密钥
	begin_vector	初始向量
	datalen			MAC数据长度
	data			MAC数据
输出参数:		
	mac				MAC值
*/	

unsigned char MY_FUNCTION::mac_919_cal_hex(unsigned char keyflag, UCHAR *key, UCHAR *begin_vector,int datalen, UCHAR *data, UCHAR *mac)
{
	int i, j;
	UCHAR key_buff[24], temp_data[8], temp_vector[8], temp_buff[1024], temp[1024];
	UCHAR *p_data;

	memset(temp, '0', 1024);
	memcpy(temp_buff, data, datalen);
	p_data = temp_buff;

	//获取密钥和初始向量
//	String2Byte(keyflag*16, key, key_buff);
//	String2Byte(16, begin_vector, temp_vector);		
	memcpy(key_buff, key, keyflag*8);
	memcpy(temp_vector, begin_vector, 8);

	set_key(key_buff);

	if (datalen%8 != 0)
	{
		memset(temp_buff+datalen, 0, 8-datalen %8);
		datalen += 8-datalen %8;			
	}

	for (i=0; i<datalen/8;i++)
	{
		memcpy(temp_data, p_data, 8);
		for (j=0; j<8; j++)
		{
			temp_vector[j] ^= temp_data[j];
		}
		des_crypt(ENCRYPT, temp_vector, temp_vector);
		p_data += 8;
	}

	if(keyflag==DES_1)
	{ 
//		Byte2String(8, temp_vector, mac);
		memcpy(mac, temp_vector, 8);
		return 0;
	}
	else if(keyflag==DES_2)
	{
		set_key(key_buff+8);
		des_crypt(DECRYPT, temp_vector, temp_vector);
		set_key(key_buff);
		des_crypt(ENCRYPT, temp_vector, temp_vector);
//		Byte2String(8, temp_vector, mac);
		memcpy(mac, temp_vector, 8);
		return TRUE;
	}
	else
	{
		set_key(key_buff+8);
		des_crypt(DECRYPT, temp_vector, temp_vector);
		set_key(key_buff+16);
		des_crypt(ENCRYPT, temp_vector, temp_vector);
//		Byte2String(8, temp_vector, mac);
		memcpy(mac, temp_vector, 8);
		return TRUE;
	}

	return TRUE;
}