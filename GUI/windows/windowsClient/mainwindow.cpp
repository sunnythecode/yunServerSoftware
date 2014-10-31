

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->timer1 = new QTimer(this);
    //initialize player stack
    this->playerStack.isConnected=false;
    this->playerStack.nextPlayer =NULL;
    ui->setupUi(this);

   // QTimer *timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()),this, SLOT(updateValGraph()));
   // timer->start(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::updateValGraph()
{
        char data[255];
        XINPUT_STATE player1;
        int port =0;
        while(!XInputGetState(port++,&player1) && port<15);
        if(port<15)
            sprintf(data, "LY:%6d RY:%6d bttn1:%6d", player1.Gamepad.sThumbLY, player1.Gamepad.sThumbRY, player1.Gamepad.wButtons);
        else
            sprintf(data, "CNF");
}
*/

void MainWindow::scanNet()
{
        WSADATA wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL,
                        *ptr = NULL,
                        hints;
        char name[255],*ip;
        IN_ADDR subNet;
        PHOSTENT hostinfo;
        int iResult;

        //startup and get local IP
        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
        }
        else
        {
            if( gethostname ( name, sizeof(name)) == 0)
            {
                if((hostinfo = gethostbyname(name)) != NULL)
                {
                   int nCount = 0;
                   while(hostinfo->h_addr_list[nCount])
                   {
                        ip = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]);;
                        nCount++;
                        ui->clientList->addItem(ip);        //CHANGE TO PRIVATE VAR INSTEAD OF UI ELEMENT!
                   }
                }
            }
        }

        ZeroMemory( &hints, sizeof(hints) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if((this->ipPos)++<=255)
        {
            ui->scanProg->setValue(this->ipPos);
            subNet.S_un.S_addr = inet_addr(ip); //convert to data struct
            subNet.S_un.S_un_b.s_b4=this->ipPos; //change last bit of ip

            iResult = getaddrinfo(inet_ntoa(subNet), DEFAULT_PORT, &hints, &result);
            if ( iResult == 0 )
            {
                // Create a SOCKET for connecting to server
                ConnectSocket = socket(result->ai_family, result->ai_socktype,
                    result->ai_protocol);
                if (ConnectSocket == INVALID_SOCKET) {
                    printf("socket failed with error: %d\n", WSAGetLastError());
                    WSACleanup();
                }

                // Connect to server.
                iResult = ::connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                }
                else
                {
                    ui->clientList->addItem(inet_ntoa(subNet));
                }
                closesocket(ConnectSocket); //reset socket for next iteration
                ConnectSocket = INVALID_SOCKET;
            }

            freeaddrinfo(result);

            if (ConnectSocket == INVALID_SOCKET) {
                printf("Unable to connect to server!\n");
                WSACleanup();
            }
        }
        else
        {
            this->timer1->stop();
        }
    }

    void MainWindow::pushPlayerStack(struct player *stack)
    {
        while(stack->nextPlayer) stack = stack->nextPlayer;
        stack->nextPlayer =(struct player *) malloc(sizeof(struct player));
        stack->nextPlayer->isConnected =false;
        stack->nextPlayer->nextPlayer = NULL;
    }

    void MainWindow::popPlayerStack(struct player *stack)
    {
        struct player *mover = stack;
        if(stack->nextPlayer)
        {
            while(mover->nextPlayer)
            {
                stack = mover;
                mover = mover->nextPlayer;
            }
            stack->nextPlayer = NULL;
            free(mover);
        }
    }

    void MainWindow::deletePlayer(struct player *stack, struct player *del)
    {
       while(stack != del && stack->nextPlayer)
           stack = stack->nextPlayer;
       if(stack->nextPlayer == del)
       {
           stack->nextPlayer = del->nextPlayer;
           free(del);
       }
}

void MainWindow::on_clientList_itemClicked(QListWidgetItem *item)
{
    ui->ipBox->setText(item->text());
}

void MainWindow::on_Scan4robot_clicked()
{
     this->ipPos=0;
     connect(this->timer1, SIGNAL(timeout()),this, SLOT(scanNet()));
     this->timer1->start();
}

void MainWindow::deletePlayer(struct player *stack, int playerNum)
{
    struct player *mover = stack;
    while(mover->playerNum != playerNum && mover->nextPlayer)
    {
        stack = mover;
        mover = mover->nextPlayer;
    }
    if(mover->playerNum == playerNum)
    {
        stack->nextPlayer = mover->nextPlayer;
        free(mover);
    }
}


void MainWindow::on_connect2robot_clicked()
{
    ui->clientList->addItem(ui->ipBox->text());
}
