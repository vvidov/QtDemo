#include "sharedresource.h"
#include <QMutexLocker>

SharedResource::SharedResource() = default;

void SharedResource::addData(const QString& data) {
    QMutexLocker locker(&m_mutex);
    m_data.append(data);
}

QVector<QString> SharedResource::getAllData() const {
    QMutexLocker locker(&m_mutex);
    return m_data;
}

void SharedResource::clear() {
    QMutexLocker locker(&m_mutex);
    m_data.clear();
}

int SharedResource::size() const {
    QMutexLocker locker(&m_mutex);
    return m_data.size();
}
