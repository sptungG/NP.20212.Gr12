using ChatClient.Login;
using System;
using System.Windows.Forms;

namespace ChatClient
{
    static class Program
    {
        public static string ConfigHost { get; set; } = "127.0.0.1";
        public static int ConfigPort { get; set; } = 54000;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            try
            {
                Application.Run(new login());
            }
            catch(Exception e)
            {
                MessageBox.Show(e.ToString(), "MAIN LOOP");
            }
        }
    }
}
