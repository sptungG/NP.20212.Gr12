using ChatClient.Menu;
using System;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;

namespace ChatClient.Chat
{
    public partial class groupChat : Form
    {
        string user;
        TcpClient _client;
        bool done;
        byte[] _buffer = new byte[4096];

        string preveousGroupName;
        public groupChat(string user, TcpClient client)
        {
            InitializeComponent();
            this.user = user.Trim();
            _client = client;
            label2.Hide();
            done = false;
            Text = "GroupChat";
            username.Text = "User: " + user.Trim();
        }
        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            // Connect to the remote server. The IP address and port # could be
            // picked up from a settings file.
            //_client.Connect(Program.ConfigHost, Program.ConfigPort);

            // Start reading the socket and receive any incoming messages
            _client.GetStream().BeginRead(_buffer,
                                            0,
                                            _buffer.Length,
                                            Server_MessageReceived,
                                            null);
            var msg = Encoding.ASCII.GetBytes("SKIP|NULL|");
            _client.GetStream().Write(msg, 0, msg.Length);
        }

        private void Server_MessageReceived(IAsyncResult ar)
        {
            if (!done)
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
                            if (str != "Skip login page\0")
                            {
                                if (str.IndexOf("|") != -1)
                                {
                                    if (str.Substring(0, str.IndexOf("|")) == "GC_ADD_USER" || str.Substring(0, str.IndexOf("|")) == "GC_LEFT_USER")
                                    {
                                        listBox1.Items.Add("\t\t\t\t\t\t" + str.Substring(str.IndexOf("|") + 1));
                                        listBox1.Items.Add("");
                                    }
                                }
                                else
                                {
                                    if (str.Contains("Group"))
                                    {
                                        listBox1.Items.Add(str);
                                        listBox1.Items.Add("");
                                    }
                                }

                            //listBox1.SelectedIndex = listBox1.Items.Count - 1;
                            }
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
        }

        // Back Button
        private void button2_Click(object sender, EventArgs e)
        {
            done = true;
            this.Hide();
            menu chatAll = new menu(user, _client);
            chatAll.ShowDialog();
            this.Close();
        }
        // Send Chat message
        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox2.Text == "")
            {
                label2.Show();
                textBox2.Focus();
                return;
            }
            label2.Hide();
            if (textBox1.Text == "") return;
            // Encode the message and send it out to the server.

            if (textBox2.Text != preveousGroupName && preveousGroupName != null)
            {
                _client.GetStream().Write(Encoding.ASCII.GetBytes("LEFT_GROUP_CHAT|NULL|" + preveousGroupName), 0, Encoding.ASCII.GetBytes("LEFT_GROUP_CHAT|NULL|" + preveousGroupName).Length);
                preveousGroupName = textBox2.Text;
                listBox1.Items.Clear();
            }

            preveousGroupName = textBox2.Text;

            var content = "GROUP_CHAT|NULL|" + textBox2.Text + "|NULL|" + textBox1.Text;

            var msg = Encoding.ASCII.GetBytes(content);
            _client.GetStream().Write(msg, 0, msg.Length);

            // Clear the text box and set it's focus
            textBox1.Text = "";
            textBox1.Focus();
        }
        // Close GrChat Window
        private void groupChat_FormClosed(object sender, FormClosedEventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);
        }
    }
}
