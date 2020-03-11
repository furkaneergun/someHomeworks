namespace CS408_GUI_PROJECT
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
            this.label_n = new System.Windows.Forms.Label();
            this.port_label = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.connect_button = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.name_textbox = new System.Windows.Forms.TextBox();
            this.port_textbox = new System.Windows.Forms.TextBox();
            this.ip_textbox = new System.Windows.Forms.TextBox();
            this.question_textbox = new System.Windows.Forms.TextBox();
            this.answer_textbox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label_n
            // 
            this.label_n.AutoSize = true;
            this.label_n.Location = new System.Drawing.Point(48, 163);
            this.label_n.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label_n.Name = "label_n";
            this.label_n.Size = new System.Drawing.Size(35, 13);
            this.label_n.TabIndex = 15;
            this.label_n.Text = "Name";
            // 
            // port_label
            // 
            this.port_label.AutoSize = true;
            this.port_label.Location = new System.Drawing.Point(58, 114);
            this.port_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.port_label.Name = "port_label";
            this.port_label.Size = new System.Drawing.Size(26, 13);
            this.port_label.TabIndex = 14;
            this.port_label.Text = "Port";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(58, 56);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "IP";
            // 
            // connect_button
            // 
            this.connect_button.Location = new System.Drawing.Point(206, 361);
            this.connect_button.Margin = new System.Windows.Forms.Padding(2);
            this.connect_button.Name = "connect_button";
            this.connect_button.Size = new System.Drawing.Size(70, 32);
            this.connect_button.TabIndex = 12;
            this.connect_button.Text = "Connect";
            this.connect_button.UseVisualStyleBackColor = true;
            this.connect_button.Click += new System.EventHandler(this.connect_button_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(340, 11);
            this.richTextBox1.Margin = new System.Windows.Forms.Padding(2);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(491, 332);
            this.richTextBox1.TabIndex = 11;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // name_textbox
            // 
            this.name_textbox.Location = new System.Drawing.Point(88, 160);
            this.name_textbox.Margin = new System.Windows.Forms.Padding(2);
            this.name_textbox.Name = "name_textbox";
            this.name_textbox.Size = new System.Drawing.Size(76, 20);
            this.name_textbox.TabIndex = 10;
            this.name_textbox.TextChanged += new System.EventHandler(this.name_textbox_TextChanged);
            // 
            // port_textbox
            // 
            this.port_textbox.Location = new System.Drawing.Point(88, 111);
            this.port_textbox.Margin = new System.Windows.Forms.Padding(2);
            this.port_textbox.Name = "port_textbox";
            this.port_textbox.Size = new System.Drawing.Size(76, 20);
            this.port_textbox.TabIndex = 9;
            this.port_textbox.TextChanged += new System.EventHandler(this.port_textbox_TextChanged);
            // 
            // ip_textbox
            // 
            this.ip_textbox.Location = new System.Drawing.Point(88, 56);
            this.ip_textbox.Margin = new System.Windows.Forms.Padding(2);
            this.ip_textbox.Name = "ip_textbox";
            this.ip_textbox.Size = new System.Drawing.Size(76, 20);
            this.ip_textbox.TabIndex = 8;
            this.ip_textbox.TextChanged += new System.EventHandler(this.ip_textbox_TextChanged);
            // 
            // question_textbox
            // 
            this.question_textbox.Location = new System.Drawing.Point(87, 207);
            this.question_textbox.Margin = new System.Windows.Forms.Padding(2);
            this.question_textbox.Multiline = true;
            this.question_textbox.Name = "question_textbox";
            this.question_textbox.Size = new System.Drawing.Size(188, 54);
            this.question_textbox.TabIndex = 16;
            this.question_textbox.TextChanged += new System.EventHandler(this.question_textbox_TextChanged);
            // 
            // answer_textbox
            // 
            this.answer_textbox.Location = new System.Drawing.Point(88, 285);
            this.answer_textbox.Margin = new System.Windows.Forms.Padding(2);
            this.answer_textbox.Multiline = true;
            this.answer_textbox.Name = "answer_textbox";
            this.answer_textbox.Size = new System.Drawing.Size(188, 58);
            this.answer_textbox.TabIndex = 17;
            this.answer_textbox.TextChanged += new System.EventHandler(this.answer_textbox_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(43, 301);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "Answer";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(34, 226);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 13);
            this.label3.TabIndex = 19;
            this.label3.Text = "Question";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(87, 361);
            this.button1.Margin = new System.Windows.Forms.Padding(2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(103, 32);
            this.button1.TabIndex = 20;
            this.button1.Text = "Send Question";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(7, 361);
            this.button2.Margin = new System.Windows.Forms.Padding(2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(68, 32);
            this.button2.TabIndex = 21;
            this.button2.Text = "Answer";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(298, 361);
            this.button3.Margin = new System.Windows.Forms.Padding(2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(70, 32);
            this.button3.TabIndex = 22;
            this.button3.Text = "Disconnect";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(842, 414);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.answer_textbox);
            this.Controls.Add(this.question_textbox);
            this.Controls.Add(this.label_n);
            this.Controls.Add(this.port_label);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.connect_button);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.name_textbox);
            this.Controls.Add(this.port_textbox);
            this.Controls.Add(this.ip_textbox);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_n;
        private System.Windows.Forms.Label port_label;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button connect_button;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.TextBox name_textbox;
        private System.Windows.Forms.TextBox port_textbox;
        private System.Windows.Forms.TextBox ip_textbox;
        private System.Windows.Forms.TextBox question_textbox;
        private System.Windows.Forms.TextBox answer_textbox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
    }
}

