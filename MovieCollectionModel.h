#ifndef MOVIECOLLECTIONMODEL_H
#define MOVIECOLLECTIONMODEL_H

#include <QFileSystemModel>
#include <QSortFilterProxyModel>

class MovieCollectionModel : public QSortFilterProxyModel
{
    public:
        MovieCollectionModel(QString directory, QObject* parent = 0);

        QPersistentModelIndex getRootIndex() const;

        bool isDir(const QModelIndex& index) const;
        QString fileName(const QModelIndex& index) const;
        QString filePath(const QModelIndex& index) const;

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

    private:
        QFileSystemModel* fsModel;
        QPersistentModelIndex fsModelRootIndex;

        bool isVideoFile(const QModelIndex& fsModelIndex) const;
        int hasVideoFiles(const QModelIndex& fsModelIndex) const;
        QModelIndex getFirstVideoFile(const QModelIndex& fsModelIndex) const;
};

#endif // MOVIECOLLECTIONMODEL_H
