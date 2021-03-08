using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TrafficAccidentInquiryProgram
{
    public partial class Form1 : Form
    {
        string si, gu;
        List<string[]> tail = new List<string[]>();
        
        DataTable dataTable = new DataTable();
        public Form1()
        {
            InitializeComponent();
        }

        private void text_input_si_TextChanged(object sender, EventArgs e)
        {

        }

        /*전체 데이터 조회*/
        private void button1_Click(object sender, EventArgs e)
        {
            dataGridView1.DataSource = null;
            dataTable.Clear();
            for (int i = 0; i < tail.Count(); i++)
            {
                dataTable.Rows.Add(tail[i][0], tail[i][1], tail[i][2], tail[i][3], tail[i][4], tail[i][5], tail[i][6],
                    tail[i][7], tail[i][8], tail[i][9], tail[i][10], tail[i][11], tail[i][12]);
            }
            dataGridView1.DataSource = dataTable;
        }

        /*초기 로드*/
        private void Form1_Load(object sender, EventArgs e)
        {
            StreamReader sr = new StreamReader("data.csv", Encoding.GetEncoding("euc-kr"));
            //StreamReader sr = new StreamReader("data.csv");
            while (!sr.EndOfStream)
            {
                string s = sr.ReadLine();
                string[] temp = s.Split(',');        // Split() 메서드를 이용하여 ',' 구분하여 잘라냄
                tail.Add(temp);
            }
            sr.Close();

            dataTable.Columns.Add("시,도", typeof(string));
            dataTable.Columns.Add("시,군,구", typeof(string));
            dataTable.Columns.Add("횡단보도 위", typeof(string));
            dataTable.Columns.Add("횡단보도 부근", typeof(string));
            dataTable.Columns.Add("터널 안", typeof(string));
            dataTable.Columns.Add("교량 위", typeof(string));
            dataTable.Columns.Add("기타 단일로", typeof(string));
            dataTable.Columns.Add("교차로 내", typeof(string));
            dataTable.Columns.Add("교차로 부근", typeof(string));
            dataTable.Columns.Add("건널목", typeof(string));
            dataTable.Columns.Add("기타 / 불명", typeof(string));
            dataTable.Columns.Add("고가도로 위", typeof(string));
            dataTable.Columns.Add("지하도로 내", typeof(string));
            dataGridView1.DataSource = dataTable;

        }

        private void reset_Click(object sender, EventArgs e)
        {
            dataGridView1.DataSource = null;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int[] sum_list = new int[11];
            dataTable.Clear();
            si = text_input_si.Text;
            int[] si_sum = new int[11];
            for (int i = 0; i < tail.Count(); i++)
            {
                if (tail[i][0] == si)
                {
                    for(int j = 0; j <11; j++)
                    {
                        si_sum[j] += Int32.Parse(tail[i][2 + j]);
                    }
                }
            }
            dataTable.Rows.Add(si,"모든 구",si_sum[0], si_sum[1], si_sum[2], si_sum[3], si_sum[4], si_sum[5], si_sum[6], si_sum[7], si_sum[8], si_sum[9], si_sum[10]);
            dataGridView1.DataSource = dataTable;
        }

        private void gu_sum_button_Click(object sender, EventArgs e)
        {
            int[] gu_sum_list = new int[11];
            gu = text_input_gu.Text;

            dataTable.Clear();
            for (int i = 0; i < tail.Count; i++)
            {
                if (gu == tail[i][1])
                {
                    for (int j = 0; j < 11; j++)
                    {
                        gu_sum_list[j] += Int32.Parse(tail[i][j + 2]);
                    }
                }
            }
            dataTable.Rows.Add("모든 시에서 동일한 이름의 구들의 합", gu, gu_sum_list[0], gu_sum_list[1], gu_sum_list[2], gu_sum_list[3], gu_sum_list[4], gu_sum_list[5], gu_sum_list[6], gu_sum_list[7], gu_sum_list[8], gu_sum_list[9], gu_sum_list[10]);
            dataGridView1.DataSource = dataTable;
        }

        private void search_button_Click(object sender, EventArgs e)
        {
            dataGridView1.DataSource = null;
    
            dataTable.Clear();
            si = text_input_si.Text;
            gu = text_input_gu.Text;
            for (int i = 0; i < tail.Count(); i++)
            {
                if (tail[i][0] == si && tail[i][1] == gu)
                {
                    dataTable.Rows.Add(tail[i][0], tail[i][1], tail[i][2], tail[i][3], tail[i][4], tail[i][5], tail[i][6],
                        tail[i][7], tail[i][8], tail[i][9], tail[i][10], tail[i][11], tail[i][12]);
                }
            }
            dataGridView1.DataSource = dataTable;
        }
    }
}
