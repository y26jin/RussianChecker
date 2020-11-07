#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "checker.h"

#define WHITE 0
#define BLACK 1

using namespace std;

void dfs(vector<vector<string>> &r ,vector<string> &b, int level, int max){
  if(level==max){
    return;
  }

  // find possible moves
  cout<<level<<endl;
  vector<int> x;
  vector<int> y;
  if(level%2 == WHITE){
    for(int i=0;i<8;++i){
      for(int j=0;j<8;++j){
	if(b[i][j]=='w' || b[i][j]=='W'){
	  x.push_back(i);
	  y.push_back(j);
	}
      }
    }
  }
  else if(level%2 == BLACK){
    for(int i=0;i<8;++i){
      for(int j=0;j<8;++j){
	if(b[i][j]=='b' || b[i][j]=='B'){
	  x.push_back(i);
	  y.push_back(j);
	}
      }
    }
  }

  for(int i=0;i<x.size();++i){
    vector<vector<string>> temp = generateMovePerPiece(b,x[i],y[i]);
    for(auto t:temp){
      dfs(r,t,level+1,max);
    }
  }
}

int main(){
  // w - white man
  // b - black man
  // W - king
  // B - king
  vector<string> board = {
			  "w*w*w*w*",
			  "*w*w*w*w",
			  "w*w*w*w*",
			  "********",
			  "********",
			  "*b*b*b*b",
			  "b*b*b*b*",
			  "*b*b*b*b"
  };

  int nextTurn = WHITE;
  int max = 10;
  int level = 0;
  
  queue<vector<string>> q;
  q.push(board);
  while(!q.empty() && level < max){
    vector<string> b = q.front();
    q.pop();
    printBoard(b);
    cout<<"->\n";

    // generate next moves
    vector<int> x;
    vector<int> y;
    if(level%2 == WHITE){
      for(int i=0;i<8;++i){
	for(int j=0;j<8;++j){
	  if(b[i][j]=='w' || b[i][j]=='W'){
	    x.push_back(i);
	    y.push_back(j);
	  }
	}
      }
    }
    else if(level%2 == BLACK){
      for(int i=0;i<8;++i){
	for(int j=0;j<8;++j){
	  if(b[i][j]=='b' || b[i][j]=='B'){
	    x.push_back(i);
	    y.push_back(j);
	  }
	}
      }
    }
    for(int i=0;i<x.size();++i){
      vector<vector<string>> temp = generateMovePerPiece(b,x[i],y[i]);
      if(!temp.empty()){
	reverse(temp.begin(),temp.end());
	for(auto t:temp){
	  printBoard(t);
	  q.push(t);
	}
      }
    }
    cout<<"=============================\n";
  }
  return 0;
}
