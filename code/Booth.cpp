
#include "stdafx.h"
#include "Booth.h"

Booth::Booth(CString A, int B, int C, int D, int E, int F){
	comName = A;
	preference = B;
	possibleCnt = C;
	useTime = D;
	XAnxis = E;
	YAnxis = F;
	ingcnt = 0;
	linecnt = 0;
	linecnt2 = 0;
	term = 0;
	
	for(int boothcnt=0; boothcnt < 50; boothcnt ++){
		ing[boothcnt] = -1;
	}
	for(int boothcnt=0; boothcnt < 100; boothcnt ++){
		line[boothcnt] = -1;
	}
}

void Booth::setComName(CString name){
	comName = name;
}

void Booth::setPreference(int Pre){
	if(Pre<=0)
		Pre=0;
	else if(Pre>=100)
		Pre=100;

	preference=Pre;
}

void Booth::setPossibleCnt(int Pos){
	possibleCnt=Pos;
}

void Booth::setUseTime(int Time){
	useTime=Time;
}

void Booth::Serialize(CArchive& ar){
	CObject::Serialize( ar );

    if (ar.IsStoring())
    {         
        ar << comName << preference << possibleCnt << useTime<<XAnxis<<YAnxis;
    }
    else 
    {   
        ar >> comName >> preference >> possibleCnt >> useTime>>XAnxis>>YAnxis;
    }   
}

//���ϴ� �������� ���������� �ش� �ν��� �Լ��� ȣ��, 
//0�� ���ϵǸ� �ش� �ν� ��ȣ�� ������ �� ���� �ν��� �̵�, ����ٿ� ������ ǥ��

int Booth::in_que(Human *h){
	if(possibleCnt*10>que_line.GetCount()){//���� ���� �ο��� 10�� ����
		//h->hp.MoveToXY(-100,-100);
		que_line.Add(h);
		return 1;//��ť�� ����, ������ �̵� ��̿��� �����ϼ�
	}
	else{
		return 0;//��ť�� ����, ���н� �ش� �ν��� �ٽ� ���� ���� ��Ʈ����Ʈ�� �ٽ� ������?
	}
}

void Booth::outtime_que(CArray<Human *, Human *> *p){//Ÿ�̸� ���� ��� �ν����� ȣ�����ּ� �� ù��°��

	
	if(term==useTime){
		//�̵���̿� in ��� ��ü ��� �ѱ�
		for(int i=0; i<in.GetCount(); i++){
			/*�̵����.Add*/p->Add(in.GetAt(i));//�̺κп��� �̵���̷� �ѱ��
			in.RemoveAt(i);//�̺κп��� ����, ���� ���� ������
		}
		for(int i =0; i<possibleCnt && i <que_line.GetCount();i++){
			in.Add(que_line.GetAt(i));//��⿭���� �޾ƿ�
			que_line.RemoveAt(i);//��⿭���� ����
		}
		term=0;
	}
	else if(in.GetCount()>0){//����� ������
		term++;
	}//�ð� ����
	else if(in.GetCount()==0 && term==0){//���ۿ� ����� ������ 
		if(que_line.GetCount()!=0){
			for(int i =0; i<possibleCnt && i <que_line.GetCount();i++){
			in.Add(que_line.GetAt(i));//��⿭���� �޾ƿ�
			que_line.RemoveAt(i);//��⿭���� ����
			}
		}
		else{return;}
	}
}

int Booth::In_line(int num){
	if(linecnt2 <= possibleCnt*2){
		line[linecnt] = num;
		linecnt = (linecnt +1)%100;
		linecnt2 ++;
		return 1;
	}
	else 
		return 0;
}

int Booth::out_ing(){
	if(term >= useTime*20){
		if(ingcnt2 == ingcnt){
			term = 0;
			return -1;
		}
		else{
			return ing[ingcnt2++];
		}
	}
	else if(term == 0){
		for(int termcnt = 0; termcnt < ingcnt; termcnt ++){
			ing[termcnt] = -1;
		}
		ingcnt = 0;
		ingcnt2 = 0;
		if(linecnt2 > 0){
			if(linecnt2 < possibleCnt){
				for(int termcnt = 0; termcnt < linecnt2; termcnt ++){
					if(linecnt-1-termcnt > 0){
						ing[termcnt] = line[linecnt-1-termcnt];
						line[linecnt-1-termcnt] = -1;
					}else{
						ing[termcnt] = line[linecnt-1-termcnt+99];
						line[linecnt-1-termcnt] = -1;
					}
					ingcnt ++;
				}
				linecnt2 = 0;
			}
			else{
				for(int termcnt = 0; termcnt < possibleCnt; termcnt ++){
					if(linecnt-1-termcnt > 0){
						ing[termcnt] = line[(linecnt-1)-termcnt];
						line[linecnt-1-termcnt] = -1;
					}
					else{
						ing[termcnt] = line[linecnt-1-termcnt+99];
						line[linecnt-1-termcnt] = -1;
					}
					ingcnt ++;
				}
				linecnt2 -= possibleCnt;
			}
		}
		term ++;
		return -1;
	}
	else if(ing > 0 || term > 0){
		term ++;
		return -1;
	}
}