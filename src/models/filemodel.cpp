#include "filemodel.h"
#include <QFileInfo>
#include <QDebug>

FileModel::FileModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

FileModel::~FileModel()
{
}

int FileModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_files.size();
}

int FileModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant FileModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_files.size()) {
        return QVariant();
    }

    const FileItem& item = m_files.at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case FileName:
                return item.fileName;
            case Extension:
                return item.extension.toUpper();
            case Type:
                switch (item.type) {
                    case FileType::KGMA: return "KGMA";
                    case FileType::KGM: return "KGM";
                    case FileType::KGG: return "KGG";
                    case FileType::VPR: return "VPR";
                    default: return "未知";
                }
            case Status:
                return item.status;
            case Size:
                return getFileSizeStr(item.fileSize);
            default:
                return QVariant();
        }
    }

    return QVariant();
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case FileName:
                return "文件名";
            case Extension:
                return "格式";
            case Type:
                return "类型";
            case Status:
                return "状态";
            case Size:
                return "大小";
            case Operation:
                return "操作";
            default:
                return QVariant();
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void FileModel::addFiles(const QStringList& files)
{
    for (const QString& filePath : files) {
        addFiles(QStringList() << filePath);
    }
}

void FileModel::removeFile(int row)
{
    if (row >= 0 && row < m_files.size()) {
        beginRemoveRows(QModelIndex(), row, row);
        m_files.removeAt(row);
        endRemoveRows();
    }
}

void FileModel::updateStatus(int row, const QString& status)
{
    if (row >= 0 && row < m_files.size()) {
        m_files[row].status = status;
        emit dataChanged(index(row, Status), index(row, Status), QVector<int>() << Qt::DisplayRole);
    }
}

void FileModel::clear()
{
    beginResetModel();
    m_files.clear();
    endResetModel();
}

FileItem FileModel::getFile(int row) const
{
    if (row >= 0 && row < m_files.size()) {
        return m_files.at(row);
    }
    return FileItem();
}

QVector<FileItem> FileModel::getAllFiles() const
{
    return m_files;
}

FileType FileModel::detectFileType(const QString& filePath) const
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "kgma") return FileType::KGMA;
    if (ext == "kgm") return FileType::KGM;
    if (ext == "kgg") return FileType::KGG;
    if (ext == "vpr") return FileType::VPR;

    return FileType::Unknown;
}

QString FileModel::getFileSizeStr(qint64 bytes) const
{
    if (bytes < 1024) {
        return QString("%1 B").arg(bytes);
    } else if (bytes < 1024 * 1024) {
        return QString("%1 KB").arg(bytes / 1024.0, 0, 'f', 2);
    } else if (bytes < 1024 * 1024 * 1024) {
        return QString("%1 MB").arg(bytes / (1024.0 * 1024.0), 0, 'f', 2);
    } else {
        return QString("%1 GB").arg(bytes / (1024.0 * 1024.0 * 1024.0), 0, 'f', 2);
    }
}
