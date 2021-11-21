#include <iostream>
#include <array>
#include <thread>
#include <string>

const int ROW = 300;
const int COL = 300;

std::array<std::array<uint8_t, COL>, ROW> board;

void updateBoard();
void draw(std::array<std::array<uint8_t, COL>, ROW> buffer);

int main(){
  board[0][1] = 1;
  board[1][2] = 1;
  board[2][2] = 1;
  board[2][1] = 1;
  board[2][0] = 1;
  
  while(true){
    draw(board);
    updateBoard();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << std::endl;
}

void updateBoard(){
  std::array<std::array<uint8_t, COL>, ROW> buffer;
  
  for(int r = 0; r < ROW; ++r){
    for(int c = 0; c < COL; ++c){
      int neighbourSum = 0;

      if(c+1 < board[r].size()){ neighbourSum += board[r][c+1]; }//R
      if(r+1 < board.size() && c+1 < board[r].size()){ neighbourSum += board[r+1][c+1]; }//DR
      if(r+1 < board.size()){ neighbourSum += board[r+1][c]; }//D
      if(r+1 < board.size() && c-1 >= 0){ neighbourSum += board[r+1][c-1]; }//DL
      if(c-1 >= 0){ neighbourSum += board[r][c-1]; }//L
      if(r-1 >= 0 && c-1 >= 0){ neighbourSum += board[r-1][c-1]; }//UL
      if(r-1 >= 0){ neighbourSum += board[r-1][c]; }//U
      if(r-1 >= 0 && c+1 < board[r].size()){ neighbourSum += board[r-1][c+1]; }//UR

      switch(neighbourSum){
      case 0 ... 1:
	buffer[r][c] = 0;
	break;
	
      case 2:
	buffer[r][c] = board[r][c];
	break;
	
      case 3:
	buffer[r][c] = 1;
	break;
	
      case 4 ... 8:
	buffer[r][c] = 0;
	break;
      }
    }
  }

  board = buffer;
}

void draw(std::array<std::array<uint8_t, COL>, ROW> buffer){

#if defined(__linux__)
#define consoleClear "clear"
#endif

#if defined(_WIN64)
#define consoleClear "CLS"
#elif defined(_WIN32)
#define consoleClear "CLS"
#endif
  
  system(consoleClear);
  std::string output;

  for(int r = 0; r < 50; ++r){
    for(int c = 0; c < 200; ++c){
      output += std::to_string(board[r][c]);
    }
    output += "\n";
  }

  std::cout << output << std::endl;
}
