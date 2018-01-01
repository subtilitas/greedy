namespace greedyconf
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.t_update_sequencer = new System.Windows.Forms.Timer(this.components);
            this.tbllayout = new System.Windows.Forms.TableLayoutPanel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.actionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.flowLayoutPanel1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.AutoSize = true;
            this.flowLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.flowLayoutPanel1.Controls.Add(this.tbllayout);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 28);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(1006, 949);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // t_update_sequencer
            // 
            this.t_update_sequencer.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tbllayout
            // 
            this.tbllayout.AutoSize = true;
            this.tbllayout.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tbllayout.ColumnCount = 18;
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tbllayout.GrowStyle = System.Windows.Forms.TableLayoutPanelGrowStyle.FixedSize;
            this.tbllayout.Location = new System.Drawing.Point(3, 3);
            this.tbllayout.MinimumSize = new System.Drawing.Size(80, 80);
            this.tbllayout.Name = "tbllayout";
            this.tbllayout.RowCount = 18;
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tbllayout.Size = new System.Drawing.Size(80, 80);
            this.tbllayout.TabIndex = 2;
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.actionsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1006, 28);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // actionsToolStripMenuItem
            // 
            this.actionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clearAllToolStripMenuItem});
            this.actionsToolStripMenuItem.Name = "actionsToolStripMenuItem";
            this.actionsToolStripMenuItem.Size = new System.Drawing.Size(68, 24);
            this.actionsToolStripMenuItem.Text = "actions";
            // 
            // clearAllToolStripMenuItem
            // 
            this.clearAllToolStripMenuItem.Name = "clearAllToolStripMenuItem";
            this.clearAllToolStripMenuItem.Size = new System.Drawing.Size(181, 26);
            this.clearAllToolStripMenuItem.Text = "clear all";
            this.clearAllToolStripMenuItem.Click += new System.EventHandler(this.clearAllToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1006, 977);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Timer t_update_sequencer;
        private System.Windows.Forms.TableLayoutPanel tbllayout;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem actionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearAllToolStripMenuItem;
    }
}

