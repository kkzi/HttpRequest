

#include <HttpRequest/HttpRequest.h>
#include <QtCore/qcoreapplication.h>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QtConcurrent::run([]
        {
            for (int i = 0; i < 20; ++i)
            {

                qDebug() << "thread";
                QThread::sleep(1);
            }
        }
    );
    auto reply = http::syncRequest<http::Get>("http://qq.com");
    qDebug() << reply;

    QThread::sleep(1);

    reply = http::syncRequest<http::Get>("http://qq.com/index.html");
    qDebug() << reply;

    http::asyncRequest<http::Get>("http://localhost:8888");

    qDebug() << "ok";


}