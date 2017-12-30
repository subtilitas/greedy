using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace greedyconf
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < 16; i++)

                for (int j = 1; j < 17; j++)
                {
                    Button tblbtn = new Button();
                tblbtn.Width = 44;
                tblbtn.Height = 44;
                tblbtn.MouseClick += tblbutton_clicked;
                

                tblbtn.Name = "tblbtn_" + i.ToString() + "_" + j.ToString();
                tbllayout.Controls.Add(tblbtn, i, j);
            }
        }

        private void tblbutton_clicked (object sender, EventArgs e)
        {
            Button snd = (Button)sender;
            snd.BackColor = Color.Black;
        }


    }
}
