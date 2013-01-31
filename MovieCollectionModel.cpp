#include "MovieCollectionModel.h"
#include <unistd.h>

#include <QDebug>

MovieCollectionModel::MovieCollectionModel(QString directory, QObject* parent)
    : QSortFilterProxyModel(parent)
{
    this->fsModel = new QFileSystemModel(parent);
    this->fsModel->setRootPath(directory);

    this->setSourceModel(fsModel);
    this->setDynamicSortFilter(true);

    this->fsModelRootIndex = QPersistentModelIndex(this->mapFromSource(this->fsModel->index(directory)));
}

QPersistentModelIndex MovieCollectionModel::getRootIndex() const
{
    return this->fsModelRootIndex;
}

bool MovieCollectionModel::isDir(const QModelIndex& index) const
{
    QModelIndex fsModelIndex = this->mapToSource(index);
    return this->fsModel->isDir(fsModelIndex) && this->hasVideoFiles(fsModelIndex) != 1;
}

QString MovieCollectionModel::fileName(const QModelIndex& index) const
{
    return this->fsModel->fileName(this->mapToSource(index));
}

QString MovieCollectionModel::filePath(const QModelIndex& index) const
{
    QModelIndex fsModelIndex = this->mapToSource(index);
    if (this->fsModel->isDir(fsModelIndex) && this->hasVideoFiles(fsModelIndex) == 1)
    {
        return this->fsModel->filePath(this->getFirstVideoFile(fsModelIndex));
    }

    return this->fsModel->filePath(fsModelIndex);
}

bool MovieCollectionModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex fsModelIndex = this->fsModel->index(sourceRow, 0, sourceParent);
    if (this->fsModel->filePath(fsModelIndex) == this->fsModel->rootPath())
    {
        return true;
    }
    else if (!this->fsModel->filePath(fsModelIndex).contains(this->fsModel->rootPath()))
    {
        return false;
    }
    else if (this->fsModel->isDir(fsModelIndex))
    {
        if (this->hasVideoFiles(fsModelIndex))
        {
            return true;
        }
    }
    else
    {
        if (this->isVideoFile(fsModelIndex))
        {
            return true;
        }
    }

    return false;
}

bool MovieCollectionModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    qDebug() << "lessThan";
    return false;
    // return QString::localeAwareCompare(this->fsModel->fileName(left), this->fsModel->fileName(right)) < 0;
}

bool MovieCollectionModel::isVideoFile(const QModelIndex& fsModelIndex) const
{
    QString cmp = this->fsModel->fileName(fsModelIndex).toLower();
    return cmp.endsWith(".avi") || cmp.endsWith(".mkv") || cmp.endsWith(".mp4");
}

int MovieCollectionModel::hasVideoFiles(const QModelIndex& fsModelIndex) const
{
    int count = 0;
    this->fsModel->fetchMore(fsModelIndex);
    for (int i = 0; i < this->fsModel->rowCount(fsModelIndex); i++)
    {
        QModelIndex fsModelChildIndex = this->fsModel->index(i, 0, fsModelIndex);
        if (this->fsModel->isDir(fsModelChildIndex))
        {
            count += this->hasVideoFiles(fsModelChildIndex);
        }
        else
        {
            if (this->isVideoFile(fsModelChildIndex))
            {
                count += 1;
            }
        }
    }
    return count;
}

QModelIndex MovieCollectionModel::getFirstVideoFile(const QModelIndex& fsModelIndex) const
{
    this->fsModel->fetchMore(fsModelIndex);
    for (int i = 0; i < this->fsModel->rowCount(fsModelIndex); i++)
    {
        QModelIndex fsModelChildIndex = this->fsModel->index(i, 0, fsModelIndex);
        if (this->fsModel->isDir(fsModelChildIndex))
        {
            QModelIndex fsModelFirstVideoFileIndex = this->getFirstVideoFile(fsModelChildIndex);
            if (fsModelFirstVideoFileIndex.isValid())
            {
                return fsModelFirstVideoFileIndex;
            }
        }
        else
        {
            if (this->isVideoFile(fsModelChildIndex))
            {
                return fsModelChildIndex;
            }
        }
    }

    return QModelIndex();
}
