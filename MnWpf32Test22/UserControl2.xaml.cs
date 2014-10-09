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
using MongolDotNet;
namespace MnWpf32Test
{
    /// <summary>
    /// Interaction logic for UserControl2.xaml
    /// </summary>
    public partial class UserControl2 : UserControl
    {

        public UserControl2()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty MnTextProperty = DependencyProperty.Register("MnText", typeof(String
        ), typeof(UserControl2), new PropertyMetadata(new PropertyChangedCallback(propertyChangedCallback)));



        public string MnText
        {
            get
            {
                return (string)this.GetValue(MnTextProperty);
            }
            set
            {
                this.SetValue(MnTextProperty, value);
            }
        }


        private static void propertyChangedCallback(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            UserControl2 userControl = sender as UserControl2;

            if (userControl != null)
            {
                if (e.Property == MnTextProperty)
                {
                    userControl.abc.Text = (string)e.NewValue;
                }


            }

        }

        private void abc_TextChanged(object sender, EventArgs e)
        {
            MnText = this.abc.Text;
        }


        static void propertyChangedCallback2(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {




            //VUMeter vuMeter = (sender as VUMeter);
            //if (vuMeter != null)
            //{
            //    if (e.Property == VUMeterDrawProperty)
            //    {
            //        if ((VUMeterDraw)e.NewValue == null)
            //        {
            //            return;
            //        }
            //        vuMeter.VUMeterDraw = (VUMeterDraw)e.NewValue;
            //        return;
            //    }

            //    if (e.Property == VUMeterDrawByIndexProperty)
            //    {
            //        if ((VUMeterDrawByIndex)e.NewValue == null)
            //        {
            //            return;
            //        }
            //        vuMeter.VUMeterDrawByIndex = (VUMeterDrawByIndex)e.NewValue;
            //        return;
            //    }

            //    if (e.Property == VuMeterShowerProperty)
            //    {
            //        vuMeter.VuMeterShower = (VuMeterShower)e.NewValue;
            //        vuMeter.ShowVuMeter(vuMeter.VuMeterShower);
            //        return;
            //    }
            //}
        }

        private void windowsFormsHost1_LayoutError(object sender, System.Windows.Forms.Integration.LayoutExceptionEventArgs e)
        {
            e.ThrowException = false;
        }

    }
}
