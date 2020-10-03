#include "HttpRequest/HttpRequest.h"
#include <QtCore/qcoreapplication.h>

namespace http
{
    static QByteArray verb2str(Verb v)
    {
        static QMap<Verb, QByteArray> verbs{
            { Verb::Get, "GET" },
            { Verb::Post, "POST" },
            { Verb::Delete, "DELETE" },
            { Verb::Put, "PUT" },
        };
        return verbs.value(v, "");
    }

    static QNetworkRequest makeRequest(const QByteArray& url, const Header& head)
    {
        QNetworkRequest req;
        req.setUrl(QUrl(url));
        for (const auto& key : head.keys())
        {
            req.setRawHeader(key, head.value(key));
        }
        return req;
    }

    QNetworkReply* asyncRequest(const QByteArray& verb, const QNetworkRequest& req, const QByteArray& body, int ms)
    {
        static QNetworkAccessManager* nam = new QNetworkAccessManager(qApp);
        //static QNetworkAccessManager nam(qApp);

        QNetworkRequest r(req);
        if (ms > 0)
        {
            r.setTransferTimeout(ms);
        }
        return nam->sendCustomRequest(r, verb, body);
    }

    QNetworkReply* asyncRequest(const Verb& verb, const QNetworkRequest& req, const QByteArray& body, int ms)
    {
        const QByteArray& method = verb2str(verb);
        if (method.isEmpty())
        {
            return nullptr;
        }
        return asyncRequest(method, req, body, ms);
    }

    QNetworkReply* asyncRequest(const Verb& verb, const QByteArray& url, const Header& head, const QByteArray& body, int ms)
    {
        return asyncRequest(verb, makeRequest(url, head), body, ms);
    }

    QNetworkReply* syncRequest(const QByteArray& verb, const QNetworkRequest& req, const QByteArray& body, int ms)
    {
        QNetworkReply* reply = asyncRequest(verb, req, body, ms);
        if (reply != nullptr)
        {
            //QEventLoop loop;
            //QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            //loop.exec();
            while (!reply->isFinished())
            {
                QCoreApplication::processEvents();
            }
        }
        return reply;
    }

    QNetworkReply* syncRequest(const Verb& verb, const QNetworkRequest& req, const QByteArray& body, int ms)
    {
        const QByteArray& method = verb2str(verb);
        if (method.isEmpty())
        {
            return nullptr;
        }
        return syncRequest(method, req, body, ms);
    }

    QByteArray syncRequest(const Verb& verb, const QByteArray& url, const Header& head, const QByteArray& body, int ms)
    {
        QNetworkRequest req = makeRequest(url, head);
        QByteArray rep;
        QNetworkReply* reply = syncRequest(verb, req, body, ms);
        if (reply != nullptr)
        {
            rep = reply->readAll();
            reply->deleteLater();
        }
        return rep;
    }
}