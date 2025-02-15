#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpClient;
}
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void loadConfig();//loadConfig()的声明
public slots://信号处理函数
    void showConnect();

private:
    Ui::TcpClient *ui;
    QString m_strIP;//将文件读取出来的数据添加到全局变量m_strIP中去(Ip地址)
    quint16 m_usPort;//端口号

    //连接服务器，和服务器数据交互
    QTcpSocket m_tcpSocket;
};
#endif // TCPCLIENT_H
