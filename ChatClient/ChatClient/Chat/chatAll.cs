using ChatClient.Menu;
using System;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace ChatClient
{
    public partial class chatAll : Form
    {

        // The .net wrapper around WinSock sockets.
        TcpClient _client;
        bool done;
        string user;
        /// <summary>
        /// Buffer to store incoming messages from the server.
        /// </summary>
        byte[] _buffer = new byte[4096];

        public chatAll(string user, TcpClient client)
        {
            InitializeComponent();
            this.user = user.Trim();
            _client = client;
            done = false;
            Text = "ChatAll - " + user.Trim();
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
                        listBox1.Invoke((Action)(() =>
                        {
                            if (str != "Skip login page\0" && !str.Contains("Private") && !str.Contains("Group") && !str.Contains("FILE|"))
                            {
                                listBox1.Items.Add(str);
                                listBox1.Items.Add("");
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") return;
            // Encode the message and send it out to the server.

            var content = "CHAT_ALL|NULL|" + textBox1.Text;

            var msg = Encoding.ASCII.GetBytes(content);
            _client.GetStream().Write(msg, 0, msg.Length);

            // Clear the text box and set it's focus
            textBox1.Text = "";
            textBox1.Focus();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }


        private void button2_Click(object sender, EventArgs e)
        {
            done = true;
            this.Hide();
            menu chatAll = new menu(user, _client);
            chatAll.ShowDialog();
            this.Close();
        }

        private void chatAll_FormClosed(object sender, FormClosedEventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);
        }
    }
}
