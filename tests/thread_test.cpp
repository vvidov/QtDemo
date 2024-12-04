#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include "sharedresource.h"
#include "threadworker.h"

class ThreadTest : public ::testing::Test {
protected:
    void SetUp() override {
        int argc = 0;
        char** argv = nullptr;
        app = new QCoreApplication(argc, argv);
        resource = new SharedResource();
    }

    void TearDown() override {
        delete resource;
        delete app;
    }

    void waitForWorkers(const QVector<ThreadWorker*>& workers, int timeoutMs = 5000) {
        QEventLoop loop;
        QTimer timer;
        timer.setSingleShot(true);
        
        int completedWorkers = 0;
        for (auto worker : workers) {
            QObject::connect(worker, &ThreadWorker::workFinished, [&]() {
                completedWorkers++;
                if (completedWorkers == workers.size()) {
                    loop.quit();
                }
            });
        }
        
        QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(timeoutMs);
        loop.exec();
    }

    QCoreApplication* app;
    SharedResource* resource;
};

TEST_F(ThreadTest, MultipleThreadsAccess) {
    const int itemCount = 100;
    const int threadCount = 3;
    QVector<ThreadWorker*> workers;

    // Create multiple workers
    for (int i = 0; i < threadCount; ++i) {
        auto worker = new ThreadWorker(resource, QString("Thread%1").arg(i));
        workers.append(worker);
    }

    // Start all workers
    for (auto worker : workers) {
        worker->startWork(itemCount);
    }

    // Wait for all workers to finish
    waitForWorkers(workers);

    // Verify results
    QVector<QString> allData = resource->getAllData();
    
    // Check that we have the expected number of items
    EXPECT_EQ(allData.size(), itemCount * threadCount);

    // Check that we have items from all threads
    QSet<QString> prefixes;
    for (const QString& item : allData) {
        prefixes.insert(item.split('_').first());
    }
    EXPECT_EQ(prefixes.size(), threadCount);

    // Cleanup
    for (auto worker : workers) {
        worker->stopWork();
        delete worker;
    }
}

TEST_F(ThreadTest, ConcurrentAddAndClear) {
    const int itemCount = 50;
    ThreadWorker worker1(resource, "Writer");
    
    // Start adding items
    worker1.startWork(itemCount);
    
    // While items are being added, clear the resource multiple times
    for (int i = 0; i < 5; ++i) {
        QThread::msleep(100);
        resource->clear();
    }
    
    // Wait for worker to finish
    QThread::sleep(1);
    
    // Final size should be less than or equal to itemCount
    EXPECT_LE(resource->size(), itemCount);
    
    worker1.stopWork();
}
