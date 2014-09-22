using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void mnTextView1_DoubleClick(object sender, EventArgs e)
        {
            //MessageBox.Show("mnTextView1_DoubleClick");
        }

        private void mnTextView1_TextChanged(object sender, EventArgs e)
        {
            //MessageBox.Show("mnTextView1_TextChanged haha");
            //textBox1.Text = mnTextView1.Text;
        }






        private void 撤消UToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.Undo();
        }

        private void 重复RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.Redo();
        }

        private void 剪切TToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.Cut();
        }

        private void 复制CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.Copy();
        }

        private void 粘贴PToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.Paste();
        }

        private void 全选AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mnTextBox1.SelectAll();
        }

        private void 前景颜色ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {

                mnTextBox1.ForeColor = colorDialog1.Color;
                mnTextBox1.ForeColor = colorDialog1.Color;
            }
        }

        private void 背景颜色ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                //backColor.BackColor = colorDialog1.Color;
                mnTextBox1.BackColor = colorDialog1.Color;
                mnTextBox1.BackColor = colorDialog1.Color;
            }
        }

        private void 字体ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = fontDialog1.ShowDialog() ;
            if (dr == DialogResult.OK)
            {
                mnTextBox1.Font = fontDialog1.Font;//new Font("MNWHITE", 12);// 
            }
        }

        private void mnTextBox1_TextChanged(object sender, EventArgs e)
        {

        }


    }
}
