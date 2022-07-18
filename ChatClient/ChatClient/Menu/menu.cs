using ChatClient.Chat;
using ChatClient.Login;
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

namespace ChatClient.Menu
{
    public partial class menu : Form
    {
        string user;
        TcpClient _client;
        byte[] _buffer = new byte[4096];
        bool pass;
        public menu(string user, TcpClient client)
        {
            InitializeComponent();
            this.user = user.Trim();
            _client = client;
            pass = false;
            Text = "Welcome - " + user.Trim();
            username.Text = "User: " + user.Trim();
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            // Connect to the remote server. The IP address and port # could be
            // picked up from a settings file.

            //_client.Connect(Program.ConfigHost, Program.ConfigPort);

            // Start reading the socket and receive any incoming messages
            if (!pass)
            {            
                var msg = Encoding.ASCII.GetBytes("INIT|NULL|" + user);
                _client.GetStream().Write(msg, 0, msg.Length);
            }
            
        }
        // chatAll
        private void button1_Click(object sender, EventArgs e)
        {
            pass = true;
            this.Hide();
            chatAll chatAll = new chatAll(user, _client);
            chatAll.ShowDialog();
            this.Close();
        }

        private void menu_Load(object sender, EventArgs e)
        {
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
        }
        // privateChat
        private void button2_Click(object sender, EventArgs e)
        {
            pass = true;
            this.Hide();
            privateChat c = new privateChat(user, _client);
            c.ShowDialog();
            this.Close();
        }
        // Gr chat
        private void button3_Click(object sender, EventArgs e)
        {
            pass = true;
            this.Hide();
            groupChat c = new groupChat(user, _client);
            c.ShowDialog();
            this.Close();
        }
        // Logout
        private void button4_Click(object sender, EventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);

            this.Hide();
            login c = new login();
            c.ShowDialog();
            this.Close();
        }
        // Close Window
        private void menu_FormClosed(object sender, FormClosedEventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);
        }
    }
}
