#include "MathManager.h"

CMathManager::CMathManager(){
	
}

CMathManager::~CMathManager(){
	
}

void CMathManager::swap(float* A, float* B){
	float Temp;

	Temp = *A;
	*A = *B;
	*B = Temp;
}

void CMathManager::VLine(float x, float y1, float y2){
	float column;

	if(y1 > y2){
		swap(&y1, &y2);
	}

	for(column = y1; column <= y2; column+=1.0f){

	}
}

void CMathManager::HLine(float x1, float x2, float y){
	float row;

	if(x1 > x2){
		swap(&x1, &x2);
	}

	for(row = x1; row <= x2; row+=1.0f){

	}
}


void CMathManager::Line(float x1, float y1, float x2, float y2){
	float m; //기울기를 계산할 변수
	float x, y;

	float tempx, tempy;
	

	if(x1 == x2){
		VLine(x1, y1, y2);
		return;
	}
	if(y1 == y2){
		HLine(x1, x2, y1);
		return;
	}

	tempx = x1;
	tempy = y1;

	m = (float)(y2 - y1) / (x2 - x1);

	if((m < 1) && (m > -1)){ //x축을 독립축으로	
		if(x1 > x2){
			for(x = x1; x > x2; x--){
				y = m * (x - tempx) + tempy;
			}
		}
		else{
			for(x = x1; x <= x2; x++){
				y = m * (x - tempx) + tempy;
			}
		}
	}
	else{
		if(y1 > y2){
			for(y = y1; y > y2; y--){
				x = (1/m) * (y - tempy) + tempx;
			}
		}
		else{
			for(y = y1; y <= y2; y++){
				x = (1/m) * (y - tempy) + tempx;
			}
		}
	}	
}

void CMathManager::LinearMove(COrgan* _pOrgan, float mx, float my, float vx, float vy){
	static float m; //기울기를 계산할 변수
	static float x, y;
	static float x1, y1;
	static float x2, y2;

	float dx, dy; //목표좌표

	dx = mx-35;	dy = my-45;

	if(x2 != dx || y2 != dy){ //새로운 값이 입력될 경우에만 새로계산한다.	
		x1 = _pOrgan->GetPriPos()->x;	y1 = _pOrgan->GetPriPos()->y;
		x2 = dx;		y2 = dy;

		m = (float)(y2 - y1) / (x2 - x1);
		x = x1;		y = y1;
	}

	if(x1 == x2){	//x의 값이 같을 경우	
		if(y1 > y2){
			if(y > y2){
				y-=vy;
			}
		}
		else{
			if(y <= y2){
				y+=vy;
			}
		}
		return;
	}
	if(y1 == y2){	//y의 값이 같을 경우
		if(x1 > x2){
			if(x > x2){
				x-=vx;
			}
		}
		else{
			if(x <= x2){
				x+=vx;
			}
		}
		return;
	}


	if((m < 1) && (m > -1)){ //x축을 독립축으로
		if(x1 > x2){
			if(x > x2){
				y = m * (x - x1) + y1;//덧셈에 의한 값을 산출 할 경우 더욱 계산식을 빨리 가능하다.
				_pOrgan->GetPriPos()->x = x;
				_pOrgan->GetPriPos()->y = y;
				x-=vx;
			}
		}
		else{
			if(x <= x2){
				y = m * (x - x1) + y1;
				_pOrgan->GetPriPos()->x = x;
				_pOrgan->GetPriPos()->y = y;
				x+=vx;
			}
		}
	}
	else{
		if(y1 > y2){
			if(y > y2){
				x = (1/m) * (y - y1) + x1;
				_pOrgan->GetPriPos()->x = x;
				_pOrgan->GetPriPos()->y = y;
				y-=vy;
			}
		}
		else{
			if(y <= y2){
				x = (1/m) * (y - y1) + x1;
				_pOrgan->GetPriPos()->x = x;
				_pOrgan->GetPriPos()->y = y;
				y+=vx;
			}
		}
	}
}