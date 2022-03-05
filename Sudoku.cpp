#include <iostream>
#define LINE 9

int sudoku[LINE+1][LINE+1] = {0,};  // sudoku 판

bool isEnd = false; // 완성본을 봤는가?
int fill=0;     // 입력된 sudoku 판에 들어있는 0의 개수
class Point { public: int x; int y; Point(int _x=0, int _y=0) : x(_x), y(_y) {} };  // 점의 위치 (x,y) 를 담는다
Point* Arr = new Point [LINE*LINE +1];  // 0이 저장된 sudoku 판 위 점들의 위치

void PrintSudoku(void)      // 완성된 sudoku 판 출력
{
    for (int y=1; y<=9; y++)
    {
        for (int x=1; x<=9; x++)
        {
            std::cout << sudoku[x][y] << ' ';
        }
        std::cout << '\n';
    }
    return;
}

bool Condition(Point P, int n)  // 점 P에 숫자 n을 넣어도 될까?
{
    for (int iter=1; iter<=9; iter++)
    {
        if ( sudoku[iter][P.y] == n ) return false;     // 가로 점검
        if ( sudoku[P.x][iter] == n ) return false;     // 세로 점검
    }

    for (int iter_x=1; iter_x<=3; iter_x++)
    {
        for (int iter_y=1; iter_y<=3; iter_y++)
        {
            int X = 3 * ( (P.x-1) / 3 ) + iter_x;
            int Y = 3 * ( (P.y-1) / 3 ) + iter_y;

            if ( sudoku[X][Y] == n ) return false;      // 박스 점검
        }
    }

    return true;
}

void PutNum(int put)    // Arr[put] 이 가리키는 위치에 대입할 수 탐색
{
    if (put > fill) { isEnd = true; PrintSudoku(); return; }

    for (int n=1; n<=9; n++)
    {
        if ( Condition(Arr[put], n) == true )
        {
            sudoku[ Arr[put].x ][ Arr[put].y ] = n;
            PutNum(put+1);
            if (isEnd) return;  // 한 번 끝을 봤기 때문에 다른 결과는 볼 필요 X
        }
    }
    // isEnd = false 일 때 여기 왔다는 것은, Arr[put] 에 어떤 값이 들어가도 가망이 없다는 것이므로 다른 경로를 위해 초기화한다.
    sudoku[ Arr[put].x ][ Arr[put].y ] = 0;
    return;
}

int main(void)
{
    for (int y=1; y<=9; y++) { for (int x=1; x<=9; x++) { std::cin >> sudoku[x][y]; } }
    for (int y=1; y<=9; y++) { for (int x=1; x<=9; x++) { if ( sudoku[x][y] == 0 ) { Arr[++fill] = Point(x,y); } } }    // Arr[1] ~ Arr[fill] 에만 정보 저장.

    PutNum(1);

    return 0;
}