
// lineBIView.cpp : implementation of the ClineBIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lineBI.h"
#endif

#include "lineBIDoc.h"
#include "lineBIView.h"
#include <thread>
#include <functional>
#include <chrono>

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int deg = 6;
bool is_b=FALSE;
bool is_stp = FALSE;
int sx = 1000;
int sy = 500;
int len = 50;
int isx = 1000;
int isy = 350;
int imx = 1000;
int imy= 400;
int ihx = 1000;
int ihy = 450;
int ex(int dg,int inx,int iny);
int ey(int dg, int inx, int iny);
int dg = 0;
int mdg = 0;
int hdg = 0;






// ClineBIView

IMPLEMENT_DYNCREATE(ClineBIView, CView)

BEGIN_MESSAGE_MAP(ClineBIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ClineBIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_ROT,onbnclk)
	ON_BN_CLICKED(IDC_STP, onstp)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// ClineBIView construction/destruction

ClineBIView::ClineBIView() noexcept
{
	// TODO: add construction code here
	

}

ClineBIView::~ClineBIView()
{
}

BOOL ClineBIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	

	return CView::PreCreateWindow(cs);
}

// ClineBIView drawing

void ClineBIView::OnDraw(CDC* pDC)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));	
	CPoint cp(880, 315);
	CSize cs(150 * 1.414, 150 * 1.414);
	//CPoint cpr(1)
	CRect rec(cp, cs);	
	CPen* cpOldPen = pDC->SelectObject(&cpen);
	pDC->Ellipse(rec);
	CTime time = CTime::GetCurrentTime();
	int nSecond = time.GetSecond();
	int nMinute = time.GetMinute();
	int nHour = time.GetHour() % 12;
	
	
	dg = 6 * nSecond;
	mdg = 6 * nMinute+nSecond/10;
	hdg = 30 * nHour+nMinute/2;
	
	SetTimer(1, 1000, NULL);
	CPen txtpen;
	txtpen.CreatePen(PS_SOLID, 5, RGB(100, 101,104));
	
	CSize tcs(10, 5);	
	CPen* txtpOldPen = pDC->SelectObject(&txtpen);
	int tdeg = 0;
	pDC->TextOut(isx-10, isy-20, L"12");
	for (int i = 1; i <12; i++) {
		tdeg += 30;
		CString l;
		l.Format(L"%d",i);
		CPoint tcp(ex(tdeg, isx+10, isy - 20), ey(tdeg, isx+10, isy - 20));
		pDC->TextOut(tcp.x, tcp.y, l);
	}
	
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);
	// Select the pen into the device context
	
	
	pDC->MoveTo(sx, sy);
	pDC->LineTo(ex(dg, isx, isy), ey(dg, isx, isy));
		
	dg += deg;
	if (1) {
		CPen mpen;
		mpen.CreatePen(PS_SOLID, 7, RGB(0, 255, 0));
		CPen* mpOldPen = pDC->SelectObject(&mpen);
		pDC->MoveTo(sx, sy);
		pDC->LineTo(ex(mdg, imx, imy), ey(mdg, imx, imy));
		/*if (dg % 360 == 0) {
			pDC->MoveTo(sx, sy);
			pDC->LineTo(ex(mdg += 6, imx, imy), ey(mdg += 6, imx, imy));	
		}*/
	}
	if (1) {
		CPen hpen;
		hpen.CreatePen(PS_SOLID, 10, RGB(150, 0, 255));
		CPen* hpOldPen = pDC->SelectObject(&hpen);
		pDC->MoveTo(sx, sy);
		pDC->LineTo(ex(hdg, ihx, ihy), ey(hdg, ihx, ihy));
				
		/*if (dg % 2160  == 0) {
			pDC->MoveTo(sx, sy);
			pDC->LineTo(ex(hdg += 6, ihx, ihy), ey(hdg += 6, ihx, ihy));
		}*/
	}
	
	
	
	ClineBIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
}


// ClineBIView printing


void ClineBIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL ClineBIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void ClineBIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void ClineBIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void ClineBIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void ClineBIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ClineBIView diagnostics

#ifdef _DEBUG
void ClineBIView::AssertValid() const
{
	CView::AssertValid();
}

void ClineBIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

ClineBIDoc* ClineBIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ClineBIDoc)));
	return (ClineBIDoc*)m_pDocument;
}
#endif //_DEBUG


// ClineBIView message handlers


int ClineBIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rec;
	//m_btn.Create(_T("Rotate"), BS_PUSHBUTTON, CRect(10, 600, 100, 650),this,IDC_ROT);
	//m_edt.Create(ES_NUMBER| WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(10,10,50,30), this, IDC_EDT);
	//m_stp.Create(_T("Stop"), BS_PUSHBUTTON, CRect(200, 600, 300, 650), this, IDC_ROT);	
	//m_btn.ShowWindow(SW_SHOW);
	//m_stp.ShowWindow(SW_SHOW);
	
	return 0;
}

void ClineBIView::onbnclk() {
	//CString degs;
	//m_edt.GetWindowText(degs);

	//deg = _ttoi(degs);
	//AfxMessageBox(degs);
	
	is_b = !is_b;

	//Invalidate();
	

}

void ClineBIView::onstp() {
	is_stp = TRUE;
	is_b = FALSE;

	
}

int ex(int dg, int inx, int iny) {
	double radian = dg * 0.01745;
	return (int)(sx + ((inx - sx) * cos(radian) - (iny - sy) * sin(radian)));
}
int ey(int dg, int inx, int iny) {
	double radian = dg * 0.01745;
	return (int)(sy + ((inx - sx) * sin(radian) + (iny - sy) * cos(radian)));
}

//void ClineBIView::recrot(CDC * pDC,int dg) {
//	
//	CPoint tl = (100,100);
//	CPoint br = (60, 700);
//	CSize sz = (1000, 1000);
//	CRect rec(tl,sz);
//	while (dg < 360) {
//		dg += deg;
//		pDC->MoveTo(sx, sy);
//		pDC->LineTo(ex(dg, ix, iy), ey(dg, ix, iy));
//		InvalidateRect(rec,0);	
//		UpdateWindow();
//	}
//}





void ClineBIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
		
		Invalidate(); // Invalidate the window to trigger a redraw
	
}


void ClineBIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//SetTimer(1, 5000, NULL);

	
}


