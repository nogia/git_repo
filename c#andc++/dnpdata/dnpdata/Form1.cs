using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Office.Interop.Excel;
using System.IO;
using System.Xml;


namespace dnpdata
{
    public partial class formBecoConvert : Form
    {
        private DeccyptedData decryptedData;
        Microsoft.Office.Interop.Excel.Application xlApp;
        List<XmlNode> outlist = new List<XmlNode>();
        List<List<KeyValuePair<string, string>>> outlst = new List<List<KeyValuePair<string, string>>>();
        List<List<KeyValuePair<string, string>>> setpointslst = new List<List<KeyValuePair<string, string>>>();
        public formBecoConvert()
        {
            decryptedData = new DeccyptedData();
            InitializeComponent();
        }
        private DeccyptedData getDecryptedData()
        {
            return decryptedData;
        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.ShowDialog();
            ConstantValues.ENCRYPTED_FILE_NAME = openFileDialog.FileName;
            if (ConstantValues.ENCRYPTED_FILE_NAME != "")
            {
                enableControls(true);
                lblFileName.Text = "File Selected :  " + ConstantValues.ENCRYPTED_FILE_NAME + "\n";
                Archive archeveDecData = new Archive();
                decryptedData = archeveDecData.DecryptData(ConstantValues.ENCRYPTED_FILE_NAME, ConstantValues.password);
                List<string> itemsxml = new List<string>();
                string xml = decryptedData.getXML();
                XmlDocument doc = new XmlDocument();
                try
                    {
                        doc.LoadXml(xml);
                        XmlElement root = doc.DocumentElement;
                        outlist = new List<XmlNode>();
                        outlst = new List<List<KeyValuePair<string, string>>>();
                        setpointslst = new List<List<KeyValuePair<string, string>>>();
                        try
                        {
                            printNode(root);
                            for (int i = 0; i < outlist.Count; i++)
                                printRoot(outlist[i]);
                        }
                        catch
                        {
                            MessageBox.Show("Read Node Exception");
                        }

                        string[] xmllines = xml.Split('\n');
                        for (int i = 0; i < xmllines.Length; i++)
                            itemsxml.Add(xmllines[i]);
                        lstXml.DataSource = itemsxml;
                        //next  lile output decreapted text data into the file
                       // archeveDecData.outputXMLdata();
                        //next  lile output decreapted binary data into the file
                         //archeveDecData.outputxmldata();
                    }
                    catch
                    {
                        MessageBox.Show("Read XML Exception");
                    }
            }
        }
        public void printNode(XmlNode node)
        {
            if (node != null)
            {
                outlist.Add(node);
               // Console.Write(node.Name);
               // for (int i = 0; i < node.Attributes.Count; i++)
                  // Console.Write(new KeyValuePair<string, string>(node.Attributes.Item(i).Name, node.Attributes.Item(i).Value));
                //Console.Write("\n");
                if (node.HasChildNodes)
                    printNode(node.FirstChild);
                else
                {
                    if (node.NextSibling != null)
                        printNode(node.NextSibling);
                    else if (node.ParentNode != null && node.ParentNode.NextSibling != null)
                        printNode(node.ParentNode.NextSibling);
                    else if(node.ParentNode.ParentNode != null && node.ParentNode.ParentNode.NextSibling != null)
                        printNode(node.ParentNode.ParentNode.NextSibling);
                    else
                        return;
                }
            }
        }

        public void printRoot(XmlNode node)
        {
            List<KeyValuePair<string, string>> templst = new List<KeyValuePair<string, string>>();
            templst.Add(new KeyValuePair<string, string>(node.Name, node.Name));
            bool sp = false;
            if (node.Name == ConstantValues.setpoints)
                sp = true;
            for (int i = 0; i < node.Attributes.Count; i++)
            
                templst.Add(new KeyValuePair<string, string>(node.Attributes.Item(i).Name, node.Attributes.Item(i).Value));

            outlst.Add(templst);
            if (sp)
                setpointslst.Add(templst);
        }

        private void enableControls(bool value)
        {
            btnOutputDnp.Enabled = value;
            btnReadAllSettings.Enabled = value;
            lblFileName.Visible = value;

        }
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            enableControls(false);
        }

