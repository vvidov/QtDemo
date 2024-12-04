#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include <QThread>
#include "sharedresource.h"

class ThreadWorker : public QObject {
    Q_OBJECT

public:
    explicit ThreadWorker(SharedResource* resource, const QString& prefix, QObject* parent = nullptr);
    ~ThreadWorker();

    void startWork(int itemCount);
    void stopWork();

signals:
    void workFinished();

private slots:
    void doWork();

private:
    SharedResource* m_resource;
    QString m_prefix;
    QThread m_thread;
    bool m_running;
    int m_itemCount;
};

#endif // THREADWORKER_H
