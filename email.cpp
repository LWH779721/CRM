#include "email.h"

email::email()
{

}

void communication(QTcpSocket & socket, const char *msg)
{
    char data[1024];
    try
    {
        if (socket.write(msg, qstrlen(msg)) == -1)
            qDebug() << "@@@@@@@@@@@@@@ socket.write failed";
        socket.flush();

        if (socket.waitForReadyRead(-1) == true)
        {
            memset(data, '\0', sizeof(data));
            socket.readLine(data, 1024);
            qDebug() << data;
        }
    }
    catch (...)
    {
        qDebug() << "Exception socket.write failed";
    }
}

void smtpCommunication(QTcpSocket & socket, QString &passwd, QString &to)
{
    QString str;
    communication(socket, "HELO smtp.163.com\r\n");
    communication(socket, "AUTH LOGIN\r\n");
    communication(socket, QByteArray("18720059263@163.com").toBase64()+"\r\n");
    communication(socket, QByteArray("qazw960023815").toBase64()+"\r\n");
    communication(socket, "MAIL FROM: <18720059263@163.com>\r\n");
    str = QStringLiteral("RCPT TO: <");
    str += to;
    str += QStringLiteral(">\r\n");
    communication(socket, str.toUtf8().data());
    communication(socket, "DATA\r\n");
    str.clear();
    str = QStringLiteral("From: 18720059263@163.com\r\nTo: ");
    str += to;
    str += QStringLiteral("\r\nSubject:获取密码\r\n\r\n尊敬的用户，您好\r\n\r\n    您的密码是");
    str += passwd;
    str += QStringLiteral("，请劳记！\r\n\r\n\r\n.\r\n");
    QByteArray ba = str.toUtf8();
    char *mailmessage = ba.data();
    communication(socket,mailmessage);
    communication(socket, "quit\r\n");

    qDebug() << "send email ok." << endl;
}

void readWelcome(QTcpSocket & socket)
{
    char data[1024];
    int len;
    try
    {
        if (socket.waitForReadyRead(-1) == true)
        {
            memset(data, '\0', sizeof(data));
            len = socket.readLine(data, 1024);
            qDebug() <<"Exception readWelcome "<<data << endl;
        }
    }
    catch(...)
    {
        qDebug() <<"readWelcome "<< endl;
    }

}

long email::send(QString &passwd, QString &to)
{
    QTcpSocket socket;
    socket.connectToHost("smtp.163.com", 25);

    if (socket.waitForConnected(2000))
    {
        qDebug() << "smtp server connected success.";
        readWelcome(socket);
        smtpCommunication(socket, passwd, to);
        socket.close();
    }
    else
        qDebug() << "connection failed.";
}
