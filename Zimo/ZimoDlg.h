
// ZimoDlg.h : ͷ�ļ�
//

#pragma once


// CZimoDlg �Ի���
class CZimoDlg : public CDialogEx
{
// ����
public:
	CZimoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZIMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_editInput;
	CString m_editOutput;
	CString m_displayMatrix;
	afx_msg void OnBnClickedBeginButton();
	afx_msg void OnEnChangeInputEdit(); //����༭���ַ��ı���Ӧ����


	afx_msg void OnBnClickedButton1();
	CString readFilePath;
	afx_msg void OnBnClickedOpenFileButton();
	afx_msg void OnBnClickedOpenfileButton();
};
