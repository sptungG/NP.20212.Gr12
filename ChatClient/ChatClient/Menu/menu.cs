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
            Text = "Menu - " + user.Trim();
            button5.Text = "User: " + user.Trim();
            _client = client;
            pass = false;
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            // Connect to the remote server. The IP address and port # could be
            // picked up from a settings file.

            //_client.Connect("127.0.0.1", 54000);

            // Start reading the socket and receive any incoming messages
            if (!pass)
            {
                _client.GetStream().BeginRead(_buffer,
                                            0,
                                            _buffer.Length,
                                            null,
                                            null);

                var msg = Encoding.ASCII.GetBytes("INIT|NULL|" + user);
                _client.GetStream().Write(msg, 0, msg.Length);
            }

        }

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

        private void button2_Click(object sender, EventArgs e)
        {
            pass = true;
            this.Hide();
            privateChat c = new privateChat(user, _client);
            c.ShowDialog();
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            pass = true;
            this.Hide();
            groupChat c = new groupChat(user, _client);
            c.ShowDialog();
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);

            this.Hide();
            login c = new login();
            c.ShowDialog();
            this.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {

        }
        private void menu_FormClosed(object sender, FormClosedEventArgs e)
        {
            var msg = Encoding.ASCII.GetBytes("CLOSE_CONNECTION");
            _client.GetStream().Write(msg, 0, msg.Length);
        }
    }
}
