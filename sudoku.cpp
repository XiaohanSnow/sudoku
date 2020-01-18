#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <istream>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

string Sudoku[9] = {     //初始化一个数独终局，第一个数字为2(1120161721 (2+1)mod9+1 = 4)
	"234567891",       
    "891234567",
    "567891234",
    "123456789",
    "789123456",
    "456789123",
    "912345678",
    "678912345",
    "3456789123" };

char Sudoku_out[200000000];       //记录输出的数独 
char Sudoku_in[200000000];        //记录输入的数独 
char out[17];
int unsolvedSudoku[10][10];     //记录待解决的数独 
int rowMark[10][10];            //记录数字在行中是否出现 
int colMark[10][10];            //记录数字在列中是否出现 
int blockMark[10][10];          //记录数字在九宫格中是否出现 
int row[10], col[10], block[10];//记录行、列、九宫格中出现的数字数目 
int blank[100][3];              //记录空格所在的行、列、九宫格已经填入的数字数目 
int blankCounter = 0;           //记录空格的数目 

void Write()                                    //输出程序结果 
{
    remove("sudoku.txt");
    ofstream WriteFile("sudoku.txt");
    WriteFile << Sudoku_out;
}


inline int BlockNum(int r,int c)     //根据空格的行、列计算所在九宫格的序号 
{
    return ((r-1)/3)*3+((c-1)/3);
}

inline void Swap(int * x, int * y)    //交换空格的顺序 
{
    int arr[3];
    arr[0] = x[0];
    arr[1] = x[1];
    arr[2] = x[2];

    x[0] = y[0];
    x[1] = y[1];
    x[2] = y[2];

    y[0] = arr[0];
    y[1] = arr[1];
    y[2] = arr[2];
    return;
}

inline void SetMark(int r, int c, int n, bool flag)  //记录方格有数字 
{
    rowMark[r][n] = flag;
    colMark[c][n] = flag;
    blockMark[BlockNum(r, c)][n] = flag;
}
 
void Reset()          //深度搜索结束之后将计数的数组归零 
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            rowMark[i][j]=0;
            colMark[i][j]=0;
            blockMark[i][j]=0;
            unsolvedSudoku[i][j]=0;
        }
        row[i]=0;
        col[i]=0;
        block[i]=0;
    }
    blankCounter = 0;
    for (int i = 0; i < 100; ++i)
    {
        blank[i][0] = 0;
        blank[i][1] = 0;
        blank[i][2] = 0;
    }
    return;
}

bool DFS(int deep)                   //深度优先搜索 
{
    if(deep==blankCounter)            //求解完成             
    {
        return true;
    }

    int r = blank[deep][0], c = blank[deep][1];
    for(int i = 1; i < 10; i++)
    {
        if(!rowMark[r][i] && !colMark[c][i] && !blockMark[BlockNum(r, c)][i]) 
        {
            unsolvedSudoku[r][c]=i;
            SetMark(r, c, unsolvedSudoku[r][c], 1); //空格填入数字 
            if(DFS(deep+1))return true;
            SetMark(r, c, unsolvedSudoku[r][c], 0); //空格未填入数字 
            unsolvedSudoku[r][c]=0;
        }
    }
    return false;
}


void SolveSudoku(string  path)
{
    ifstream ReadFile(path);
    if (!ReadFile.is_open())
    {
        cout << "== Invalid Path ==" << endl;
        cout << "Check your file path!" << endl;
        return;
    }
    int count = 0;
    while(!ReadFile.eof())
    {
        ReadFile >> Sudoku_in[count++];   //读入数独题目 
    }
    ReadFile.close();
    int count_in = 0;
    int count_out = 0;

    while(Sudoku_in[count_in])
    {
        for(int r = 1; r < 10; r++)
        {
            for(int c = 1; c < 10; c++)
            {
                unsolvedSudoku[r][c] = Sudoku_in[count_in++] - 48;

                if(unsolvedSudoku[r][c] == 0)   //所在方格为空格 
                {
                    blank[blankCounter][0] = r;
                    blank[blankCounter][1] = c;
                    blankCounter++;
                }
                else                            //记录方格有数字 
                {
                    SetMark(r, c, unsolvedSudoku[r][c], 1);
                    row[r]++;
                    col[c]++;
                    block[BlockNum(r, c)]++;
                }
            }
        }

        for(int i = 0; i < blankCounter; i++)
        {
            int r = blank[blankCounter][0], c = blank[blankCounter][1];
            blank[blankCounter][2] = row[r] + col[c] + block[BlockNum(r, c)];
        }

        for(int i = 0; i < blankCounter; i++)   //根据记录空格所在的行、列、九宫格已经填入的数字数目由大到小排序 
        {
            int min = i;
            for(int j = i+1; j < blankCounter; j++)
            {
                
                if(blank[min][2] < blank[j][2])
                    min = j;
            }
            Swap(blank[i],blank[min]);
        }

        if(DFS(0))
        {
            for(int r = 1; r < 10; r++)
            {
                for(int c = 1; c < 10; c++)
                {
                    Sudoku_out[count_out++] = unsolvedSudoku[r][c] + '0';
                    if (c == 9)
                       Sudoku_out[count_out++] = '\n';
                    else 
                        Sudoku_out[count_out++] = ' ';
                }
            }
            Sudoku_out[count_out++] = '\n';
        }
        Reset();
    }
    Write();
}

