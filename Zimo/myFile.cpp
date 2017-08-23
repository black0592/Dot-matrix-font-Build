/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		Font.cpp
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.11
* Description   ���ļ����������ʵ��
description
*******************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include "SET.h"
#include "myFile.h"
using namespace std;

myFile::myFile()
{

}

myFile::~myFile()
{

}

bool myFile::setPath(CString path){

	savePath = path;
	LPCTSTR p = savePath.GetBuffer(0);
	savePath.ReleaseBuffer();
	pszFileName = new char[savePath.GetLength() + 1];
	strcpy_s(pszFileName, savePath.GetLength() + 1, CT2CA(p));
	if (mysFile.Open(pszFileName, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite), &fileException)
		return TRUE;
	else
		return false;
	
}

// ���ݲ������ֽ�����������ļ�
bool myFile::outFile(unsigned char* word, int byteNumber){

	int k;
	strOrder.Format("unsigned char code key[%d] = {", byteNumber);
	mysFile.WriteString(strOrder);
	for (k = 0; k < byteNumber; k++){
		strOrder.Format("0x%02X,", word[k]);
		mysFile.WriteString(strOrder);
	}
	mysFile.WriteString("}\n");

	return TRUE;
}