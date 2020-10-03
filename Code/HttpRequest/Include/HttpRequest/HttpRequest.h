#pragma once

#include <QtCore/qglobal.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>


# if defined(HTTPREQUEST_LIB)
#  define HTTPREQUEST_EXPORT Q_DECL_EXPORT
# else
#  define HTTPREQUEST_EXPORT Q_DECL_IMPORT
# endif


namespace http
{
    enum Verb
    {
        Get = QNetworkAccessManager::Operation::GetOperation,
        Post = QNetworkAccessManager::Operation::PostOperation,
        Delete = QNetworkAccessManager::Operation::DeleteOperation,
        Put = QNetworkAccessManager::Operation::DeleteOperation,
    };
    using Header = QMap<QByteArray, QByteArray>;

    HTTPREQUEST_EXPORT QNetworkReply* asyncRequest(const Verb& verb, const QByteArray& url, const Header& head, const QByteArray& body, int ms = -1);
    HTTPREQUEST_EXPORT QNetworkReply* asyncRequest(const Verb& verb, const QNetworkRequest& req, const QByteArray& body, int ms = -1);
    HTTPREQUEST_EXPORT QNetworkReply* asyncRequest(const QByteArray& verb, const QNetworkRequest& req, const QByteArray& body, int ms = -1);
    HTTPREQUEST_EXPORT QByteArray     syncRequest(const Verb& verb, const QByteArray& url, const Header& head, const QByteArray& body, int ms = -1);
    HTTPREQUEST_EXPORT QNetworkReply* syncRequest(const Verb& verb, const QNetworkRequest& req, const QByteArray& body, int ms = -1);
    HTTPREQUEST_EXPORT QNetworkReply* syncRequest(const QByteArray& verb, const QNetworkRequest& req, const QByteArray& body, int ms = -1);

    template<Verb v>
    QNetworkReply* asyncRequest(const QByteArray& url, int ms = -1)
    {
        return asyncRequest<v>(url, Header(), ms);
    }

    template<Verb v>
    QNetworkReply* asyncRequest(const QByteArray& url, const Header& head, int ms = -1)
    {
        return asyncRequest<v>(url, head, QByteArray(), ms);
    }

    template<Verb v>
    QNetworkReply* asyncRequest(const QByteArray& url, const QByteArray& body, int ms = -1)
    {
        return asyncRequest<v>(url, Header(), body, ms);
    }

    template<Verb v>
    QNetworkReply* asyncRequest(const QByteArray& url, const Header& head, const QByteArray& body, int ms = -1)
    {
        return asyncRequest(v, url, head, body, ms);
    }

    template<Verb v>
    QByteArray syncRequest(const QByteArray& url, int ms = -1)
    {
        return syncRequest<v>(url, Header(), ms);
    }

    template<Verb v>
    QByteArray syncRequest(const QByteArray& url, const Header& head, int ms = -1)
    {
        return syncRequest<v>(url, head, QByteArray(), ms);
    }

    template<Verb v>
    QByteArray syncRequest(const QByteArray& url, const QByteArray& body, int ms = -1)
    {
        return syncRequest<v>(url, Header(), body, ms);
    }

    template<Verb v>
    QByteArray syncRequest(const QByteArray& url, const Header& head, const QByteArray& body, int ms = -1)
    {
        return syncRequest(v, url, head, body, ms);
    }
}
