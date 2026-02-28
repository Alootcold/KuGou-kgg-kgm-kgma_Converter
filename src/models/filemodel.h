#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include "../decrypt/decrypt_global.h"

struct FileItem {
    QString filePath;
    QString fileName;
    QString extension;
    FileType type;
    QString status;
    QString outputPath;
    qint64 fileSize;
};

class FileModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        FileName = 0,
        Extension,
        Type,
        Status,
        Size,
        Operation
    };

    explicit FileModel(QObject *parent = nullptr);
    ~FileModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addFiles(const QStringList& files);
    void removeFile(int row);
    void updateStatus(int row, const QString& status);
    void clear();

    FileItem getFile(int row) const;
    QVector<FileItem> getAllFiles() const;

private:
    FileType detectFileType(const QString& filePath) const;
    QString getFileSizeStr(qint64 bytes) const;

    QVector<FileItem> m_files;
};

#endif // FILEMODEL_H
