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

namespace ChatClient.Menu
{
    public partial class menu : Form
    {
        string user;
        public menu(string user)
        {
            InitializeComponent();
            this.user = user.Trim();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            chatAll chatAll = new chatAll(user);
            chatAll.ShowDialog();
            this.Close();
        }

        private void menu_Load(object sender, EventArgs e)
        {
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            privateChat c = new privateChat(user);
            c.ShowDialog();
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Hide();
            groupChat c = new groupChat(user);
            c.ShowDialog();
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.Hide();
            login c = new login();
            c.ShowDialog();
            this.Close();
        }
    }
}
