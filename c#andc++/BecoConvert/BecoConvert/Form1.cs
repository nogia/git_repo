using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DecryptUtil;
using XMLInOut;
using System.IO;

namespace BecoConvert
{
    public partial class FormBecoConvert : Form
    {
        public FormBecoConvert()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
       
        private string pass = "BECKWITH";
        string savefilename = "";
        

        public KeyValuePair<MemoryStream, int> convertToMemoryStream(string filename)
        {
            MemoryStream ms = new MemoryStream(File.ReadAllBytes(filename).Length);
            (new FileStream(filename, FileMode.Open, FileAccess.Read)).CopyTo(ms);
           
            return new KeyValuePair<MemoryStream, int>(ms, File.ReadAllBytes(filename).Length);
        }
     

        public List<XMLInOut.Task> createTasks()
        {
            List<XMLInOut.Task> tasklst = new List<XMLInOut.Task>();
            Task temp = new Task();

            temp = new Task();
            temp.taskid = 0;
            temp.taskname = "SP";
            string[] tmpstr10 = { "NAME", "VALUE", "REGISTER" };
            temp.columnnames = tmpstr10;
            string[] tmpstr11 = { "ID", "V", "REG" };
            temp.selectedcolumns = tmpstr11;
            temp.outfile = "";
            tasklst.Add(temp);

            return tasklst;
        }
        private List<string> createDataList(DecryptUtil.DeccyptedData data)
        {
            if (data != null)
            {
                List<string> xml = new List<string>();
                for (int i = 0; i < data.getCount(); i++)
                    xml.Add(data.getXML(i));

                return xml;
            }
            else
                return null;
        }
        private void outDecryptedData(string[] seperator,string filenamefortextdata, string filenameforbinarydata)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.ShowDialog();

            if (openFileDialog.FileName != "")
            {
             
                if((seperator == null) || ( seperator != null && seperator.Length == 0) ) 
                {
                    seperator = new string[1];
                    seperator[0] = "\0";
                }
               
                DecryptUtil.Archive archeveDecData = new DecryptUtil.Archive(openFileDialog.FileName, pass, seperator);
                DecryptUtil.DeccyptedData decryptedData = archeveDecData.getDecryptedData();
                outputDataList(decryptedData, filenamefortextdata, filenameforbinarydata);
             
            }
        }
       
        private void outputDataList(DecryptUtil.DeccyptedData data, string outfiletext, string outfilebin)
        {
            if (data != null && outfiletext != null && outfiletext != "" && outfilebin != null && outfilebin != "")
            {
                for (int i = 0; i < data.getCount(); i++)
                {
                    data.outputXMLdata(outfiletext + i + ".xml", i);
                    data.outputxmldata(outfilebin + i + ".xml", i);
                }
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void decryptToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.ShowDialog();

            if (openFileDialog.FileName != "")
            {
                string[] seperator = { "\0" };
                DecryptUtil.Archive archeveDecData = new DecryptUtil.Archive(openFileDialog.FileName, pass, seperator);
                DecryptUtil.DeccyptedData decryptedData = archeveDecData.getDecryptedData();
                //outputDataList(decryptedData, "\\\\ENG83-WIN7//Share//Modbus//data//checkfiletextfromMemoryStream.dec", "\\\\ENG83-WIN7//Share//Modbus//data//checkfilebinaryfromMemoryStream");

                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "All files (*.xls)|*.xls";
                saveFileDialog.FilterIndex = 2;
                saveFileDialog.RestoreDirectory = true;
                saveFileDialog.ShowDialog();

                lblfilepath.Text = lblfilepath.Text + " " + openFileDialog.FileName;
                lblfilepath.Enabled = true;
                savefilename = saveFileDialog.FileName;
                string[] sep = { ".xls" };
                string[] temp = savefilename.Split(sep, System.StringSplitOptions.None);

                List<string> xml = createDataList(decryptedData);

              

                if (xml != null)
                {
                    List<XMLInOut.Task> tasklst = createTasks();
                    for (int i = 0; i < xml.Count; i++)
                    {
                        if (savefilename != "")
                        {
                            for (int j = 0; j < tasklst.Count; j++)
                                tasklst[j].outfile = savefilename;// +"xml" + i + "task" + j + ".xls";
                            //output into list
                            string[] xmllines = xml[i].Split('\n');
                            List<string> itemsxml = new List<string>();
                            for (int j = 0; j < xmllines.Length; j++)
                                itemsxml.Add(xmllines[j]);
                            lstXml.DataSource = itemsxml;
                            XMLInOut.xmlutility task = new XMLInOut.xmlutility(xml[i].ToString(), tasklst);
                        }
                    }
                }
            }

        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string[] seperator = {};
              outDecryptedData(seperator, "\\\\ENG83-WIN7//Share//BecoConvert//data//checkfiletextfromMemoryStream.dec" , "\\\\ENG83-WIN7//Share//BecoConvert//data//checkfilebinaryfromMemoryStream");
        
        }

       

     
    }
}
