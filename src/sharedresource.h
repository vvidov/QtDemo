#ifndef SHAREDRESOURCE_H
#define SHAREDRESOURCE_H

#include <QMutex>
#include <QString>
#include <QVector>

class SharedResource {
public:
    SharedResource();
    
    // Add data to the shared resource
    void addData(const QString& data);
    
    // Get all data from the shared resource
    QVector<QString> getAllData() const;
    
    // Clear all data
    void clear();
    
    // Get the current size of data
    int size() const;

private:
    mutable QMutex m_mutex;
    QVector<QString> m_data;
};

#endif // SHAREDRESOURCE_H
