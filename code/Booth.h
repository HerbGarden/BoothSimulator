//��ȣ��, ȸ���, �� �ҿ� ���밡�� �ο�, �� �� �� �ִ� ��� ��, ���� ���� �ð�
#include "stdafx.h"
#pragma once
#include "Human.h"

class Booth: public CObject{
public:
	CString comName; // ȸ���
	int preference; // ��ȣ�� 0~100
	int possibleCnt; // ���밡�� �ο�
	int useTime; // ��������ð�

	void setComName(CString);
	void setPreference(int );
	void setPossibleCnt(int );
	void setUseTime(int ime);
	Booth(CString, int, int, int, int, int);
	int XAnxis;
	int YAnxis;
	
	int ing[50];
	int ingcnt;
	int ingcnt2; //�����ϱ� ���� ��
	int line[100];
	int linecnt;
	int linecnt2; //������ ���� �ִ� ��
	int In_line(int num);
	int out_ing();

	int term;
	virtual void Serialize(CArchive& ar);
	 CArray<Human *, Human *> que_line;
	 CArray<Human *, Human *> in;
	 int in_que(Human *h);//����ٿ� ������� ���
	// void in_stand();//�ȿ��� Ȱ������ ���
	 void outtime_que(CArray<Human *, Human *> *p);//������ ����� ����
	 

	Booth(){term=0;}//���� �Ҵ�� ����Ʈ ������
};