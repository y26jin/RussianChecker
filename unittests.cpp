#include <iostream>
#include <vector>
#include "checker.h"
using namespace std;

int main(){
  // Test 1: check if isVacant is working

  cout<<"Test 1: isVacant()\n";
  vector<string> board = {
			  "**w*w*w*",
			  "*W*w*w*w",
			  "w*b*w*w*",
			  "********",
			  "********",
			  "b*b*b*b*",
			  "*b*b*b*b",
			  "b*b*b*b*"
  };
  bool ret = isVacant(board,1,1,0,0);
  if(ret!=true) cout<<"Test 1 Failed\n";
  else cout<<"Test 1 Passed\n";


  // Test 2: isJump()
  cout<<"Test 2: isJump()\n";
  ret=isJump(board,1,1,3,3);
  if(ret!=true) cout<<"Test 1 Failed\n";
  else cout<<"Test 1 Passed\n";


  // Test 3: generateMovePerPiece
  cout<<"Test 3: generateMovePerPiece()\n";
  auto r = generateMovePerPiece(board,1,1);
  for(auto rr:r){
    printBoard(rr);
  }
  
  return 0;
}