void CreateSudoku(int & n)
{
    int FirstRow[] = {2,3,4,5,6,7,8,9,1};    //记录第一行的9个数 
    int RowOrder[] = {0,1,2,3,4,5,6,7,8};    //记录交换行以后行号的对应关系 
    int NumberOrder[9];                      //记录9个数字在第一行全排列变换后的对应关系 
    int NewSudoku[9][9];                     //记录第一行全排列变换后根据规则生成的新数独 
    int count = 0;                           //记录输出的个数 

    
    ofstream WriteFile;
	WriteFile.open("sudoku.txt",ios::trunc);
  

    do
    {
        for (int i = 0; i < 9; i++)        //9个数字在第一行全排列变换后与原位置数字一一对应 
            NumberOrder[Sudoku[0][i] - 49] = FirstRow[i];//原位置数字的ASCII码-48等于数字，再-1等于数组序号 
        
        for (int i = 0; i < 9; ++i)        //将数独中的所有数字按照对应关系替换 
            for (int j = 0; j < 9; ++j)
                NewSudoku[i][j] = NumberOrder[Sudoku[i][j] - 49];

       
            for (int i = 0; i < 6 && n; i++)
            {
                for (int j = 0;j < 6 && n; j++)
                {
                    for (int k = 0; k < 9; k++)
                    {
                    	count = 0;
                        for (int t = 0; t < 9; t++)
                        {
                            out[count++] = NewSudoku[RowOrder[k]][t] +'0';
                            if (t != 8)
                            out[count++] = ' ';		//方格之间空格 
                        }
                        WriteFile<<out<<"\n";
                    }
                    if (--n)
                        WriteFile<<"\n";              //数独之间空行 
                    else
                        return;
                    next_permutation(RowOrder+6,RowOrder+9); //对7 8 9行全排列变换 
                }
                next_permutation(RowOrder+3,RowOrder+6);     //对4 5 6行全排列变换 
            }
    }
    while(next_permutation(FirstRow+1,FirstRow+9));    //对第一行的后8个数全排列 
    return;
}

int main(int argc, char *argv[])
{
    clock_t start,finish;
    start = clock();
    
    if (argc != 3)                  //检查输入的指令个数 
    {
        cout << "== Invalid Arguments ==" << endl;
        cout << "If the file path contains spaces:"<< endl;
        cout << "1.Use backslash before spaces as escape character" << endl;
        cout << "2.Quotes the path with double quotation mark" << endl;
        return 0;
    }

    if (strcmp(argv[1],"-c") && strcmp(argv[1],"-s")) //检查输入的类型 
    {
        cout << "== Invalid Command ==" << endl;
        cout << "This applicaiton only supports create(-c) and solve(-s) functions!" << endl;
        return 0;
    }

    switch(argv[1][1])                          
    {
        case 'c':                
        {
            int num = atoi(argv[2]);                
            if (num <= 0 || strlen(argv[2]) != int(log10(num))+1 || num >1000000)//检查输入的数字是否符合题目要求 
            {
                cout << "== Invalid Input ==" << endl;
                cout << "Make sure the number is in the range of 1-1,000,000!" << endl;
                return 0;
            }
            else
            {
                CreateSudoku(num);
                Write();
            }
            break;
        }

        case 's':
        {
            SolveSudoku(argv[2]);
            break;
        }
    }

    finish = clock();
    cout << "Used time = " << double(finish-start)/CLOCKS_PER_SEC << "s" << endl;
    
    return 0;
}








