#include "tcpclient.h"
#include "ui_tcpclient.h"


TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();

    //信号与slots的connect
    //(旧版Qt4写法的垮平台特效更好 嵌入式设备一般都是用QT4)
    // connect(&m_tcpSocket,SIGNAL(connect()),this,SLOT(showConnect()) );
    //新版写法：
    /*
     * &m_tcpSocket：m_tcpSocket 是一个 QTcpSocket 类型的对象，表示你正在连接信号的发出者（也就是发出 connected 信号的对象）。
    &QTcpSocket::connected：这是信号的成员函数指针，表示 QTcpSocket 的 connected 信号。
    this：指的是 TcpClient 类的实例对象，即当前对象。this 作为连接的目标，表示当信号发出时，槽函数 showConnect 应该被调用。
    &TcpClient::showConnect：这是槽函数的成员函数指针，表示当 connected 信号发出时，要调用 TcpClient 类中的 showConnect 函数
     */
    // 检查是否已连接
    if(!m_tcpSocket.isOpen())
    {
        //信号和slots连接
        connect(&m_tcpSocket,&QTcpSocket::connected, this,&TcpClient::showConnect);
        //连接服务器
        m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);

    }

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()//添加loadConfig的定义
{
    QFile file(":/client.config");
    if(file.open(QIODeviceBase::ReadOnly))//成功打开返回true，失败打开返回false
    {
        QByteArray baData = file.readAll();//读出来返回的是QByteArray
        QString strData = QString::fromUtf8(baData);// 将 QByteArray 转换为 QString
        qDebug() << "读出来的QString：" << strData;
        file.close();

        // 将字符串(读出来的QString： "127.0.0.1\n8888\n")进行分割，去除掉\n
        strData.replace("\n"," ");//"127.0.0.1 8888 "
        qDebug() << strData;
        //按照空格进行切分
        //当前方法： 通过替换和分割字符串的方式来提取信息，简单有效，但在处理更复杂格式时会出现一些问题（例如多个空格、换行等）。
        //改进方法： 使用正则表达式可以更加精准地提取 IP 地址和端口号，且具备更好的可扩展性和鲁棒性。
        QStringList strList = strData.split(" ");
        // for (int i = 0; i < strList.size();++i)
        // {
        //     qDebug() << "----" << strList[i];
        // }
        m_strIP = strList.at(0);//用at(0)比直接strList【0】安全
        m_usPort= strList.at(1).toUShort();//toUShort() 会将字符串转换为无符号短整型（quint16）
        qDebug() << "ip:" <<m_strIP << "port:" <<m_usPort;

    }else {
        QMessageBox::critical(this,"open config","open config failed");
    }

}

void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}
