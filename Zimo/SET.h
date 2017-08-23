#pragma once
#include "afxwin.h"
#include "resource.h"

// CSET �Ի���

class CSET : public CDialogEx
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSET();

// �Ի�������
	enum { IDD = IDD_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo1();
	// ����������
	CString m_CBfonts;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_comboxFonts;
	afx_msg void OnBnClickedSaveButton();
	CString m_editSavepath;
	int m_CB_ModelSave;
	CComboBox m_comboModelWay;
	CComboBox m_CB_FontSize;
	int m_combo_FontSize;
};

extern  CString m_editSavepath;
extern  CString	m_SavePath;
extern  CString m_selectfonts;
extern  int m_fontSize;
extern  int m_CB_ModelSave;