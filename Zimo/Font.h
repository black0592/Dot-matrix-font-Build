/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		Font.h
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.11
* Description   ͷ�ļ�������Font.h
description     �ṩ���ֿ�������������
*******************************************************************************/
#pragma once

//�������
class CMyFont
{
public:
	//���캯��
	CMyFont();
	//��������
	~CMyFont();

	/* DESCRIPTION
	����Ӣ���ֿ�
	* ARGUMENTS
	Argumegnt1          int offset
	* RETURN
	Return value        unsigned char* 
	* NOTES
	Function note
	*/
	unsigned char* getAsciiLib(int offset, int byteNumber);
	unsigned char* getHzkLib(int offset, int byteNumber);

	/* DESCRIPTION
	�����ַ����ֿ��е�ƫ������������ֿ�
	* ARGUMENTS
	Argumegnt1          char* word
	* RETURN
	Return value        int offset
	* NOTES
	Function note
	*/
	unsigned char* getLib(unsigned char* word);

	bool openHzk(CString m_selectfonts);
	bool openAsc();

	/* DESCRIPTION
	������ȡģתΪ����ȡģ
	* ARGUMENTS
	Argumegnt1          unsigned char org[][2], unsigned char* re
	* RETURN
	Return value        void
	* NOTES
	Function note
	*/
	char shift_value(char org, int index);
	void transverse_modulus(unsigned char org[][2], unsigned char* re, int x, int y);
	void transverse_modulus(unsigned char org[][3], unsigned char* re, int x, int y);

	// �ֽڵ���
	void bit_reverse(unsigned char* word, unsigned char *retValue);
private:
	FILE* fileHzk;		// Hzk�ļ�ָ��
	FILE* fileAsc;		// Asc�ļ�ָ��
	int i, j, k, offset;	// ƫ����

	
	unsigned char asciiLib[16];
	unsigned char hzkLib[32];
};

