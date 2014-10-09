using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Forms;

namespace MnWpf32Test
{
    /// <summary>
    /// Interaction logic for Window2.xaml
    /// </summary>
    public partial class Window2 : Window
    {
        public Window2()
        {
            InitializeComponent();

            dataGrid1.ItemsSource = new People[]

            {

                new People(){ Name1 = "王", Score1 = "100" },

                new People(){ Name1 = "刘", Score1 = "30" },

                new People(){ Name1 = "李", Score1 = "86" },

                new People(){ Name1 = "赵", Score1 = "50" }

            };
        }
    }
}
