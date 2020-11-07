#include <iostream>
#include <vector>
#include <queue>

#include "checker.h"

using namespace std;

void printBoard(vector<string> &b){
  cout<<"Board:\n";
  for(auto &s : b){
    cout<<s<<"\n";
  }
}

int abs(int x){
  if(x<0) return -x;
  return x;
}

bool isValidLoc(int x, int y){
  if((x>=0 && x<=7) && (y>=0 && y<=7)) return true;
  return false;
}

bool isVacant(vector<string>& b, int sx, int sy, int dx, int dy){
  if(b[dx][dy]!='*') return false;
  
  if(b[sx][sy]=='w'){
    if(abs(sx-dx)==1 && dy-sy==1) return true;
  }
  else if(b[sx][sy]=='b'){
    if(abs(sx-dx)==1 && sy-dy==1) return true;
  }
  else if(b[sx][sy]=='W' || b[sx][sy]=='B'){
    if(abs(sx-dx)==1 &&  abs(sy-dy)==1) return true;
  }
  
  return false;
}

bool isJump(vector<string>& b, int sx, int sy, int dx, int dy){
  // king can jump two ways
  // man can jump forward only
  if(b[dx][dy]!='*') return false;

  if(abs(dx-sx)==2 && abs(dy-sy)==2){
    int midx=(sx+dx)/2, midy=(sy+dy)/2;
    if(b[sx][sy]=='w' || b[sx][sy]=='W'){
      if(b[midx][midy]=='b' || b[midx][midy]=='B') return true;
    }
    else{
      if(b[midx][midy]=='w' || b[midx][midy]=='W') return true;
    }
  }
  
  return false;  
}

void dfsJump(vector<vector<string>>& ret, vector<string> &board, int ix, int iy){
  bool everJumped=false;
  if(board[ix][iy]=='w' || board[ix][iy]=='b'){
    vector<int> dy={iy-2,iy+2};
    int dx=(board[ix][iy]=='w')?ix+2:ix-2;

    for(auto y:dy){
      if(isValidLoc(dx,y) && isJump(board,ix,iy,dx,y)){
	everJumped=true;
	vector<string> temp=board;
	temp[(dx+ix)/2][(iy+y)/2]='*';
	temp[dx][y]=((dx==7 && temp[ix][iy]=='w') || (dx==0 && temp[ix][iy]=='b'))?toupper(temp[ix][iy]):temp[ix][iy];
	temp[ix][iy]='*';
	dfsJump(ret,temp,dx,y);
      }
    }
  }
  else if(board[ix][iy]=='W' || board[ix][iy]=='B'){
    vector<int> dx={ix-2,ix+2};
    vector<int> dy={iy-2,iy+2};
    for(auto x:dx){
      for(auto y:dy){
	if(isValidLoc(x,y) && isJump(board,ix,iy,x,y)){
	  everJumped=true;
	  vector<string> temp=board;
	  temp[(x+ix)/2][(iy+y)/2]='*';
	  temp[x][y]=temp[ix][iy];
	  temp[ix][iy]='*';
	  dfsJump(ret,temp,x,y);
	}
      }
    }

  }

  if(!everJumped) ret.push_back(board);
}

vector<vector<string>> generateMovePerPiece(vector<string>& board, int ix, int iy){
  vector<vector<string>> ret;

  // men can only go "up" or "down", in a diagnoal manner
  if(board[ix][iy] == 'w' || board[ix][iy]=='b'){
    // 1. vacancies
    vector<int> dy = {iy-1, iy+1};
    int dx=(board[ix][iy]=='w')?ix+1:ix-1;

    for(auto y : dy){
      if(isValidLoc(dx,y) && isVacant(board,ix,iy,dx,y)){
	// if reached the end of the other side, promote to king
	vector<string> temp=board;
	temp[dx][y]=((dx==7 && temp[ix][iy]=='w') || (dx==0 && temp[ix][iy]=='b'))?toupper(temp[ix][iy]):temp[ix][iy];
	temp[ix][iy] = '*';
	ret.push_back(temp);
      }
    }
  }
  else if(board[ix][iy]=='W' || board[ix][iy]=='B'){
    // 1. vacancies
    vector<int> dx={ix-1,ix+1};
    vector<int> dy={iy-1,iy+1};
    for(auto x:dx){
      for(auto y:dy){
	if(isValidLoc(x,y) && isVacant(board,ix,iy,x,y)){
	  vector<string> temp=board;
	  temp[x][y]=temp[ix][iy];
	  temp[ix][iy]='*';
	  ret.push_back(temp);
	}
      }
    }
  }
  // 2. jumps
  dfsJump(ret,board,ix,iy);

  return ret;
}
