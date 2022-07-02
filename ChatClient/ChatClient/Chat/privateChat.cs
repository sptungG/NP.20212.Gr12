using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using ChatClient.Menu;
using System.IO;

namespace ChatClient.Chat
{
    
    public partial class privateChat : Form
    {
        TcpClient _client;
        bool sendFile;
        string user;
        byte[] _buffer = new byte[4096];
        public privateChat(string user)
        {
            InitializeComponent();
            this.user = user.Trim();
            _client = new TcpClient();
            sendFile = false;
            label2.Hide();
            label3.Hide();
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            // Connect to the remote server. The IP address and port # could be
            // picked up from a settings file.
            _client.Connect("127.0.0.1", 54000);

            // Start reading the socket and receive any incoming messages
            _client.GetStream().BeginRead(_buffer,
                                            0,
                                            _buffer.Length,
                                            Server_MessageReceived,
                                            null);

            var msg = Encoding.ASCII.GetBytes("INIT|NULL|" + user);
            _client.GetStream().Write(msg, 0, msg.Length);
        }

        private void Server_MessageReceived(IAsyncResult ar)
        {
            if (ar.IsCompleted)
            {
                // End the stream read
                var bytesIn = _client.GetStream().EndRead(ar);
                if (bytesIn > 0)
                {
                    // Create a string from the received data. For this server 
                    // our data is in the form of a simple string, but it could be
                    // binary data or a JSON object. Payload is your choice.
                    var tmp = new byte[bytesIn];
                    Array.Copy(_buffer, 0, tmp, 0, bytesIn);
                    var str = Encoding.ASCII.GetString(tmp);

                    // Any actions that involve interacting with the UI must be done
                    // on the main thread. This method is being called on a worker
                    // thread so using the form's BeginInvoke() method is vital to
                    // ensure that the action is performed on the main thread.
                    BeginInvoke((Action)(() =>
                    {
                        if (str.IndexOf("|") != -1)
                        {
                            string[] words = str.Split('|');
                            string fileName = words[1];

                            DialogResult res = MessageBox.Show("Do you want to receive " + fileName + "?", "Confirmation", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                            if (res == DialogResult.OK)
                            {
                                SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                                saveFileDialog1.DefaultExt = "txt";
                                saveFileDialog1.Filter = "RichTextFile |*.rtf|Text file (*.txt)|*.txt|XML file (*.xml)|*.xml|All files (*.*)|*.*";
                                saveFileDialog1.AddExtension = true;
                                saveFileDialog1.RestoreDirectory = true;
                                saveFileDialog1.Title = "Where do you want to save the file?";
                                saveFileDialog1.InitialDirectory = @"C:/";
                                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                                {
                                    File.WriteAllText(saveFileDialog1.FileName, words[2]);
                                }
                            }
                        }
                        else
                        {
                            if (str == "C_PC_FAILURE\0")
                            {
                                label3.Show();
                            }
                            else
                            {
                                listBox1.Items.Add(str);
                                listBox1.Items.Add("");
                            }
                        }
                        
                        
                        //listBox1.SelectedIndex = listBox1.Items.Count - 1;
                    }));
                }

                // Clear the buffer and start listening again
                Array.Clear(_buffer, 0, _buffer.Length);
                _client.GetStream().BeginRead(_buffer,
                                                0,
                                                _buffer.Length,
                                                Server_MessageReceived,
                                                null);
            }
        }

        private string toNameOfFile(string name)
        {
            string[] words = name.Split('\\');
            return words[words.Length-1];
        }

        private void handleSendFile()
        {
            byte[] a = File.ReadAllBytes(textBox1.Text);
            _client.GetStream().Write(a, 0, a.Length);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox2.Text == "")
            {
                label2.Show();
                textBox2.Focus();
                return;
            }
            label2.Hide();
            label3.Hide();
            if (textBox1.Text == "") return;
            // Encode the message and send it out to the server.
            if (!sendFile)
            {
                var content = "PRIVATE_CHAT|NULL|" + textBox2.Text + "|NULL|" + textBox1.Text;
                var msg = Encoding.ASCII.GetBytes(content);
                _client.GetStream().Write(msg, 0, msg.Length);
            } else
            {
                var content = "PRIVATE_CHAT|NULL|" + textBox2.Text + "|NULL|SEND_FILE|NULL|" + toNameOfFile(textBox1.Text);
                var msg = Encoding.ASCII.GetBytes(content);
                _client.GetStream().Write(msg, 0, msg.Length);
                handleSendFile();
            }


            // Clear the text box and set it's focus
            textBox1.Text = "";
            textBox1.Focus();
            sendFile = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);

            this.Hide();
            menu chatAll = new menu(user);
            chatAll.ShowDialog();
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                sendFile = true;
                textBox1.Text = dlg.FileName;
            }
        }
    }
}
