#pragma once

#include "MessageReader.h"
#include "ObjectIdMap.h"

#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtCore/QTextStream>

class QLocalServer;
class QLocalSocket;

namespace service
{
	class InspectorRequest;
	class InspectorResponse;
	class QtObject;
};

class InspectorServer : public QObject
{
	Q_OBJECT

	public:
		InspectorServer(QTextStream* log, QObject* parent);

		static QString socketName(int pid);

	private Q_SLOTS:
		void handleConnection();
		void readyRead();

	private:
		void readFromSocket(QLocalSocket* socket);
		void handleRequest(const service::InspectorRequest& request,
                           service::InspectorResponse* response);
		void updateObjectMessage(QObject* object, service::QtObject* message);

		QTextStream* m_log;
		QLocalServer* m_server;
		MessageReader m_messageReader;
		ObjectIdMap m_objectMap;
};

