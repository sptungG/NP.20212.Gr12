using System;
using ChatClient.Menu;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;

namespace ChatClient.Login
{
    public partial class login : Form
    {
        TcpClient _client;
        
        bool pass;
        byte[] _buffer = new byte[4096];
        public login()
        {
            InitializeComponent();
            _client = new TcpClient();
            pass = false;
            label3.Hide();
            label4.Hide();
            label5.Hide();
            label6.Hide();
            label7.Hide();
            textBox2.PasswordChar = '*' ;
            this.AcceptButton = button3;
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            // Connect to the remote server. The IP address and port # could be
            // picked up from a settings file.
             _client.Connect(Program.ConfigHost, Program.ConfigPort);

            // Start reading the socket and receive any incoming messages
            _client.GetStream().BeginRead(_buffer,
                                            0,
                                            _buffer.Length,
                                            Server_MessageReceived,
                                            null);
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
                        if (str == "LI_SUCCESS\0")
                        {
                            pass = true;
                            this.Hide();
                            menu chatAll = new menu(textBox1.Text, _client);
                            chatAll.ShowDialog();
                            this.Close();
                        }
                        else if (str == "LI_FAILURE\0")
                        {
                            label4.Hide();
                            label6.Hide();
                            label7.Hide();
                            label5.Show();
                        }
                        else if (str == "SU_SUCCESS\0")
                        {
                            label4.Hide();
                            label5.Hide();
                            label6.Hide();
                            label7.Show();
                        }
                        else if (str == "SU_FAILURE\0")
                        {
                            label4.Hide();
                            label5.Hide();
                            label7.Hide();
                            label6.Show();
                        }
                    }));
                }

                if (!pass)
                {
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

        private void login_Load(object sender, EventArgs e)
        {
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                label3.Show();
                return;
            }
            if (textBox2.Text == "")
            {
                label5.Hide();
                label6.Hide();
                label7.Hide();
                label4.Show();
                return;
            }

            var content = "LOGIN|NULL|" + textBox1.Text + "|NULL|" + textBox2.Text;

            var msg = Encoding.ASCII.GetBytes(content);
            _client.GetStream().Write(msg, 0, msg.Length);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                label3.Hide();
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (textBox2.Text != "")
            {
                label4.Hide();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                label3.Show();
                return;
            }
            if (textBox2.Text == "")
            {
                label5.Hide();
                label6.Hide();
                label7.Hide();
                label4.Show();
                return;
            }

            var content = "SIGNUP|NULL|" + textBox1.Text + "|NULL|" + textBox2.Text;

            var msg = Encoding.ASCII.GetBytes(content);
            _client.GetStream().Write(msg, 0, msg.Length);
        }
    }
}
