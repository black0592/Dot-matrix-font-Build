/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		doFile.h
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.12
* Description   ͷ�ļ�������doFile.h
description     �ṩ���ļ��������������
*******************************************************************************/
#pragma once

class   myFile
{
public:
	myFile();
	~myFile();

	/* DESCRIPTION
	���ֿ�������ļ�
	* ARGUMENTS
	Argumegnt1          char* word
	* RETURN
	Return value        bool
	* NOTES
	Function note
	*/
	bool outFile(unsigned char*, int byteNumber);

	// �����ļ��洢·��
	bool setPath(CString path);
private:
	CStdioFile mysFile;
	CFileException fileException;
	CString strOrder;
	char * pszFileName;
	CString savePath;

};

