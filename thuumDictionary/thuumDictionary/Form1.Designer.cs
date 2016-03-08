namespace thuumDictionary
{
    partial class mainForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.closeButtonPicbox = new System.Windows.Forms.PictureBox();
            this.minButtonPicbox = new System.Windows.Forms.PictureBox();
            this.engToDragRadio = new System.Windows.Forms.RadioButton();
            this.dragToEngRadio = new System.Windows.Forms.RadioButton();
            this.entryCbox = new System.Windows.Forms.ComboBox();
            this.tranLabel = new System.Windows.Forms.Label();
            this.typeLabel = new System.Windows.Forms.Label();
            this.canonLabel = new System.Windows.Forms.Label();
            this.notesLabel = new System.Windows.Forms.Label();
            this.addNotesLabel = new System.Windows.Forms.Label();
            this.eventTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.closeButtonPicbox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.minButtonPicbox)).BeginInit();
            this.SuspendLayout();
            // 
            // closeButtonPicbox
            // 
            this.closeButtonPicbox.BackColor = System.Drawing.Color.Transparent;
            this.closeButtonPicbox.Image = ((System.Drawing.Image)(resources.GetObject("closeButtonPicbox.Image")));
            this.closeButtonPicbox.Location = new System.Drawing.Point(466, 209);
            this.closeButtonPicbox.Name = "closeButtonPicbox";
            this.closeButtonPicbox.Size = new System.Drawing.Size(21, 21);
            this.closeButtonPicbox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.closeButtonPicbox.TabIndex = 0;
            this.closeButtonPicbox.TabStop = false;
            this.closeButtonPicbox.Click += new System.EventHandler(this.closeButtonPicbox_Click);
            this.closeButtonPicbox.MouseEnter += new System.EventHandler(this.closeButtonPicbox_MouseEnter);
            this.closeButtonPicbox.MouseLeave += new System.EventHandler(this.closeButtonPicbox_MouseLeave);
            // 
            // minButtonPicbox
            // 
            this.minButtonPicbox.BackColor = System.Drawing.Color.Transparent;
            this.minButtonPicbox.Image = ((System.Drawing.Image)(resources.GetObject("minButtonPicbox.Image")));
            this.minButtonPicbox.Location = new System.Drawing.Point(439, 209);
            this.minButtonPicbox.Name = "minButtonPicbox";
            this.minButtonPicbox.Size = new System.Drawing.Size(21, 21);
            this.minButtonPicbox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.minButtonPicbox.TabIndex = 1;
            this.minButtonPicbox.TabStop = false;
            this.minButtonPicbox.Click += new System.EventHandler(this.minButtonPicbox_Click);
            this.minButtonPicbox.MouseEnter += new System.EventHandler(this.minButtonPicbox_MouseEnter);
            this.minButtonPicbox.MouseLeave += new System.EventHandler(this.minButtonPicbox_MouseLeave);
            // 
            // engToDragRadio
            // 
            this.engToDragRadio.AutoSize = true;
            this.engToDragRadio.BackColor = System.Drawing.Color.Transparent;
            this.engToDragRadio.ForeColor = System.Drawing.Color.LightGray;
            this.engToDragRadio.Location = new System.Drawing.Point(197, 236);
            this.engToDragRadio.Name = "engToDragRadio";
            this.engToDragRadio.Size = new System.Drawing.Size(115, 17);
            this.engToDragRadio.TabIndex = 2;
            this.engToDragRadio.TabStop = true;
            this.engToDragRadio.Text = "  English to Dragon";
            this.engToDragRadio.UseVisualStyleBackColor = false;
            this.engToDragRadio.CheckedChanged += new System.EventHandler(this.engToDragRadio_CheckedChanged);
            // 
            // dragToEngRadio
            // 
            this.dragToEngRadio.AutoSize = true;
            this.dragToEngRadio.BackColor = System.Drawing.Color.Transparent;
            this.dragToEngRadio.ForeColor = System.Drawing.Color.LightGray;
            this.dragToEngRadio.Location = new System.Drawing.Point(342, 236);
            this.dragToEngRadio.Name = "dragToEngRadio";
            this.dragToEngRadio.Size = new System.Drawing.Size(115, 17);
            this.dragToEngRadio.TabIndex = 3;
            this.dragToEngRadio.TabStop = true;
            this.dragToEngRadio.Text = "  Dragon to English";
            this.dragToEngRadio.UseVisualStyleBackColor = false;
            this.dragToEngRadio.CheckedChanged += new System.EventHandler(this.dragToEngRadio_CheckedChanged);
            // 
            // entryCbox
            // 
            this.entryCbox.FormattingEnabled = true;
            this.entryCbox.Location = new System.Drawing.Point(197, 284);
            this.entryCbox.Name = "entryCbox";
            this.entryCbox.Size = new System.Drawing.Size(109, 21);
            this.entryCbox.TabIndex = 4;
            // 
            // tranLabel
            // 
            this.tranLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.tranLabel.BackColor = System.Drawing.Color.Transparent;
            this.tranLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tranLabel.ForeColor = System.Drawing.Color.Gainsboro;
            this.tranLabel.Location = new System.Drawing.Point(339, 284);
            this.tranLabel.MaximumSize = new System.Drawing.Size(200, 60);
            this.tranLabel.Name = "tranLabel";
            this.tranLabel.Size = new System.Drawing.Size(140, 56);
            this.tranLabel.TabIndex = 5;
            this.tranLabel.Text = "translation";
            // 
            // typeLabel
            // 
            this.typeLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.typeLabel.AutoSize = true;
            this.typeLabel.BackColor = System.Drawing.Color.Transparent;
            this.typeLabel.ForeColor = System.Drawing.Color.LightGray;
            this.typeLabel.Location = new System.Drawing.Point(351, 340);
            this.typeLabel.Name = "typeLabel";
            this.typeLabel.Size = new System.Drawing.Size(27, 13);
            this.typeLabel.TabIndex = 6;
            this.typeLabel.Text = "type";
            this.typeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // canonLabel
            // 
            this.canonLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.canonLabel.AutoSize = true;
            this.canonLabel.BackColor = System.Drawing.Color.Transparent;
            this.canonLabel.ForeColor = System.Drawing.Color.LightGray;
            this.canonLabel.Location = new System.Drawing.Point(420, 340);
            this.canonLabel.Name = "canonLabel";
            this.canonLabel.Size = new System.Drawing.Size(37, 13);
            this.canonLabel.TabIndex = 7;
            this.canonLabel.Text = "canon";
            // 
            // notesLabel
            // 
            this.notesLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.notesLabel.BackColor = System.Drawing.Color.Transparent;
            this.notesLabel.ForeColor = System.Drawing.Color.LightGray;
            this.notesLabel.Location = new System.Drawing.Point(197, 342);
            this.notesLabel.Name = "notesLabel";
            this.notesLabel.Size = new System.Drawing.Size(148, 65);
            this.notesLabel.TabIndex = 8;
            this.notesLabel.Text = "notes";
            // 
            // addNotesLabel
            // 
            this.addNotesLabel.AutoSize = true;
            this.addNotesLabel.BackColor = System.Drawing.Color.Transparent;
            this.addNotesLabel.ForeColor = System.Drawing.Color.LightSteelBlue;
            this.addNotesLabel.Location = new System.Drawing.Point(197, 327);
            this.addNotesLabel.Name = "addNotesLabel";
            this.addNotesLabel.Size = new System.Drawing.Size(87, 13);
            this.addNotesLabel.TabIndex = 9;
            this.addNotesLabel.Text = "Additional Notes:";
            this.addNotesLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // eventTimer
            // 
            this.eventTimer.Enabled = true;
            this.eventTimer.Interval = 10;
            this.eventTimer.Tick += new System.EventHandler(this.eventTimer_Tick);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Desktop;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(768, 463);
            this.ControlBox = false;
            this.Controls.Add(this.addNotesLabel);
            this.Controls.Add(this.notesLabel);
            this.Controls.Add(this.canonLabel);
            this.Controls.Add(this.typeLabel);
            this.Controls.Add(this.tranLabel);
            this.Controls.Add(this.entryCbox);
            this.Controls.Add(this.dragToEngRadio);
            this.Controls.Add(this.engToDragRadio);
            this.Controls.Add(this.minButtonPicbox);
            this.Controls.Add(this.closeButtonPicbox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "mainForm";
            this.Text = "Dovahzul Dictionary";
            this.TransparencyKey = System.Drawing.Color.Red;
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseUp);
            ((System.ComponentModel.ISupportInitialize)(this.closeButtonPicbox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.minButtonPicbox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox closeButtonPicbox;
        private System.Windows.Forms.PictureBox minButtonPicbox;
        private System.Windows.Forms.RadioButton engToDragRadio;
        private System.Windows.Forms.RadioButton dragToEngRadio;
        private System.Windows.Forms.ComboBox entryCbox;
        private System.Windows.Forms.Label tranLabel;
        private System.Windows.Forms.Label typeLabel;
        private System.Windows.Forms.Label canonLabel;
        private System.Windows.Forms.Label notesLabel;
        private System.Windows.Forms.Label addNotesLabel;
        private System.Windows.Forms.Timer eventTimer;
    }
}

