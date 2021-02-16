using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StopWatch
{
    public partial class Form1 : Form
    {
        DateTime start_time, cur_time;
        TimeSpan stop_watch;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            start_time = DateTime.Now;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            cur_time = DateTime.Now;
            stop_watch = cur_time - start_time;
            time_diplay_label.Text = stop_watch.ToString();
        }

        private void start_button_Click(object sender, EventArgs e)
        {
            timer.Enabled = true;
        }

        private void record_button_Click(object sender, EventArgs e)
        {
            TimeRecord time = new TimeRecord();
            time.time_record = stop_watch.ToString(@"hh\:mm\:ss\.ffff");
            timeRecordBindingSource.Add(time);
        }

        private void reset_button_Click(object sender, EventArgs e)
        {
            start_time = cur_time;
            stop_watch = cur_time - start_time;
            time_diplay_label.Text = stop_watch.ToString();
            timeRecordBindingSource.Clear();
        }

        private void stop_button_Click(object sender, EventArgs e)
        {
            timer.Enabled = false;
        }
    }
}
