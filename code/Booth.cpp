
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

//원하는 도착지에 도착했을때 해당 부스의 함수를 호출, 
//0이 리턴되면 해당 부스 선호도 재점검 및 다음 부스로 이동, 대기줄에 못들어간것 표시

int Booth::in_que(Human *h){
	if(possibleCnt*10>que_line.GetCount()){//수용 가능 인원의 10배 까지
		//h->hp.MoveToXY(-100,-100);
		que_line.Add(h);
		return 1;//인큐에 성공, 성공시 이동 어레이에서 제외하셈
	}
	else{
		return 0;//인큐에 실패, 실패시 해당 부스를 다시 갈지 말지 원트리스트에 다시 넣으셈?
	}
}

void Booth::outtime_que(CArray<Human *, Human *> *p){//타이머 마다 모든 부스에서 호출해주셈 젤 첫번째로

	
	if(term==useTime){
		//이동어레이에 in 어레이 객체 모두 넘김
		for(int i=0; i<in.GetCount(); i++){
			/*이동어레이.Add*/p->Add(in.GetAt(i));//이부분에서 이동어레이로 넘기고
			in.RemoveAt(i);//이부분에서 방출, 방출 이후 포인터
		}
		for(int i =0; i<possibleCnt && i <que_line.GetCount();i++){
			in.Add(que_line.GetAt(i));//대기열에서 받아옴
			que_line.RemoveAt(i);//대기열에서 제거
		}
		term=0;
	}
	else if(in.GetCount()>0){//사람이 있을때
		term++;
	}//시간 측정
	else if(in.GetCount()==0 && term==0){//시작에 사람이 없을때 
		if(que_line.GetCount()!=0){
			for(int i =0; i<possibleCnt && i <que_line.GetCount();i++){
			in.Add(que_line.GetAt(i));//대기열에서 받아옴
			que_line.RemoveAt(i);//대기열에서 제거
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