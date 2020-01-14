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

string Sudoku[9] = {     //��ʼ��һ�������վ֣���һ������Ϊ2(1120161721 (2+1)mod9+1 = 4)
	"234567891",       
    "891234567",
    "567891234",
    "123456789",
    "789123456",
    "456789123",
    "912345678",
    "678912345",
    "3456789123" };

char Sudoku_out[200000000];       //��¼��������� 
char Sudoku_in[200000000];        //��¼��������� 
int unsolvedSudoku[10][10];     //��¼����������� 
int rowMark[10][10];            //��¼�����������Ƿ���� 
int colMark[10][10];            //��¼�����������Ƿ���� 
int blockMark[10][10];          //��¼�����ھŹ������Ƿ���� 
int row[10], col[10], block[10];//��¼�С��С��Ź����г��ֵ�������Ŀ 
int blank[100][3];              //��¼�ո����ڵ��С��С��Ź����Ѿ������������Ŀ 
int blankCounter = 0;           //��¼�ո����Ŀ 

void Write()                                    //��������� 
{
    remove("sudoku.txt");
    ofstream WriteFile("sudoku.txt");
    WriteFile << Sudoku_out;
}

inline int BlockNum(int r,int c)     //���ݿո���С��м������ھŹ������� 
{
    return ((r-1)/3)*3+((c-1)/3);
}

inline void Swap(int * x, int * y)    //�����ո��˳�� 
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

inline void SetMark(int r, int c, int n, bool flag)  //��¼���������� 
{
    rowMark[r][n] = flag;
    colMark[c][n] = flag;
    blockMark[BlockNum(r, c)][n] = flag;
}
 
void Reset()          //�����������֮�󽫼������������ 
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

bool DFS(int deep)                   //����������� 
{
    if(deep==blankCounter)            //������             
    {
        return true;
    }

    int r = blank[deep][0], c = blank[deep][1];
    for(int i = 1; i < 10; i++)
    {
        if(!rowMark[r][i] && !colMark[c][i] && !blockMark[BlockNum(r, c)][i]) 
        {
            unsolvedSudoku[r][c]=i;
            SetMark(r, c, unsolvedSudoku[r][c], 1); //�ո��������� 
            if(DFS(deep+1))return true;
            SetMark(r, c, unsolvedSudoku[r][c], 0); //�ո�δ�������� 
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
        ReadFile >> Sudoku_in[count++];   //����������Ŀ 
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

                if(unsolvedSudoku[r][c] == 0)   //���ڷ���Ϊ�ո� 
                {
                    blank[blankCounter][0] = r;
                    blank[blankCounter][1] = c;
                    blankCounter++;
                }
                else                            //��¼���������� 
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

        for(int i = 0; i < blankCounter; i++)   //���ݼ�¼�ո����ڵ��С��С��Ź����Ѿ������������Ŀ�ɴ�С���� 
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
    int FirstRow[] = {2,3,4,5,6,7,8,9,1};    //��¼��һ�е�9���� 
    int RowOrder[] = {0,1,2,3,4,5,6,7,8};    //��¼�������Ժ��кŵĶ�Ӧ��ϵ 
    int NumberOrder[9];                      //��¼9�������ڵ�һ��ȫ���б任��Ķ�Ӧ��ϵ 
    int NewSudoku[9][9];                     //��¼��һ��ȫ���б任����ݹ������ɵ������� 
    int count = 0;                           //��¼����ĸ��� 
    do
    {
        for (int i = 0; i < 9; i++)        //9�������ڵ�һ��ȫ���б任����ԭλ������һһ��Ӧ 
            NumberOrder[Sudoku[0][i] - 49] = FirstRow[i];//ԭλ�����ֵ�ASCII��-48�������֣���-1����������� 
        
        for (int i = 0; i < 9; ++i)        //�������е��������ְ��ն�Ӧ��ϵ�滻 
            for (int j = 0; j < 9; ++j)
                NewSudoku[i][j] = NumberOrder[Sudoku[i][j] - 49];

       
            for (int i = 0; i < 6 && n; i++)
            {
                for (int j = 0;j < 6 && n; j++)
                {
                    for (int k = 0; k < 9; k++)
                    {
                        for (int t = 0; t < 9; t++)
                        {
                            Sudoku_out[count++] = NewSudoku[RowOrder[k]][t] +'0';
                            if (t == 8)
                                Sudoku_out[count++] = '\n';     //ÿ��ĩβ���� 
                            else 
                                Sudoku_out[count++] = ' ';		//����֮��ո� 
                        }
                    }
                    if (--n)
                        Sudoku_out[count++] = '\n';              //����֮����� 
                    else
                        return;
                    next_permutation(RowOrder+6,RowOrder+9); //��7 8 9��ȫ���б任 
                }
                next_permutation(RowOrder+3,RowOrder+6);     //��4 5 6��ȫ���б任 
            }
    }
    while(next_permutation(FirstRow+1,FirstRow+9));    //�Ե�һ�еĺ�8����ȫ���� 
    return;
}

int main(int argc, char *argv[])
{
    clock_t start,finish;
    start = clock();
    
    if (argc != 3)                  //��������ָ����� 
    {
        cout << "== Invalid Arguments ==" << endl;
        cout << "If the file path contains spaces:"<< endl;
        cout << "1.Use backslash before spaces as escape character" << endl;
        cout << "2.Quotes the path with double quotation mark" << endl;
        return 0;
    }

    if (strcmp(argv[1],"-c") && strcmp(argv[1],"-s")) //������������ 
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
            if (num <= 0 || strlen(argv[2]) != int(log10(num))+1 || num >1000000)//�������������Ƿ������ĿҪ�� 
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









