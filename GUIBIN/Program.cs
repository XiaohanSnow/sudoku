using System;
using System.Windows.Forms;

namespace sudokuGame
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Sudoku_Game());
        }
    }
}