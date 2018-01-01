using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace greedyconf
{
    public partial class Form1 : Form
    {
        public SerialPort sp_teensy;
        public Byte[][][] sequencer_data;
        List<Button> seq_buttons = new List<Button>();
        public bool sequencer_data_updated = true;
        public const int note = 0, velocity = 1, instrument = 2;
        public Form1()
        {
            InitializeComponent();
        }

        private void Open_Comport()
        {
            sp_teensy = new SerialPort("COM6", 115200);
            sp_teensy.WriteBufferSize = 4096;
            sp_teensy.Parity = Parity.None;
            sp_teensy.StopBits = StopBits.One;
            sp_teensy.Handshake = Handshake.None;
            sp_teensy.DtrEnable = true;
            sp_teensy.RtsEnable = true;

            sp_teensy.Open();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

            Open_Comport();

            sequencer_data = new Byte[16][][];
            for (int i = 0; i < 16; i++)
            {
                sequencer_data[i] = new Byte[16][];
                for (int j = 0; j < 16; j++)
                {
                    sequencer_data[i][j] = new Byte[3];
                    sequencer_data[i][j][note] = 55; //tone
                    sequencer_data[i][j][velocity] = 0; //velocity
                    sequencer_data[i][j][instrument] = 1; //instrument
                }
            }

            for (int i = 1; i < 17; i++)
            {
                ComboBox dd_instrument = new ComboBox();
                dd_instrument.Name = "instr_" + i.ToString();
                dd_instrument.Width = 70;
                dd_instrument.SelectedIndexChanged += DDSelectedIndexChanged;
                //ddt.Anchor = AnchorStyles.Left;
                dd_instrument.Dock = DockStyle.Left;

                ComboBox dd_tone = new ComboBox();
                dd_tone.Name = "tone_" + i.ToString();
                dd_tone.Width = 70;
                dd_tone.SelectedIndexChanged += DDSelectedIndexChanged;
                //ddb.Anchor = AnchorStyles.Right;
                dd_tone.Dock = DockStyle.Right;


                for (int instrument = 1; instrument < 17; instrument++)
                {
                    dd_instrument.Items.Add("Instr: " + instrument.ToString());
                }

                for (int tone = 1; tone < 127; tone++)
                {
                    dd_tone.Items.Add("tone: " + tone.ToString());
                }
                dd_tone.SelectedIndex = 47 - i;
                tbllayout.Controls.Add(dd_tone, 0, i);

                dd_instrument.SelectedIndex = 0;
                tbllayout.Controls.Add(dd_instrument, 1, i);

                for (int sdr = 0; sdr < 16; sdr++)
                {
                    sequencer_data[sdr][i - 1][instrument] = (Byte)(dd_instrument.SelectedIndex + 1);
                    sequencer_data[sdr][i - 1][note] = (Byte)(dd_tone.SelectedIndex + 1);
                }


                for (int j = 1; j < 17; j++)
                {
                    Button tblbtn = new Button();
                    tblbtn.Width = 44;
                    tblbtn.Height = 25;
                    tblbtn.MouseClick += tblbutton_clicked;
                    tblbtn.Name = "tblbtn_" + i.ToString() + "_" + j.ToString();
                    tblbtn.Text = i.ToString() + "/" + j.ToString();
                    tblbtn.BackColor = Color.White;
                    tblbtn.ForeColor = Color.Black;

                    tbllayout.Controls.Add(tblbtn, i + 1, j);
                    seq_buttons.Add(tblbtn);
                }
            }
            t_update_sequencer.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (sequencer_data_updated)
            {
                Byte[] SendBuffer = new byte[16 * 16 * 3 + 4];
                int buf_pos = 0;
                SendBuffer[buf_pos++] = 222;
                SendBuffer[buf_pos++] = 244;

                if (!sp_teensy.IsOpen)
                {
                    Open_Comport();
                }

                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        SendBuffer[buf_pos++] = sequencer_data[i][j][note];
                        SendBuffer[buf_pos++] = sequencer_data[i][j][velocity];
                        SendBuffer[buf_pos++] = sequencer_data[i][j][instrument];

                    }
                }
                SendBuffer[buf_pos++] = 222;
                SendBuffer[buf_pos++] = 244;

                sp_teensy.Write(SendBuffer, 0, buf_pos);
                sequencer_data_updated = false;
            }
        }

        private void clearAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach(Button btn in seq_buttons)
            {
                int x = 0, y = 0;
                x = int.Parse(btn.Text.Split('/')[0]) - 1;
                y = int.Parse(btn.Text.Split('/')[1]) - 1;

                if (btn.BackColor == Color.Black) // if enabled
                {
                    btn.BackColor = Color.White;
                    btn.ForeColor = Color.Black;

                    sequencer_data[x][y][velocity] = 0; //velocity
                }
            }
            sequencer_data_updated = true;
        }

        private void tblbutton_clicked(object sender, EventArgs e)
        {
            Button snd = (Button)sender;
            int x = 0, y = 0;
            x = int.Parse(snd.Text.Split('/')[0]) - 1;
            y = int.Parse(snd.Text.Split('/')[1]) - 1;

            if (snd.BackColor == Color.Black) // if enabled
            {
                snd.BackColor = Color.White;
                snd.ForeColor = Color.Black;

                sequencer_data[x][y][velocity] = 0; //velocity
            }
            else
            {
                snd.BackColor = Color.Black;
                snd.ForeColor = Color.White;

                sequencer_data[x][y][velocity] = 64; //velocity
            }

            sequencer_data_updated = true;
        }
        private void DDSelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox dd = (ComboBox)sender;
            int y = int.Parse(dd.Name.Split('_')[1]) - 1;

            int seq_data_type = dd.Name.Split('_')[0] == "tone" ? note : instrument;
            for (int x = 0; x < 16; x++)
            {
                sequencer_data[x][y][seq_data_type] = (Byte)(dd.SelectedIndex + 1);
            }

            sequencer_data_updated = true;
        }

    }
}
