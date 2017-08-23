/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		Font.cpp
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.11
* Description   ���ֿ���������ʵ��
description     
*******************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include "SET.h"
#include "Font.h"
CMyFont::CMyFont()
{
	openAsc();
	openHzk(m_selectfonts);	
}

CMyFont::~CMyFont()
{
	fclose(fileAsc);
	fileAsc = NULL;
	fclose(fileHzk);
	fileHzk = NULL;
}

// ��Ӣ���ֿ��и���offsetƫ������ȡ��bitNumberλ
unsigned char* CMyFont::getAsciiLib(int offset,int bitNumber){
	unsigned char* Lib = NULL;
	unsigned char* reverseLib = NULL;
	unsigned char ascii16[16][2];
	unsigned char ascii24[24][3];
	int conduct , column ;
	fseek(fileAsc, offset, SEEK_SET);
	fread(asciiLib, 1, bitNumber, fileAsc);
	// ����ѡ��ͬ��ȡģ�㷨�����в���
	if (0 == m_CB_ModelSave)
		return asciiLib;
	if (1 == m_CB_ModelSave){

		bit_reverse(asciiLib, reverseLib);
		return reverseLib;
	}
	if (16 == bitNumber) { 
		conduct = 1; 
		column = 16; 
		memcpy(ascii16, asciiLib, sizeof(asciiLib));
		transverse_modulus(ascii16, Lib, conduct, column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	else { 
		conduct = 2;
		column = 24;
		memcpy(ascii24, asciiLib, sizeof(asciiLib));
		transverse_modulus(ascii24, Lib, conduct, column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	return Lib;
}

// �������ֿ��и���offsetƫ��������bytetNumberλ
unsigned char* CMyFont::getHzkLib(int offset,int byteNumber){
	unsigned char* Lib = NULL;
	unsigned char* reverseLib = NULL;
	unsigned char hzk16[16][2];
	unsigned char hzk24[24][3];
	int conduct, column;
	fseek(fileHzk, offset, SEEK_SET);
	fread(hzkLib, 1, byteNumber, fileHzk);
	if (0 == m_CB_ModelSave)
		return hzkLib;
	if (1 == m_CB_ModelSave){

		bit_reverse(hzkLib, reverseLib);
		return reverseLib;
	}
	if (16 == byteNumber) {
		conduct = 2;
		column = 16;
		memcpy(hzk16, hzkLib, sizeof(hzkLib));
		transverse_modulus(hzk16, Lib,conduct,column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	else {
		conduct = 3;
		column = 24;
		memcpy(hzk24, hzkLib, sizeof(hzkLib));
		transverse_modulus(hzk24, Lib,conduct,column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	return Lib;
}

// ����ַ��ж���Ӣ�ĴӶ���ȡ��Ӧ�ֿ�
unsigned char* CMyFont::getLib(unsigned char* word){
	int m = 0;
	unsigned char* Lib = NULL;

	// ��ÿ���ַ������жϣ���ƫ��������ȡ��Ӧ�ֿ�
	while (word[m] != '\0'){
		if (word[m] > 'A' && word[m] < 'z'){
			offset = word[m] * ((m_fontSize / 8) - 1) * m_fontSize;
			Lib = getAsciiLib(offset, ((m_fontSize / 8)-1) * m_fontSize);
			m += 1;// ����ƶ�һ���ֽ�
		}
		else{
			offset = (94 * (word[m] - 0xA0 - 1) + (word[m + 1] - 0xA0 - 1)) * 32;
			if (m_fontSize == 24) offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //�����24����������ƫ��������
			Lib = getHzkLib(offset, m_fontSize * m_fontSize / 8);
			m += 2;// ���Ų�����ֽ�
		}
	}

	return Lib;
}

bool CMyFont::openAsc(){
	if (m_fontSize == 16)
		fileAsc = fopen("ASC16", "rb");
	else
		fileAsc = fopen("ASC24", "rb");
	if (fileAsc == NULL)
	{
		return false;
	}
}

bool CMyFont::openHzk(CString m_selectfonts){
	// ���û�������ѡ������ʹ�С�ϲ�Ϊ�ַ������Դ��ļ�
	CString i;
	i.Format("%d", m_fontSize);
	m_selectfonts += i;
	fileHzk = fopen(m_selectfonts, "rb");

	if (fileHzk == NULL){
		return false;
	}
}

// ����ȡģ���㷨
char CMyFont::shift_value(char org, int index)
{
	org = (org & (0x1 << index)) >> index;
	return org;
}
void CMyFont::transverse_modulus(unsigned char org[][2], unsigned char* re,int x,int y)
{
	char **tmp = (char **)malloc(sizeof(char*)*x);	// ����һ��ָ��ָ���ָ��
	for (i = 0; i < x; i++){
		tmp[i] = (char *)malloc(sizeof(char)*y);
	}
	int j = 0, n = 0, column = 0;
	for (; j< x; j++)
	{
		int i = 0, index = 0;
		for (; i< y; i++)
		{
			if (i % 2 != 0)
			{
				n = 1;
			}
			else
			{
				n = 0;
			}
			tmp[j][i] = (shift_value(org[(1 - n) * 8][column], 7 - index) << 0) | \
				(shift_value(org[(1 - n) * 8 + 1][column], 7 - index) << 1) | \
				(shift_value(org[(1 - n) * 8 + 2][column], 7 - index) << 2) | \
				(shift_value(org[(1 - n) * 8 + 3][column], 7 - index) << 3) | \
				(shift_value(org[(1 - n) * 8 + 4][column], 7 - index) << 4) | \
				(shift_value(org[(1 - n) * 8 + 5][column], 7 - index) << 5) | \
				(shift_value(org[(1 - n) * 8 + 6][column], 7 - index) << 6) | \
				(shift_value(org[(1 - n) * 8 + 7][column], 7 - index) << 7);
			if (i % 2 != 0)
				index++;
		}
		column++;
	}

	memcpy(re, tmp, 32);
}
// ����ȡģ�㷨����
void CMyFont::transverse_modulus(unsigned char org[][3], unsigned char* re, int x, int y)
{
	char tmp[2][16];
	int j = 0, n = 0, column = 0;
	for (; j<x; j++)
	{
		int i = 0, index = 0;
		for (; i< y; i++)
		{
			if (i % 2 != 0)
			{
				n = 1;
			}
			else
			{
				n = 0;
			}
			tmp[j][i] = (shift_value(org[(1 - n) * 8][column], 7 - index) << 0) | \
				(shift_value(org[(1 - n) * 8 + 1][column], 7 - index) << 1) | \
				(shift_value(org[(1 - n) * 8 + 2][column], 7 - index) << 2) | \
				(shift_value(org[(1 - n) * 8 + 3][column], 7 - index) << 3) | \
				(shift_value(org[(1 - n) * 8 + 4][column], 7 - index) << 4) | \
				(shift_value(org[(1 - n) * 8 + 5][column], 7 - index) << 5) | \
				(shift_value(org[(1 - n) * 8 + 6][column], 7 - index) << 6) | \
				(shift_value(org[(1 - n) * 8 + 7][column], 7 - index) << 7);
			if (i % 2 != 0)
				index++;
		}
		column++;
	}

	memcpy(re, tmp, 32);
}

// �ֽڵ����㷨
void  CMyFont::bit_reverse(unsigned char* word, unsigned char *retValue){
	int j = 0;
	while (word[j] != '\0')
	{
		int i;
		retValue[j] |= (word[j] & 1);
		for (i = 1; i < 8; i++)
		{
			retValue[j] <<= 1;
			retValue[j] |= (((1 << i) & word[j]) >> i);
		}
	}
}