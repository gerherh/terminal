
namespace StopWatch
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.time_diplay_label = new System.Windows.Forms.Label();
            this.start_button = new System.Windows.Forms.Button();
            this.stop_button = new System.Windows.Forms.Button();
            this.record_button = new System.Windows.Forms.Button();
            this.reset_button = new System.Windows.Forms.Button();
            this.record_listbox = new System.Windows.Forms.ListBox();
            this.timeRecordBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.timer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.timeRecordBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // time_diplay_label
            // 
            this.time_diplay_label.Font = new System.Drawing.Font("굴림", 48F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.time_diplay_label.Location = new System.Drawing.Point(51, 131);
            this.time_diplay_label.Name = "time_diplay_label";
            this.time_diplay_label.Size = new System.Drawing.Size(436, 66);
            this.time_diplay_label.TabIndex = 0;
            this.time_diplay_label.Text = "00:00:00";
            // 
            // start_button
            // 
            this.start_button.Location = new System.Drawing.Point(62, 233);
            this.start_button.Name = "start_button";
            this.start_button.Size = new System.Drawing.Size(75, 23);
            this.start_button.TabIndex = 1;
            this.start_button.Text = "시작";
            this.start_button.UseVisualStyleBackColor = true;
            this.start_button.Click += new System.EventHandler(this.start_button_Click);
            // 
            // stop_button
            // 
            this.stop_button.Location = new System.Drawing.Point(62, 282);
            this.stop_button.Name = "stop_button";
            this.stop_button.Size = new System.Drawing.Size(75, 23);
            this.stop_button.TabIndex = 2;
            this.stop_button.Text = "중지";
            this.stop_button.UseVisualStyleBackColor = true;
            this.stop_button.Click += new System.EventHandler(this.stop_button_Click);
            // 
            // record_button
            // 
            this.record_button.Location = new System.Drawing.Point(171, 233);
            this.record_button.Name = "record_button";
            this.record_button.Size = new System.Drawing.Size(75, 23);
            this.record_button.TabIndex = 3;
            this.record_button.Text = "시간 기록";
            this.record_button.UseVisualStyleBackColor = true;
            this.record_button.Click += new System.EventHandler(this.record_button_Click);
            // 
            // reset_button
            // 
            this.reset_button.Location = new System.Drawing.Point(171, 282);
            this.reset_button.Name = "reset_button";
            this.reset_button.Size = new System.Drawing.Size(75, 23);
            this.reset_button.TabIndex = 4;
            this.reset_button.Text = "리셋";
            this.reset_button.UseVisualStyleBackColor = true;
            this.reset_button.Click += new System.EventHandler(this.reset_button_Click);
            // 
            // record_listbox
            // 
            this.record_listbox.DataSource = this.timeRecordBindingSource;
            this.record_listbox.DisplayMember = "time_record";
            this.record_listbox.FormattingEnabled = true;
            this.record_listbox.ItemHeight = 12;
            this.record_listbox.Location = new System.Drawing.Point(464, 12);
            this.record_listbox.Name = "record_listbox";
            this.record_listbox.Size = new System.Drawing.Size(276, 412);
            this.record_listbox.TabIndex = 5;
            this.record_listbox.ValueMember = "time_record";
            // 
            // timeRecordBindingSource
            // 
            this.timeRecordBindingSource.DataSource = typeof(StopWatch.TimeRecord);
            // 
            // timer
            // 
            this.timer.Interval = 30;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.record_listbox);
            this.Controls.Add(this.reset_button);
            this.Controls.Add(this.record_button);
            this.Controls.Add(this.stop_button);
            this.Controls.Add(this.start_button);
            this.Controls.Add(this.time_diplay_label);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.timeRecordBindingSource)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label time_diplay_label;
        private System.Windows.Forms.Button start_button;
        private System.Windows.Forms.Button stop_button;
        private System.Windows.Forms.Button record_button;
        private System.Windows.Forms.Button reset_button;
        private System.Windows.Forms.ListBox record_listbox;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.BindingSource timeRecordBindingSource;
    }
}

