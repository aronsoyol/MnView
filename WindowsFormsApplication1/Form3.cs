using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MongolDotNet;

namespace WindowsFormsApplication1
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }
        List<MnTextView> mtbList = new List<MnTextView>();
        private void btnInsert_Click(object sender, EventArgs e)
        {
            MnTextView mnTextBox = new MnTextView();
            //try
            //{
                mtbList.Add(mnTextBox);
                this.SuspendLayout();
                mnTextBox.Multiline = true; mnTextBox.Multiline = true;
                mnTextBox.Size = new Size(30, 150);
                mnTextBox.Location = new Point((mtbList.Count - 1) * mnTextBox.Size.Width, 0);
                mnTextBox.Text = "mnTextBox" + (mtbList.Count - 1);
                mnTextBox.Font = Font;
                //mnTextBox.ForeColor = System.Drawing.SystemColors.Highlight;
                //mnTextBox.Location = new System.Drawing.Point(12, 66);
                //
                mnTextBox.Name = "mnTextBox";
                mnTextBox.Leave += mnTextBox_Leave;
                mnTextBox.Enter += mnTextBox_Enter;
                mnTextBox.KeyPress += mnTextBox_KeyPress;
                mnTextBox.TextChanged += mnTextBox_TextChanged;
                mnTextBox.BackColorChanged += mnTextBox_BackColorChanged;
                mnTextBox.ForeColorChanged += mnTextBox_BackColorChanged;
                mnTextBox.KeyDown += mnTextBox_KeyDown;
                
                this.Controls.Add(mnTextBox);
                this.ResumeLayout(false);
                this.PerformLayout();
                mnTextBox.Focus();
            //}
            //catch (System.NullReferenceException)
            //{
            //    int 
            //}
        }
        private void mnTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {

        }
        private void mnTextBox_TextChanged(object sender, EventArgs e)
        {
        }
        private void mnTextBox_Leave(object sender, EventArgs e)
        {
            textBox1.Text = ((MnTextView)sender).Text;
            ((MnTextView)sender).SelectionLength = 0;
            ((MnTextView)sender).BackColor = Color.White;
        }
        private void mnTextBox_Enter(object sender, EventArgs e)
        {
            textBox1.Text = ((MnTextView)sender).Text;
            ((MnTextView)sender).BackColor = Color.Wheat;
        }
        private void mnTextBox_BackColorChanged(object sender, EventArgs e)
        {

        }
        private void mnTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            textBox1.Text += e.KeyCode.ToString();
        }
        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (mtbList.Count == 0) return;
            this.SuspendLayout();
            MnTextView mnTextBox = mtbList[mtbList.Count - 1];
            Controls.Remove(mnTextBox);
            mtbList.Remove(mnTextBox);
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private void Form3_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_Leave(object sender, EventArgs e)
        {
            textBox1.Text = ((TextBox)sender).Text;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_ForeColorChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_BackColorChanged(object sender, EventArgs e)
        {

        }

        private void Form3_KeyPress(object sender, KeyPressEventArgs e)
        {

        }

        private void Form3_BackColorChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {

        }
    }
}
