#include "stdafx.h"
#include "Human.h"
/*class Boose{
public:
	int x,y,capa;

};*/

class Human{
private:
	int x,y;
	//CRgn pt; CheckRange
	//int CA_count;
	/*Boose tar;*/
	
	
public:
	
	CRect hp;
	//CArray<int,int>;


	void move(int m, int n){
		x += m;
		y += n;
		//getsize();
	}

	Human(){
		x=0;
		y=0;
	    getsize();
	}

	Human(int m, int n){
		x=m;
		y=n;
		getsize();
	}
	/*void Crasher(Human *g){
		pt.CreateEllipticRgnIndirect(hp);
		g->pt.CreateEllipticRgnIndirect(hp);
		int i= pt.CombineRgn(this,g,RGN_AND);
		if(i==0){
			printf("충돌하였습니다.");
		}
	}
	void TargetBoose(){
		tar=Booselist.ElementAt(0);
		Booselist.RemoveAt(0);
	}*/
	
	void getsize(){
		hp = CRect(x-10,y-10,x+10,y+10);
	}
};

*/