/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		SET.cpp
* Author 	gaoshuo
* Version 	1.2
* Date   	16.7.11
* Description   �������öԻ���
description
*******************************************************************************/

#include "stdafx.h"
#include "Zimo.h"
#include "SET.h"
#include "afxdialogex.h"
using namespace std;

// CSET �Ի���


CSET::CSET(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSET::IDD, pParent)
	, m_CBfonts(_T(""))
	, m_editSavepath(_T(""))
	, m_CB_ModelSave(0)
	, m_combo_FontSize(0)
{

}
CSET::~CSET()
{
}

void CSET::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_CBfonts);
	DDX_Control(pDX, IDC_COMBO1, m_comboxFonts);
	DDX_Text(pDX, IDC_SAVE_EDIT, m_editSavepath);
	DDX_CBIndex(pDX, IDC_COMBO_ModelSave, m_CB_ModelSave);
	DDX_Control(pDX, IDC_COMBO_ModelSave, m_comboModelWay);
	DDX_Control(pDX, IDC_COMBO_FontSize, m_CB_FontSize);
	DDX_CBIndex(pDX, IDC_COMBO_FontSize, m_combo_FontSize);
}

IMPLEMENT_DYNAMIC(CSET, CDialogEx)
BEGIN_MESSAGE_MAP(CSET, CDialogEx)
	
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSET::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CSET::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CSET::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// CSET ��Ϣ�������

void CSET::OnLbnSelchangeList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CSET::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

CString m_selectfonts;
int selectfonts;
int m_fontSize;
int m_CB_ModelSave;
void CSET::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����������
	UpdateData(TRUE);

	// ���û���ѡ��浽��ȫ�ֱ�����
	selectfonts	= m_comboxFonts.GetCurSel();
	GetDlgItemText(IDC_COMBO1, m_selectfonts);       // ��ȡѡ���б�����ַ��� 
	m_CB_ModelSave	= m_comboModelWay.GetCurSel();
	switch (m_combo_FontSize = m_CB_FontSize.GetCurSel()){
	case 0:
		m_fontSize = 16;
	case 1:
		m_fontSize = 24;
	}

	CDialogEx::OnOK();

}

//����ĳ�ʼ������
BOOL CSET::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// Ϊ����ѡ����Ͽ�ؼ����б������б��� ����   
	m_comboxFonts.AddString(_T("����"));
	m_comboxFonts.AddString(_T("����"));
	m_comboxFonts.AddString(_T("����"));
	m_comboxFonts.AddString(_T("����"));
	m_comboxFonts.AddString(_T("����"));  
	m_comboxFonts.SetCurSel(0);	//Ĭ��ѡ������

	// Ϊȡģ��ʽ��Ͽ�ؼ�����б���
	m_comboModelWay.AddString("����ȡģ���ֽ�����");
	m_comboModelWay.AddString("����ȡģ���ֽڵ���");
	m_comboModelWay.AddString("����ȡģ���ֽ�����");
	m_comboModelWay.AddString("����ȡģ���ֽڵ���");
	m_comboModelWay.SetCurSel(0);	//Ĭ��ѡ�����ȡģ���ֽ�����

	// Ϊ�����С��Ͽ�ؼ�����б���
	m_CB_FontSize.AddString("16*16��Ӣ��8*16��");
	m_CB_FontSize.AddString("24*24��Ӣ��16*24��");
	m_CB_FontSize.SetCurSel(0);	// Ĭ��ѡ��16*16

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

CString	m_SavePath;
//SAVEBUTTON���¼��������ļ�
void CSET::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("C�����ļ�|*.c|�ı��ļ�(*.txt)|*.txt|");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("��ģ"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
		m_SavePath = strFilePath;
	}
}
