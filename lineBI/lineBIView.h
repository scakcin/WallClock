
// lineBIView.h : interface of the ClineBIView class
//

#pragma once
const UINT IDC_ROT{ 1000 };
const UINT IDC_EDT{ 1001 };
const UINT IDC_STP{ 1002 };

class ClineBIView : public CView
{
protected: // create from serialization only
	ClineBIView() noexcept;
	DECLARE_DYNCREATE(ClineBIView)

// Attributes
public:
	ClineBIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~ClineBIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void onbnclk();
	afx_msg void onstp();	
	DECLARE_MESSAGE_MAP()
private:
	CButton m_btn;
	CEdit m_edt;
	CButton m_stp;
	CStatic m_cs[12];
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void recrot(CDC* pDC, int dg);
	virtual void OnInitialUpdate();
	//virtual void createtxt();
};

#ifndef _DEBUG  // debug version in lineBIView.cpp
inline ClineBIDoc* ClineBIView::GetDocument() const
   { return reinterpret_cast<ClineBIDoc*>(m_pDocument); }
#endif

