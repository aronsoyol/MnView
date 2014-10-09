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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;

namespace MnWpf32Test
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataTable dt = new DataTable();
            dt.Columns.Add("ID");
            dt.Columns.Add("Name");
            DataRow r1 = dt.NewRow();
            r1["ID"] = 11;
            r1["Name"] = "aa";

            DataRow r2= dt.NewRow();
            r1["ID"] = 22;
            r1["Name"] = "bb";

            dt.Rows.Add(r1);
            dt.Rows.Add(r2);

            string[,] source = new string[4, 2] { { "11", "aa" }, { "22", "bb" }, { "33", "cc" }, { "44", "dd" } };

        }
    }
}
