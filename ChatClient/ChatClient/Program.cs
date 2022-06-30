using ChatClient.Login;
using System;
using System.Windows.Forms;

namespace ChatClient
{
    static class Program
    {
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
