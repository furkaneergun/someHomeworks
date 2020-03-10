using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CS408_PROJECT_SERVER{
    public partial class Form1 : Form{

        public Form1(){
            InitializeComponent();
        }
        static bool canConnect = true;
        static int nofRounds;
        static int port;
        static int turn;
        static string ip;
        static Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        static int count = 0, connectedCount = 0;
        static List<Socket> nameSockets = new List<Socket>();
        static List<Thread> threadSockets = new List<Thread>();
        static bool accept = true, terminating = false;
        static List<int> points = new List<int>();
        static List<string> Names = new List<string>();
        const string askingForName = "ASKING_FOR_NAME_123456789";
        const string dcClient = "---------11111----";
        const string askQuestion = "askingForQuestion-1";
        const string answerQuestion = "aNsWeRtheQuestiOn-1";
        const string trueQuestion = "theQuEstIoniSTruE-1";
        const string falseQuestion = "theQuEstIoniSfAllSe-1";
        const string sucConnection = "theConnectionisOk---";
        const string dc = "disconnect-1-1-1-1-1-1";
        const string sameQuestion = "myQuestion-1-1-1-1-1-1";

        private void ip_textbox_TextChanged(object sender, EventArgs e){

        }

        private void port_textbox_TextChanged(object sender, EventArgs e){
        }


        private void button1_Click(object sender, EventArgs e){
            serverSocket.ReceiveTimeout = 10000000;
            serverSocket.SendTimeout = 10000000;
            port = int.Parse(port_textbox.Text);

            try
            {
                

                IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), port);
                serverSocket.Bind(endPoint);
                serverSocket.Listen(100);
                richTextBox.AppendText("Server has started with IP: "+ "127.0.0.1" + " and the port: " + port+"\n");
                Thread acceptThread = new Thread(Accept);
                acceptThread.Start();
                threadSockets.Add(acceptThread);




            }
            catch
            {
                Console.WriteLine("ERROR1 There is a problem! Check the port number and try again!");
            }
        }

        private void Accept(){ // This function accepts the threads
            while (canConnect)
            {
                while (accept)
                {
                    try
                    {
                        Socket newClient = serverSocket.Accept();
                        nameSockets.Add(newClient);
                        bool isExist = true;
                        int clientNumber = count;
                        count++;//if the client number becomes 2, the question and answer commands are sent
                        string currentName = "";
                        while (isExist)
                        {
                            currentName = askForName(clientNumber);
                            if (currentName == dcClient)
                            {
                                count--;//If client disconnects the count is decreased
                                newClient.Close();
                                return;
                            }
                            bool isOk = false;
                            for (int i = 0; i < Names.Count(); i++)
                            {
                                if (Names[i] == currentName)
                                {
                                    isOk = true;//If name exist beforehand
                                }
                            }
                            isExist = false;
                            if (isOk)
                            {
                                isExist = true;
                                richTextBox.AppendText("Please choose another name, that one is already taken\n");
                                System.Threading.Thread.Sleep(5000);
                            }
                        }
                        newClient.Send(Encoding.Default.GetBytes(sucConnection));
                        connectedCount++;
                        Names.Add(currentName);
                        richTextBox.AppendText(currentName + " connected successfully!\n");


                    }
                    catch
                    {
                        if (terminating)
                        {
                            richTextBox.AppendText("Server stopped working...");
                            accept = false;
                        }
                        else
                        {
                            richTextBox.AppendText("Problem occured while accepting the client?!");
                        }
                    }
                }
            }
            
        }

        private void richTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                richTextBox.AppendText("Server is closing \n");
                foreach(Socket s in nameSockets)
                {
                    s.Close();
                }
                foreach (Thread t in threadSockets)
                {
                    t.Abort();
                }

                System.Threading.Thread.Sleep(1000);
                Application.Exit();
            }
            catch
            {
                richTextBox.AppendText("Server is closing \n");
                System.Threading.Thread.Sleep(3000);
                Application.Exit();

            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (connectedCount >= 2) {
                canConnect = false;
                nofRounds = int.Parse(textBox1.Text);
                turn = 0;
                Thread questionThread = new Thread(sendQuestions);
                questionThread.Start();
                threadSockets.Add(questionThread);
                for(int i=0; i<connectedCount; i++)
                {
                    points.Add(0);
                }

                Thread checkingSockets = new Thread(checkSockets);
                checkingSockets.Start();
                threadSockets.Add(checkingSockets);
            }
            else
            {
                richTextBox.AppendText("Can not start the game as at least 2 connected player is required \n");
            }
        }

        private string askForName(int whichClient){
            int reportCount = 0;
            while (true) {//try while name is not correct;
                try{
                    string message = askingForName;
                    Socket thisClient = nameSockets[whichClient];
                    thisClient.Send(Encoding.Default.GetBytes(message));
                    byte[] buffer = new Byte[1024];
                    thisClient.Receive(buffer);
                    string currentName = Encoding.Default.GetString(buffer).Replace("\0", String.Empty);
                    message = String.Concat(currentName, " is trying to connect\n");
                    richTextBox.AppendText(message);
                    return currentName;
                }
                catch{
                    richTextBox.AppendText("An error occured while client number " + whichClient + " is trying to send its name\n");
                    reportCount++;
                    if (reportCount == 2) {
                        richTextBox.AppendText("The client with number " + whichClient + " probably disconnected, sorry!\n");
                        return dcClient;
                    }
                }
            }
        }

        private void sendQuestions() // This function chooses the client to ask the question, also chooses the client to asnwer it. After this, server sends
        {                              // the question to question client and does the same to answer
            for(int i=0; i<connectedCount; i++)
            {
                Socket s = nameSockets[i];
                string turnCount = nofRounds.ToString();
                s.Send(Encoding.Default.GetBytes(turnCount));
            }
            for(;nofRounds>0;nofRounds--)
            {
                if (connectedCount > 1)
                {
                    richTextBox.AppendText("A round has started \nNumber of rounds left is: " + nofRounds + "\n");
                    for(int i=0; i<connectedCount; i++)
                    {
                        Socket s = nameSockets[i];
                        string count = connectedCount.ToString();
                        s.Send(Encoding.Default.GetBytes(count));
                    }
                    List<string> questions = new List<string>();
                    List<string> answers = new List<string>();
                    for(int i=0; i<connectedCount; i++)
                    {
                        try
                        {
                            Socket s = nameSockets[i];
                            byte[] buffer = new Byte[1024];
                            s.Receive(buffer);
                            string Question = Encoding.Default.GetString(buffer).Trim('\0');
                            questions.Add(Question);

                            byte[] buffer2 = new Byte[1024];
                            s.Receive(buffer2);
                            string answer = Encoding.Default.GetString(buffer2).Trim('\0');
                            answers.Add(answer);

                            richTextBox.AppendText(Names[i] + " asked the following question: " + Question + " and the answer is: " + answer + "\n");
                        }
                        catch
                        {
                            richTextBox.AppendText("An error occured while taking the answer, a client may be disconnected \n");
                        }
                    }

                    for(int i=0; i<connectedCount; i++)
                    {
                        Socket s = nameSockets[i];
                        for(int j=0; j<questions.Count(); j++)
                        {
                            s.Send(Encoding.Default.GetBytes(questions[j]));
                            System.Threading.Thread.Sleep(500);
                            s.Send(Encoding.Default.GetBytes(answers[j]));
                        }
                    }

                    for(int i=0; i<questions.Count; i++)
                    {

                        for (int j=0; j<connectedCount; j++)
                        {
                            Socket s = nameSockets[j];
                            byte[] buffer = new Byte[1024];
                            s.Receive(buffer);
                            string result = Encoding.Default.GetString(buffer).Trim('\0');
                            if (result == trueQuestion)
                            {
                                richTextBox.AppendText(Names[j] + " has answered correctly. So +1 points\n");
                                int oldPoint = points[j];
                                oldPoint++;
                                points[j] = oldPoint;
                            }
                            else
                            {
                                richTextBox.AppendText(Names[j] + " has answered incorrectly. So no points\n");
                            }
                        }
                    }
                    


                    for(int i=0; i<connectedCount; i++)
                    {
                        richTextBox.AppendText(Names[i] + " has " + points[i] + " points. \n");
                    }
                    for(int i=0; i<connectedCount; i++)
                    {
                        for(int j=0; j<Names.Count; j++)
                        {
                            Socket s = nameSockets[i];
                            s.Send(Encoding.Default.GetBytes(Names[j]));
                            System.Threading.Thread.Sleep(500);
                            s.Send(Encoding.Default.GetBytes(points[j].ToString()));

                        }
                    }


                    
                }


                else
                {
                    richTextBox.AppendText("Game has ended as no player more than one left\n");
                    richTextBox.AppendText("Winner is: " + Names.ElementAt(0));
                    System.Threading.Thread.Sleep(10000);
                    Application.Exit();

                }
            }

            richTextBox.AppendText("Maximum number of rounds reached and game ended \n");
            findWinner();
            richTextBox.AppendText("Server is closing \n");
            foreach (Socket s in nameSockets)
            {
                s.Close();
            }
            foreach (Thread t in threadSockets)
            {
                t.Abort();
            }

            System.Threading.Thread.Sleep(1000);
            Application.Exit();

        }

        private void findWinner()
        {
            string winner = "No one";
            int max = -1;
            for(int i=0; i<connectedCount; i++)
            {
                richTextBox.AppendText(Names[i] + ": " + points[i] + "\n");
                if (points[i] > max)
                {
                    max = points[i];
                    winner = Names[i];
                }
            }
            richTextBox.AppendText("And the winner is: " + winner + " with the number of points: " + max + "\n");
        }
        private void checkSockets()
        {
            while (true)
            {
                for (int i = 0; i < connectedCount; i++)
                {
                    Socket s = nameSockets[i];
                    if (!s.Connected)
                    {
                        Names.RemoveAt(i);
                        points.RemoveAt(i);
                        connectedCount--;
                        s.Dispose();
                        s.Disconnect(false);
                        nameSockets.RemoveAt(i);

                    }
                }
                if (connectedCount == 1)
                {
                    richTextBox.AppendText("Game has ended as no player more than one left\n");
                    richTextBox.AppendText("Winner is: " + Names.ElementAt(0));
                    System.Threading.Thread.Sleep(2000);
                    Application.Exit();
                }
            }
        }
    }
}


