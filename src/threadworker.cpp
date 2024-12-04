#include "threadworker.h"
#include <QRandomGenerator>

ThreadWorker::ThreadWorker(SharedResource* resource, const QString& prefix, QObject* parent)
    : QObject(parent)
    , m_resource(resource)
    , m_prefix(prefix)
    , m_running(false)
    , m_itemCount(0)
{
    // Move to thread before starting
    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started, this, &ThreadWorker::doWork);
}

ThreadWorker::~ThreadWorker() {
    stopWork();
    m_thread.quit();
    m_thread.wait();
}

void ThreadWorker::startWork(int itemCount) {
    m_itemCount = itemCount;
    m_running = true;
    if (!m_thread.isRunning()) {
        m_thread.start();
    }
}

void ThreadWorker::stopWork() {
    m_running = false;
}

void ThreadWorker::doWork() {
    for (int i = 0; i < m_itemCount && m_running; ++i) {
        // Simulate some work with shorter delay
        int delay = QRandomGenerator::global()->bounded(50);
        QThread::msleep(delay);
        
        // Add data to shared resource
        QString data = QString("%1_%2").arg(m_prefix).arg(i);
        m_resource->addData(data);
    }
    
    emit workFinished();
    // Don't quit the thread here, let the destructor handle it
}
