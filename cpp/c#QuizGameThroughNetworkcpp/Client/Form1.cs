using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CS408_GUI_PROJECT
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        static string myQuestion = "";
        static string myAnswer = "";
        static bool nextQuestion = true;
        static string currentAnswer = "";
        static int nOfPlayers = 0;
        static int nToAnswered = -1;
        static int port;
        static int nameCount = 0;
        static int turn;
        static string ip;
        static string name;
        static string question;
        static string answer;
        const string askQuestion = "askingForQuestion-1";
        const string answerQuestion = "aNsWeRtheQuestiOn-1";
        const string trueQuestion = "theQuEstIoniSTruE-1";
        const string falseQuestion = "theQuEstIoniSfAllSe-1";
        const string sucConnection = "theConnectionisOk---";
        const string dc = "disconnect-1-1-1-1-1-1";
        const string sameQuestion = "myQuestion-1-1-1-1-1-1";
        static bool askQuestionTurn = false;
        static bool answerTurn = false;
        static bool proceedNext = false;
        static bool connected = false;
        static bool disconnect = false;
        static List<Thread> connectingThreads = new List<Thread>();
        static List<string> questions = new List<string>();
        static List<string> answers = new List<string>();


        static Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); // a new socketis created
        private void port_textbox_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void ip_textbox_TextChanged(object sender, EventArgs e)
        {
            ip = ip_textbox.Text; 
        }

        private void name_textbox_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void question_textbox_TextChanged(object sender, EventArgs e)
        {
            question = question_textbox.Text;
        }

        private void answer_textbox_TextChanged(object sender, EventArgs e)
        {
            answer = answer_textbox.Text;
        }

        private void connect_button_Click(object sender, EventArgs e) 
        {
            clientSocket.ReceiveTimeout = 10000000;
            clientSocket.SendTimeout = 10000000;
            ip = ip_textbox.Text;
            port = int.Parse(port_textbox.Text);
            name = name_textbox.Text;
            try
            {
                clientSocket.Connect(ip, port); // our client socket is connecting to the server socket 
                richTextBox1.AppendText("Trying to connect with the name of " + name + "\n");
                Thread tryToConnect = new Thread(tryConnect); 
                tryToConnect.Start();  // tryConnect thread is initialized.

                connectingThreads.Add(tryToConnect); // tryConnect thread is added to Connecting threads here
                System.Threading.Thread.Sleep(1500);
                Thread questionLoops = new Thread(questionLoop);
                questionLoops.Start();
                connectingThreads.Add(questionLoops);

            }
            catch
            {

            }
        }

        private void findWinner(List<string> names, List<int> points)
        {
            //Finds the winner, if there are 2 winner with same points, alphabetically first one is considered as winner
            int max = -1; string winner = "no one";
            for(int i=0; i<names.Count; i++)
            {
                if (points[i] > max)
                {
                    max = points[i];
                    winner = names[i];
                }
            }
            richTextBox1.AppendText("The winner is: " + winner + " with the points of: " + max + "\n");
        }

        private void questionLoop(){ // After connected, It is required  for client to ask a question and answer all incoming questions
            byte[] turnByte = new Byte[1024];
            clientSocket.Receive(turnByte);
            turn = int.Parse(Encoding.Default.GetString(turnByte).Trim('\0'));
            //Taking the number of turns at start, so can output winner easily after the ending
            while (true)
            {
                turn--;
                byte[] buffer = new Byte[1024];
                clientSocket.Receive(buffer);
                string nofpl = Encoding.Default.GetString(buffer).Trim('\0');   //Number of players can change at every round so it is taken in ever round
                nOfPlayers = int.Parse(nofpl);
                richTextBox1.AppendText("The game/round has started. Please send a question then send answer to the coming questions \n");
                askQuestionTurn = true; //Gives permission to send only one question for this loop (every question once for loop)
                questions.Clear();
                answers.Clear();
                for (int i = nOfPlayers; i > 0; i--)
                {
                    if (i != nOfPlayers) clientSocket.ReceiveTimeout = 3000;
                    try
                    {
                        //Taking all the questions from server
                        byte[] buffer2 = new Byte[1024];
                        clientSocket.Receive(buffer2);
                        string qq = Encoding.Default.GetString(buffer2).Trim('\0');
                        questions.Add(qq);
                        byte[] buffer3 = new Byte[1024];
                        clientSocket.Receive(buffer3);
                        string aa = Encoding.Default.GetString(buffer3).Trim('\0');
                        answers.Add(aa);
                    }
                    catch { }
                }
                clientSocket.ReceiveTimeout = 10000000;
                answerTurn = false;
                for (int i = 0; i < questions.Count; i++)
                {
                    //Taking and answering all questions currently now in the clients database
                    nextQuestion = true;
                    string qq = questions[i].Trim('\0');
                    string aa = answers[i].Trim('\0');
                    answerTurn = true;
                    richTextBox1.AppendText("A new question has come: " + qq + "\n");
                    question_textbox.Text = qq;
                    currentAnswer = aa;
                    while (nextQuestion) ;
                }
                //Since players and their points are changable inbetween every round, it is initialized in every loop
                List<string> names = new List<string>();
                List<int> points = new List<int>();

                for (int i = nOfPlayers; i > 0; i--)
                {
                    if (i != nOfPlayers) clientSocket.ReceiveTimeout = 2000;
                    try
                    {
                        //Taking all players and their points
                        byte[] buffer2 = new Byte[1024];
                        clientSocket.Receive(buffer2);
                        string qq = Encoding.Default.GetString(buffer2).Trim('\0');
                        names.Add(qq);
                        byte[] buffer3 = new Byte[1024];
                        clientSocket.Receive(buffer3);
                        string aa = Encoding.Default.GetString(buffer3).Trim('\0');
                        points.Add(int.Parse(aa));
                    }
                    catch { }
                }
                clientSocket.ReceiveTimeout = 10000000;
                richTextBox1.AppendText("Round has ended, the points are: \n");
                for(int i=0; i<names.Count; i++)
                {
                    //Output of every player and its point
                    richTextBox1.AppendText(names[i] + ": " + points[i]+"\n");
                }
                if (turn <= 0)
                {
                    richTextBox1.AppendText("Game is ended\n");
                    findWinner(names, points);
                    System.Threading.Thread.Sleep(1500);
                    richTextBox1.AppendText(name + " is closing the socket and releasing the resources\n");
                    clientSocket.Close();
                    foreach (Thread t in connectingThreads)
                    {
                        t.Abort();
                    }
                    System.Threading.Thread.Sleep(2000);
                    Application.Exit();
                }
            }
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }



        private void button1_Click(object sender, EventArgs e)
        {
            if (askQuestionTurn)
            {
                myQuestion = question_textbox.Text.Trim('\0');
                clientSocket.Send(Encoding.Default.GetBytes(myQuestion));
                myAnswer = answer_textbox.Text.Trim('\0');
                clientSocket.Send(Encoding.Default.GetBytes(myAnswer));
                richTextBox1.AppendText("The question: \"" + myQuestion + "\"" + " and the answer: \"" + myAnswer + "\" has been sent! \n");
                nToAnswered = nOfPlayers;
                askQuestionTurn = false;
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (answerTurn)
            {
                nToAnswered--;
                string aa = answer_textbox.Text.Trim('\0');
                if (aa == currentAnswer)
                {
                    clientSocket.Send(Encoding.Default.GetBytes(trueQuestion));
                }
                else
                {
                    clientSocket.Send(Encoding.Default.GetBytes(falseQuestion));
                }
                richTextBox1.AppendText("The answer is: " + currentAnswer + " and you said: " + aa + "\n");
                if (nToAnswered == 0) answerTurn = false;

                nextQuestion = false;
            }

        }

        private void tryConnect() // this function checks if the name is occured.If yes,new name is required
        {
            while (!connected) {
                nameCount++;
                Byte[] buffer = new Byte[1024];
                clientSocket.Receive(buffer);
                string message = Encoding.Default.GetString(buffer).Trim('\0');
                if (message == sucConnection) {
                    connected = true;
                    richTextBox1.AppendText("Connection is successfull!\n");
                    return;
                }
                else
                {
                    if (nameCount >= 2)
                    {
                        richTextBox1.AppendText("Connection failed, please try another name!\n");
                        System.Threading.Thread.Sleep(1500);
                    }
                    clientSocket.Send(Encoding.Default.GetBytes(name));
                }

                    
                }

        }

        private void button3_Click(object sender, EventArgs e)
        {
            richTextBox1.AppendText(name + " is closing the socket and releasing the resources\n");
            clientSocket.Close();
            foreach(Thread t in connectingThreads)
            {
                t.Abort();
            }
            System.Threading.Thread.Sleep(2000);
            Application.Exit();
        }


        private void dcThread()
        {
            while (disconnect == false) ;

        }
    }

}
