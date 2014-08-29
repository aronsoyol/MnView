using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace WindowsFormsControlLibrary1
{
    [Guid(UserControl1.ClassId)] 
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
        }

        public const string ClassId = "61C71E4E-6999-4375-9E62-6326C98B740A";
        private void UserControl1_Load(object sender, EventArgs e)
        {

        }
        [Browsable(true)]
        public override string Text
        {
            get
            {
                return base.Text;
            }
            set
            {
                base.Text = value;
            }
        }
    }
}