        private void btnOutputDnp_Click(object sender, EventArgs e)
        {
            if(setpointslst != null && setpointslst.Count > 0)
               ExclelOutputSetpoints(setpointslst, ConstantValues.setpointscolumnNames);
            else
                MessageBox.Show("DataList null Exception");
        }
        private void btnReadAllSettings_Click(object sender, EventArgs e)
        {
            if (outlst != null && outlst.Count > 0)
                ExclelOutputAllData(outlst, ConstantValues.alldatacolumns);
            else
                MessageBox.Show("DataList null Exception");
        }
        public void ExclelOutputAllData(List<List<KeyValuePair<string, string>>> value, string[] columns)
        {
            //create EXCEl
            xlApp = new Microsoft.Office.Interop.Excel.Application();
            Workbook xlWorkBook;
            Microsoft.Office.Interop.Excel.Worksheet xlWorkSheet;
            object misValue = System.Reflection.Missing.Value;


            xlWorkBook = xlApp.Workbooks.Add(misValue);
            // xlApp.Visible = true;
            xlWorkSheet = (Microsoft.Office.Interop.Excel.Worksheet)xlWorkBook.Worksheets.get_Item(1);
            for (int i = 0; i < columns.Length; i++)
               xlWorkSheet.Range["A1"].Offset[0, i].Value = columns[i];
            
            for (int i = 0; i < value.Count; i++)
            {
                for (int j = 0; j < value[i].Count; j++)
                {
                   
                      xlWorkSheet.Cells[i + 2, j + 1] = value[i][j].Value;
                }

            }
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "All files (*.xls)|*.xls";
            saveFileDialog.FilterIndex = 2;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.ShowDialog();
            ConstantValues.dnpExcelOut = saveFileDialog.FileName;

            xlWorkBook.SaveAs(ConstantValues.dnpExcelOut, Microsoft.Office.Interop.Excel.XlFileFormat.xlWorkbookNormal, misValue, misValue, misValue, misValue, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlShared, misValue, misValue, misValue, misValue, misValue);
            xlWorkBook.Close(true, misValue, misValue);

            xlApp.Quit();
            releaseObject(xlWorkSheet);
            releaseObject(xlWorkBook);
            releaseObject(xlApp);
        }
        public void ExclelOutputSetpoints(List<List<KeyValuePair<string, string>>> value,string[] columns)
        {
            //create EXCEl
            xlApp = new Microsoft.Office.Interop.Excel.Application();
            Workbook xlWorkBook;
            Microsoft.Office.Interop.Excel.Worksheet xlWorkSheet;
            object misValue = System.Reflection.Missing.Value;


            xlWorkBook = xlApp.Workbooks.Add(misValue);
           // xlApp.Visible = true;
            xlWorkSheet = (Microsoft.Office.Interop.Excel.Worksheet)xlWorkBook.Worksheets.get_Item(1);
            for (int i = 0; i < columns.Length; i++)
                xlWorkSheet.Range["A1"].Offset[0, i].Value = columns[i];
            for (int i = 0; i < value.Count; i++)
                for (int j = 0; j < value[i].Count; j++)
                {
                    if (j < ConstantValues.setpointscolumnNames.Length)
                        xlWorkSheet.Cells[i + 2, j + 1] = value[i][j + 1].Value;
                    else
                        break;
                }
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "All files (*.xls)|*.xls";
            saveFileDialog.FilterIndex = 2;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.ShowDialog();
            ConstantValues.dnpExcelOut = saveFileDialog.FileName;

            xlWorkBook.SaveAs(ConstantValues.dnpExcelOut, Microsoft.Office.Interop.Excel.XlFileFormat.xlWorkbookNormal, misValue, misValue, misValue, misValue, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlShared, misValue, misValue, misValue, misValue, misValue);
            xlWorkBook.Close(true, misValue, misValue);

            xlApp.Quit();
            releaseObject(xlWorkSheet);
            releaseObject(xlWorkBook);
            releaseObject(xlApp);
        }
       
      
        private void releaseObject(object obj)
        {
            try
            {
                System.Runtime.InteropServices.Marshal.ReleaseComObject(obj);
                obj = null;
            }
            catch (Exception ex)
            {
                obj = null;

            }
            finally
            {
                GC.Collect();
            }
        }

        private void lblFileName_Click(object sender, EventArgs e)
        {

        }

       
    }
}
