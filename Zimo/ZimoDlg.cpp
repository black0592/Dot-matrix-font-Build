/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		ZimoDlg.cpp
* Author 	gaoshuo
* Version 	1.2
* Date   	16.7.12
* Description   ���������Ӧ��
description
*******************************************************************************/

#include <stdio.h>
#include "stdafx.h"
#include "Zimo.h"
#include "ZimoDlg.h"
#include "afxdialogex.h"
#include "SET.h"
#include "Font.h"
#include  "myFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<stdio.h>#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fstream>
using namespace std;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx 
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CZimoDlg �Ի���

CZimoDlg::CZimoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZimoDlg::IDD, pParent)
	, m_editInput(_T(""))   //��ʼֵ
	, m_editOutput(_T(""))
	, readFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZimoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_EDIT, m_editInput);
	DDX_Text(pDX, IDC_OUTPUT_EDIT, m_editOutput);
	DDX_Text(pDX, IDC_EDIT_SAVE, readFilePath);
}

BEGIN_MESSAGE_MAP(CZimoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEGIN_BUTTON, &CZimoDlg::OnBnClickedBeginButton)
	ON_EN_CHANGE(IDC_INPUT_EDIT, &CZimoDlg::OnEnChangeInputEdit)
	ON_BN_CLICKED(IDC_BUTTON1, &CZimoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OpenFile_Button, &CZimoDlg::OnBnClickedOpenfileButton)
END_MESSAGE_MAP()


// CZimoDlg ��Ϣ�������

BOOL CZimoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{						
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZimoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZimoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZimoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZimoDlg::OnBnClickedBeginButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ǵ�������
	INT_PTR	nRES;		//��������Domodel�ķ���ֵ

	CSET set;              //�����Ի�����CSET���ʵ��

	nRES = set.DoModal();	//�����Ի���
	if (IDCANCEL == nRES)
	{
		//�������ֵΪIDCANCEL  ��return
		return;
	}

	//���ؼ������ַ����ݸ�����
	UpdateData(TRUE);
	
	//
	unsigned char word[100] = {0};
	memcpy(word, (unsigned char *)m_editInput.GetBuffer(0), m_editInput.GetLength() * 2);

	//ʵ����
	CMyFont myFont;
	myFile	myFile;
	int m = 0;
	int offset;
	unsigned char* Lib = NULL;
	myFile.setPath(m_SavePath);
	while (word[m] != '\0'){
		if (word[m]>'A' && word[m]<'z'){
			offset = word[m] * 16;
			Lib = myFont.getAsciiLib(offset, ((m_fontSize / 8) - 1) * m_fontSize);
			myFile.outFile(Lib, ((m_fontSize / 8) - 1) * m_fontSize);
			m += 1;		//����ƶ�һ���ֽ�
		}
		else{
			offset = (94 * (word[m] - 0xa0 - 1) + (word[m + 1] - 0xa0 - 1)) * 32;
			if (m_fontSize == 24)
				offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //�����24����������ƫ��������
			Lib = myFont.getHzkLib(offset, m_fontSize * m_fontSize / 8);
			myFile.outFile(Lib, m_fontSize * m_fontSize / 8);
			m += 2;		//����ƶ������ֽ�
		}
	}
	MessageBox("ת���ɹ�", "��ʾ");
	

}

//��������ʱ����Ӧ
void CZimoDlg::OnEnChangeInputEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//UpdateData(TRUE);

	//��������ַ��ı䣬��ʾ����֮�ı�
	//SetDlgItemText(IDC_OUTPUT_EDIT, i);
	
}

//����ļ��Ĵ������ļ��Ի���
void CZimoDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�|*.txt|c�����ļ�(*.c)|*.txt|");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("c"), _T("�ַ�"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_SAVE, strFilePath);
	}
}

void CZimoDlg::OnBnClickedOpenfileButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ǵ�������
	INT_PTR	nRES;		//��������Domodel�ķ���ֵ

	CSET set;              //�����Ի�����CSET���ʵ��

	nRES = set.DoModal();	//�����Ի���
	if (IDCANCEL == nRES)
	{
		//�������ֵΪIDCANCEL  ��return
		return;
	}

	//���ؼ������ַ����ݸ�����
	UpdateData(TRUE);

	unsigned char word[100] = { 0 };
	memcpy(word, (unsigned char *)m_editInput.GetBuffer(0), m_editInput.GetLength() * 2);
	int m = 0;
	int offset;
	unsigned char* Lib = NULL;

	//ʵ����
	CMyFont myFont;
	myFile	myFile;

	ifstream in(readFilePath);
	in >> word;
	while (word[m] != '\0'){
		if (word[m]>'A' && word[m]<'z'){
			offset = word[m] * 16;
			Lib = myFont.getAsciiLib(offset, ((m_fontSize / 8) - 1) * m_fontSize);
			myFile.outFile(Lib, 1);
			m += 1;		//����ƶ�һ���ֽ�
		}
		else{
			offset = (94 * (word[m] - 0xa0 - 1) + (word[m + 1] - 0xa0 - 1)) * 32;
			if (m_fontSize == 24)
				offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //�����24����������ƫ��������
			Lib = myFont.getHzkLib(offset, m_fontSize * m_fontSize / 8);
			myFile.outFile(Lib, 2);
			m += 2;		//����ƶ������ֽ�
		}
	}

	MessageBox("ת���ɹ�", "��ʾ");
}



