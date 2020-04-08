namespace dnpdata
{
    partial class formBecoConvert
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
            this.btnOutputDnp = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblFileName = new System.Windows.Forms.Label();
            this.lstXml = new System.Windows.Forms.ListBox();
            this.btnReadAllSettings = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnOutputDnp
            // 
            this.btnOutputDnp.Location = new System.Drawing.Point(36, 95);
            this.btnOutputDnp.Name = "btnOutputDnp";
            this.btnOutputDnp.Size = new System.Drawing.Size(83, 51);
            this.btnOutputDnp.TabIndex = 0;
            this.btnOutputDnp.Text = "Output Modbus DNP SetPoints";
            this.btnOutputDnp.UseVisualStyleBackColor = true;
            this.btnOutputDnp.Click += new System.EventHandler(this.btnOutputDnp_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1000, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // lblFileName
            // 
            this.lblFileName.AutoSize = true;
            this.lblFileName.Location = new System.Drawing.Point(42, 40);
            this.lblFileName.Name = "lblFileName";
            this.lblFileName.Size = new System.Drawing.Size(77, 13);
            this.lblFileName.TabIndex = 2;
            this.lblFileName.Text = "File Selected : ";
            this.lblFileName.Click += new System.EventHandler(this.lblFileName_Click);
            // 
            // lstXml
            // 
            this.lstXml.FormattingEnabled = true;
            this.lstXml.Location = new System.Drawing.Point(140, 102);
            this.lstXml.Name = "lstXml";
            this.lstXml.Size = new System.Drawing.Size(792, 368);
            this.lstXml.TabIndex = 3;
            // 
            // btnReadAllSettings
            // 
            this.btnReadAllSettings.Location = new System.Drawing.Point(36, 187);
            this.btnReadAllSettings.Name = "btnReadAllSettings";
            this.btnReadAllSettings.Size = new System.Drawing.Size(83, 58);
            this.btnReadAllSettings.TabIndex = 4;
            this.btnReadAllSettings.Text = "Output All Settings";
            this.btnReadAllSettings.UseVisualStyleBackColor = true;
            this.btnReadAllSettings.Click += new System.EventHandler(this.btnReadAllSettings_Click);
            // 
            // formBecoConvert
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1000, 484);
            this.Controls.Add(this.btnReadAllSettings);
            this.Controls.Add(this.lstXml);
            this.Controls.Add(this.lblFileName);
            this.Controls.Add(this.btnOutputDnp);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "formBecoConvert";
            this.Text = "Beco Convert";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOutputDnp;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Label lblFileName;
        private System.Windows.Forms.ListBox lstXml;
        private System.Windows.Forms.Button btnReadAllSettings;
    }
}

