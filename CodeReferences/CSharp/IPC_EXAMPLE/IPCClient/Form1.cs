using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// Named pipe
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.IO;

namespace IPCClient
{
    public partial class Form1 : Form
    {
        NamedPipeClientStream m_pipeClient;

        public Form1()
        {
            InitializeComponent();

            ipcStateTb.Text = "Not connected";

            // Connect IPC
            ipcStateTb.Text = "Attempting to connect";
            m_pipeClient = new NamedPipeClientStream(@".", @"PIPE_ADDRESS", PipeDirection.InOut);
            m_pipeClient.Connect();

            ipcStateTb.Text = "Connected";

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            using (StreamReader sr = new StreamReader(m_pipeClient))
            {
                // Display
                for (int i = 0; i < 10; i++)
                {
                    byte[] arByte = new byte[10];
                    m_pipeClient.Read(arByte, 0, 10);
                    ipcMessageTb.Text += System.Text.Encoding.UTF8.GetString(arByte, 0, arByte.Length);
                }
            }
            ipcStateTb.Text = "Connection terminated";
        }
    }
}
