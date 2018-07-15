//선호도, 회사명, 한 텀에 수용가능 인원, 줄 설 수 있는 사람 수, 예상 관람 시간
#include "stdafx.h"
#pragma once
#include "Human.h"

class Booth: public CObject{
public:
	CString comName; // 회사명
	int preference; // 선호도 0~100
	int possibleCnt; // 수용가능 인원
	int useTime; // 예상관람시간

	void setComName(CString);
	void setPreference(int );
	void setPossibleCnt(int );
	void setUseTime(int ime);
	Booth(CString, int, int, int, int, int);
	int XAnxis;
	int YAnxis;
	
	int ing[50];
	int ingcnt;
	int ingcnt2; //배출하기 위한 값
	int line[100];
	int linecnt;
	int linecnt2; //실제로 갖고 있는 값
	int In_line(int num);
	int out_ing();

	int term;
	virtual void Serialize(CArchive& ar);
	 CArray<Human *, Human *> que_line;
	 CArray<Human *, Human *> in;
	 int in_que(Human *h);//대기줄에 대기중인 사람
	// void in_stand();//안에서 활동중인 사람
	 void outtime_que(CArray<Human *, Human *> *p);//관람과 대기줄 방출
	 

	Booth(){term=0;}//저장 할당용 디폴트 생성자
};