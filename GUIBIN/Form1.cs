using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;
using System.IO;

namespace sudokuGame
{
    public partial class Sudoku_Game : Form
    {
        public static ArrayList Game_table = new ArrayList();
        public static int flag = 0;
        public Sudoku_Game()
        {
            InitializeComponent();
        }

        private void Table_Init(object sender, EventArgs e)
        {
          
            Game_table.Add(text_element11);
            Game_table.Add(text_element12);
            Game_table.Add(text_element13);
            Game_table.Add(text_element14);
            Game_table.Add(text_element15);
            Game_table.Add(text_element16);
            Game_table.Add(text_element17);
            Game_table.Add(text_element18);
            Game_table.Add(text_element19);
            Game_table.Add(text_element21);
            Game_table.Add(text_element22);
            Game_table.Add(text_element23);
            Game_table.Add(text_element24);
            Game_table.Add(text_element25);
            Game_table.Add(text_element26);
            Game_table.Add(text_element27);
            Game_table.Add(text_element28);
            Game_table.Add(text_element29);
            Game_table.Add(text_element31);
            Game_table.Add(text_element32);
            Game_table.Add(text_element33);
            Game_table.Add(text_element34);
            Game_table.Add(text_element35);
            Game_table.Add(text_element36);
            Game_table.Add(text_element37);
            Game_table.Add(text_element38);
            Game_table.Add(text_element39);
            Game_table.Add(text_element41);
            Game_table.Add(text_element42);
            Game_table.Add(text_element43);
            Game_table.Add(text_element44);
            Game_table.Add(text_element45);
            Game_table.Add(text_element46);
            Game_table.Add(text_element47);
            Game_table.Add(text_element48);
            Game_table.Add(text_element49);
            Game_table.Add(text_element51);
            Game_table.Add(text_element52);
            Game_table.Add(text_element53);
            Game_table.Add(text_element54);
            Game_table.Add(text_element55);
            Game_table.Add(text_element56);
            Game_table.Add(text_element57);
            Game_table.Add(text_element58);
            Game_table.Add(text_element59);
            Game_table.Add(text_element61);
            Game_table.Add(text_element62);
            Game_table.Add(text_element63);
            Game_table.Add(text_element64);
            Game_table.Add(text_element65);
            Game_table.Add(text_element66);
            Game_table.Add(text_element67);
            Game_table.Add(text_element68);
            Game_table.Add(text_element69);
            Game_table.Add(text_element71);
            Game_table.Add(text_element72);
            Game_table.Add(text_element73);
            Game_table.Add(text_element74);
            Game_table.Add(text_element75);
            Game_table.Add(text_element76);
            Game_table.Add(text_element77);
            Game_table.Add(text_element78);
            Game_table.Add(text_element79);
            Game_table.Add(text_element81);
            Game_table.Add(text_element82);
            Game_table.Add(text_element83);
            Game_table.Add(text_element84);
            Game_table.Add(text_element85);
            Game_table.Add(text_element86);
            Game_table.Add(text_element87);
            Game_table.Add(text_element88);
            Game_table.Add(text_element89);
            Game_table.Add(text_element91);
            Game_table.Add(text_element92);
            Game_table.Add(text_element93);
            Game_table.Add(text_element94);
            Game_table.Add(text_element95);
            Game_table.Add(text_element96);
            Game_table.Add(text_element97);
            Game_table.Add(text_element98);
            Game_table.Add(text_element99);
        }

        private void text_element11_TextChanged(object sender, EventArgs e)
        {

        }

        static void FillGrid()
        {
            StreamReader sr1 = new StreamReader("sudoku.txt");

            for (int k = 0; k < 10 * flag; k++)
            {
                string linemore = sr1.ReadLine();
            }
            for (int i = 0; i < 9; i++)
            {
                string line = sr1.ReadLine();
                for (int j = 0; j < 9; j++)
                {
                    TextBox text_element = Game_table[i * 9 + j] as TextBox;
                    if (line[2 * j] == '0')
                    {
                        text_element.Text = "";
                        text_element.ReadOnly = false;
                        text_element.ForeColor = Color.Brown;
                        text_element.BackColor = Color.Thistle;
                    }
                    else
                    {
                        text_element.Text = line[2 * j].ToString();
                        text_element.ReadOnly = true;
                        text_element.ForeColor = Color.Black;
                    }

                }
            }
            flag++;
        }

        static void UnfinishedWarning()
        {
            MessageBox.Show("Not completed, please continue to answer!", "Warning");
        }
        static void WrongAnswerWarning()
        {
            MessageBox.Show("Wrong answer!", "Error warning");
        }
        static void PassReminding()
        {
            MessageBox.Show("Completed successfully!", "Congratulations");
        }

        static void Checksubmit()
        {
            string[] finished;
            finished = new string[10];
            for (int i = 0; i < 9; i++)
            {
                finished[i] = "";
                for (int j = 0; j < 9; j++)
                {
                    TextBox text_element = Game_table[i * 9 + j] as TextBox;
                    if (text_element.Text == "")
                    {
                        UnfinishedWarning();
                        return;
                    }
                    finished[i] = finished[i] + text_element.Text;
                }
            }
            //检查结果
            int[] hang = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };
            int[] bias = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };
            for (int i = 0; i < 9; i++)
            {
                int[] chang = new int[10];
                int[] ccol = new int[10];
                int[] cgrid = new int[10];
                for (int j = 0; j < 9; j++)
                {
                    chang[j] = 0;
                    ccol[j] = 0;
                    cgrid[j] = 0;
                }
                //count++
                for (int j = 0; j < 9; j++)
                {
                    chang[finished[i][j] - '0']++;
                    ccol[finished[j][i] - '0']++;

                    int pos = hang[i] + bias[j];
                    int c = pos / 9;
                    int d = pos % 9;
                    cgrid[finished[c][d] - '0']++;

                }
                for (int j = 1; j <= 9; j++)
                {
                    if (chang[j] == 0 || chang[j] > 1)
                    {
                        WrongAnswerWarning();
                        return;
                    }
                    if (ccol[j] == 0 || ccol[j] > 1)
                    {
                        WrongAnswerWarning();
                        return;
                    }
                    if (cgrid[j] == 0 || cgrid[j] > 1)
                    {
                        WrongAnswerWarning();
                        return;
                    }
                }

            }
            PassReminding();
        }

        private void Button_Submit_Click(object sender, EventArgs e)
        {
            Checksubmit();
        }

        private void Button_Next_Click(object sender, EventArgs e)
        {
            FillGrid();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            FillGrid();
        }

        private void text_element25_TextChanged(object sender, EventArgs e)
        {

        }
    }
}

   
