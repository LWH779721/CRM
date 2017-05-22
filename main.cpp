#include "login.h"
#include <QApplication>
//#include <QSplashScreen>
//#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dboperate *db;
    int ret;
#if 1
    db = dboperate::instance();
    login w;
    w.show();
#else
    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/images/girl.bmp"));
    splash->show();

    a.processEvents();      //这句话必须加上，不加的话，无法实现效果。

    QTest::qSleep(3000);
    splash->showMessage(QObject::tr("Loading modules..."),Qt::AlignCenter,Qt::blue);
    QTest::qSleep(6000);

    login w;
    w.show();
    splash->finish(&w);
    delete splash;
#endif
    ret = a.exec();
    delete db;
    return ret;
}
