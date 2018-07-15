
// BoothInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BoothInfo.h"
#include "Booth.h"
#include <Shlwapi.h>
#include "MainFrm.h"


// CBoothInfo

IMPLEMENT_DYNCREATE(CBoothInfo, CView)

CBoothInfo::CBoothInfo()
{
	m_ClickState=INFONOTTING;
	m_selectState=1;
	rSetting.SetRect(0,330,150,400);
	rDelete.SetRect(150,330,300,400);
	index=-1;
	
}

CBoothInfo::~CBoothInfo()
{
	
}
void CBoothInfo::OnInitialUpdate()
{
}

BEGIN_MESSAGE_MAP(CBoothInfo, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CBoothInfo 그리기입니다.

void CBoothInfo::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap,bitmap1,bitmap2;
	CBitmap *pOldBitmap;

			
	bitmap.LoadBitmap(IDB_Info);
	pOldBitmap = (CBitmap *) memDC.SelectObject(&bitmap);
	pDC->BitBlt(0, 0, 300, 400, &memDC, 0, 0, SRCCOPY); 
	memDC.SelectObject(pOldBitmap);
	
	bitmap.DeleteObject();
	switch (m_ClickState){
		case INFOSETTING:
			bitmap1.LoadBitmap(IDB_Setting);
			pOldBitmap = (CBitmap *) memDC.SelectObject(&bitmap1);
			pDC->BitBlt(25, 333, 125, 400, &memDC, 0, 0, SRCCOPY); 
			memDC.SelectObject(pOldBitmap);
			break;
		case INFODELETE:
			bitmap1.LoadBitmap(IDB_Delete);
			pOldBitmap = (CBitmap *) memDC.SelectObject(&bitmap1);
			pDC->BitBlt(177, 330, 275, 400, &memDC, 0, 0, SRCCOPY); 
			memDC.SelectObject(pOldBitmap);
			break;
		case INFONOTTING:
			break;
	}

	

	
	if(m_selectState==INFO){
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(160,70,Name);
		pDC->TextOut(160,132,Pre);
		pDC->TextOut(160,197,InPeo);
		pDC->TextOut(160,260,Time);

	}

	memDC.DeleteDC();
	bitmap1.DeleteObject();
	bitmap2.DeleteObject();
}


// CBoothInfo 진단입니다.

#ifdef _DEBUG
void CBoothInfo::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBoothInfo::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBoothInfo 메시지 처리기입니다.


void CBoothInfo::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	

	if(rSetting.PtInRect(point)){
		m_ClickState=INFOSETTING;
	}
	if(rDelete.PtInRect(point)){
		m_ClickState=INFODELETE;
	}

	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}


void CBoothInfo::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CProjectDoc* pDoc = dynamic_cast<CProjectDoc*>(GetDocument());	

	if(rSetting.PtInRect(point)){
		if(m_selectState==INFODEFAULT){
			MessageBox(_T("선택된 부스가 없습니다."),_T("오류"),NULL);
		}
		if(m_selectState==INFO){
			if(pDoc->m_array[index]->map_ID == 'B'){				
				int booth_ID = pDoc->m_array[index]->booth_ID ;

				BI.Name = pDoc->b_array[booth_ID]->comName;
				BI.possibleCnt = pDoc->b_array[booth_ID]->possibleCnt;
				BI.useTime = pDoc->b_array[booth_ID]->useTime;

				if(BI.DoModal() == IDOK){
					pDoc->b_array.SetAt(booth_ID, new Booth(BI.Name, pDoc->b_array[booth_ID]->preference, BI.possibleCnt, BI.useTime, pDoc->b_array[booth_ID]->XAnxis, pDoc->b_array[booth_ID]->YAnxis));
				}
				SetStr();
			}
		}	
	}

	if(rDelete.PtInRect(point)){
		if(m_selectState==INFODEFAULT){
			MessageBox(_T("선택된 부스가 없습니다."),_T("오류"),NULL);
		}
		if(m_selectState==INFO){
			pDoc->m_array[index]->map_ID = 'R';
			pDoc->b_array.RemoveAt(pDoc->m_array[index]->booth_ID);
			for(int indexcnt=0; indexcnt<pDoc->X*pDoc->Y; indexcnt++){
				if(pDoc->m_array[indexcnt]->booth_ID > pDoc->m_array[index]->booth_ID)
					pDoc->m_array[indexcnt]->booth_ID -= 1;
			}
			pDoc->m_array[index]->booth_ID = -10;
			Name.Format(_T("%s"), "");
			Time.Format(_T("%s"),"");
			Pre.Format(_T("%s"),"");
			InPeo.Format(_T("%s"),"");
			m_selectState=1;
			MessageBox(_T("선택된 부스가 삭제되었습니다."),_T("알림"),NULL);
		}
	}

	
	m_ClickState=INFONOTTING;
	Invalidate(FALSE);
	
	CView::OnLButtonUp(nFlags, point);
}

void CBoothInfo::mainFrmEvent(){
	
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	index=pFrame->pView->index;
	SetStr();
	m_selectState=2;
	

	Invalidate(FALSE);
}

void CBoothInfo::SetStr(){
	CProjectDoc* pDoc = dynamic_cast<CProjectDoc*>(GetDocument());
	int booth_ID = pDoc->m_array[index]->booth_ID ;

	Name.Format(_T("%s"),pDoc->b_array[booth_ID]->comName);
	Time.Format(_T("%d"),pDoc->b_array[booth_ID]->useTime);
	Pre.Format(_T("%d"),pDoc->b_array[booth_ID]->preference);
	InPeo.Format(_T("%d"),pDoc->b_array[booth_ID]->possibleCnt);
}
