#pragma once
#include "stdafx.h"
class Human{

public:
	CRect hp;
	CPoint nowPoint;
	CPoint NextPoint;
	bool IsPoint;
	bool IsPlaying;

	void move(){
		nowPoint += CPoint(-5 + rand()%11,-5 + rand()%11);
		moveRect(nowPoint);
	}

	void move(int a, int b){
		nowPoint.x += a;
		nowPoint.y += b;
		moveRect(nowPoint);
	}
	
	void move(int Width, int XSize, int YSize, int wantbooth){
		if(IsPoint){
			if(nowPoint.x > NextPoint.x)
				nowPoint.x -= rand()%3;
			else if(nowPoint.x < NextPoint.x)
				nowPoint.x += rand()%3;

			if(nowPoint.y > NextPoint.y)
				nowPoint.y -= rand()%3;
			else if(nowPoint.y < NextPoint.y)
				nowPoint.y += rand()%3;
			else if(nowPoint == NextPoint)	
				IsPoint = false;

			moveRect(nowPoint);
		} 
			/*if(nextPoint[0].GetCount() != 0){
				NextPoint.x = (nextPoint[0][0]%Width)*XSize + rand()%XSize;
				NextPoint.y = (nextPoint[0][0]/Width)*YSize + rand()%YSize;

				nextPoint[0].RemoveAt(0);
				IsPoint = true;
			}*/ //������ ������ �� �κ�
	}

	Human(){
		nowPoint = (0, 0);
	    hp = CRect(-10, -10, 10, 10);
		IsPoint = false;
		IsPlaying = false;
	}

	Human(int m, int n, int booth, int nextmove){
		nowPoint = CPoint(m, n);
	    hp = CRect(-10, -10, 10, 10);
		moveRect(nowPoint);

		IsPoint = false;
		IsPlaying = false;
	}

	Human(int m, int n){
		nowPoint = CPoint(m, n);
	    hp = CRect(-10, -10, 10, 10);
		moveRect(nowPoint);

		IsPoint = false;
		IsPlaying = false;
	}
	
	void moveRect(CPoint v){
		hp.MoveToXY(v);
	}
};

class Check{
public:
	int prefer;
	int booth_ID;
	Check(int A, int B){
		prefer = A;
		booth_ID = B;
	}
};

class MapInfo : public CObject{
public :
	char map_ID; // ���� ��ġ�� ���� (S = ����, E = ��, D = ���Ա�, R = ����, B = �ν�)
	int booth_ID; // ���� ��ġ�� �ν���� ��ġ�� �ν��� �ѹ� �ƴҰ�� -1, -2, -3 ����, ��, ���Ա�
	MapInfo(char A, int B){
		map_ID = A;
		booth_ID = B;
	}
	virtual void Serialize(CArchive& ar){
		CObject::Serialize( ar );

    if (ar.IsStoring())
    {   
        //ar.SerializeClass(MapInfo::GetRuntimeClass());      
        ar << map_ID << booth_ID;
    }
    else 
    {
        //ar.SerializeClass(MapInfo::GetRuntimeClass());
        ar >> map_ID >> booth_ID;
    }   
	}
	MapInfo(){};
};

class mNode{
public:
	int F, G, H, now, target;
	mNode *bNode;

	mNode(int A, int B, int point, mNode *bN, int point2 ){
		G = A;
		H = B;
		target = point2;
		now = point;
		F = G + H;
		bNode = bN;
	}

	mNode(mNode &A){
		F = A.F;
		G = A.G;
		H = A.H;
		now = A.now;
		target = A.target;
		bNode = A.bNode;
	}

	//�ν� ���� ������ �޾� �� ��� �� CArray �� ���� ( ���� )
	/*CArray<mNode *, mNode *> *setNextNode(CArray<MapInfo *, MapInfo *> &map, int Width, int Height){
		CArray <mNode *, mNode *> rNode;

		for(int X=-1; X<2; X++){
			for(int Y=-1; Y<2; Y++){
				if(X == 0 && Y == 0) continue;
				else if(now+(Width*Y) > Width*Height || now+(Width*Y) < 0
					|| now+X > Width*Height || now+X < 0 ) continue;
				else if((now/Width) != ((now+1)/Width)) continue;
				if(now+X+(Width*Y) == target){
					rNode.RemoveAll();
					if((X*X)+(Y*Y) == 2) // �밢���� ���
						if(map[now+X]-> map_ID != 'B' && map[now+(Y*Width)]-> map_ID != 'B')
							rNode.Add(new mNode(G+14, 10*(((target-(now+X+(Width*Y)))%Width)+((target-(now+X+(Width*Y)))/Width)), target, this, target));
					else
						rNode.Add(new mNode(G+10, 10*(((target-(now+X+(Width*Y)))%Width)+((target-(now+X+(Width*Y)))/Width)), target, this, target));
					return &rNode;
				}
				else if(map[now+X+(Width*Y)]-> map_ID == 'R'){
					if((X*X)+(Y*Y) == 2) // �밢���� ���
						if(map[now+X]-> map_ID != 'B' && map[now+(Y*Width)]-> map_ID != 'B')
							rNode.Add(new mNode(G+14, 10*(((target-(now+X+(Width*Y)))%Width)+((target-(now+X+(Width*Y)))/Width)), now+X+(Width*Y), this, target));
					else
						rNode.Add(new mNode(G+10, 10*(((target-(now+X+(Width*Y)))%Width)+((target-(now+X+(Width*Y)))/Width)), now+X+(Width*Y), this, target));
				}
			}
		}

		return &rNode;

	}*/
};

