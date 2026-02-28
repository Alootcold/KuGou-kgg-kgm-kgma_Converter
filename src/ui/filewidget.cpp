#include "filewidget.h"
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>

FileWidget::FileWidget(QWidget *parent)
    : QWidget(parent)
    , m_tableWidget(nullptr)
{
    setupUI();
    setAcceptDrops(true);
}

FileWidget::~FileWidget()
{
}

void FileWidget::setupUI()
{
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "文件名" << "格式" << "大小" << "状态" << "操作");

    m_tableWidget->horizontalHeader()->setStretchLastSection(false);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    m_tableWidget->setColumnWidth(4, 100);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setAlternatingRowColors(true);

    // 深色主题样式
    m_tableWidget->setStyleSheet(R"(
        QTableWidget {
            border: 1px solid #444;
            border-radius: 4px;
            background-color: #1a1a1a;
            gridline-color: #333;
            color: #ffffff;
        }
        QTableWidget::item {
            padding: 8px;
            color: #ffffff;
        }
        QTableWidget::item:selected {
            background-color: #00A0E9;
            color: white;
        }
        QHeaderView::section {
            background-color: #2d2d2d;
            padding: 8px;
            border: none;
            border-right: 1px solid #444;
            border-bottom: 2px solid #00A0E9;
            font-weight: bold;
            color: #00A0E9;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tableWidget);
}

void FileWidget::addFiles(const QStringList& files)
{
    for (const QString& file : files) {
        addFile(file);
    }
}

void FileWidget::addFile(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        return;
    }

    for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
        if (m_filePaths.value(row) == filePath) {
            return;
        }
    }

    int row = m_tableWidget->rowCount();
    m_tableWidget->insertRow(row);
    m_filePaths.insert(row, filePath);

    m_tableWidget->setItem(row, 0, new QTableWidgetItem(fileInfo.fileName()));
    m_tableWidget->setItem(row, 1, new QTableWidgetItem(getFileType(filePath).toUpper()));
    m_tableWidget->setItem(row, 2, new QTableWidgetItem(getFileSize(fileInfo.size())));
    m_tableWidget->setItem(row, 3, new QTableWidgetItem(getFileStatus(fileInfo.suffix())));

    QWidget* buttonWidget = new QWidget();
    QPushButton* removeButton = new QPushButton("删除");
    removeButton->setFixedSize(80, 32);
    removeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #ff4757;
            color: #ffffff;
            border: none;
            border-radius: 4px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #ee3742;
        }
        QPushButton:pressed {
            background-color: #cc2936;
        }
    )");
    connect(removeButton, &QPushButton::clicked, this, [this, row]() {
        onRemoveButtonClicked(row);
    });

    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(2, 4, 4, 4);
    buttonLayout->addWidget(removeButton);
    buttonLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_tableWidget->setCellWidget(row, 4, buttonWidget);
    m_tableWidget->setRowHeight(row, 56);
}

void FileWidget::removeFile(int row)
{
    if (row >= 0 && row < m_tableWidget->rowCount()) {
        m_tableWidget->removeRow(row);
        m_filePaths.remove(row);
    }
}

void FileWidget::clearAll()
{
    m_tableWidget->setRowCount(0);
    m_filePaths.clear();
}

QStringList FileWidget::getAllFiles() const
{
    return m_filePaths.values();
}

int FileWidget::getFileCount() const
{
    return m_tableWidget->rowCount();
}

void FileWidget::onRemoveButtonClicked(int row)
{
    removeFile(row);
}

QString FileWidget::getFileType(const QString& filePath) const
{
    QFileInfo info(filePath);
    return info.suffix().toLower();
}

QString FileWidget::getFileSize(qint64 bytes) const
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

QString FileWidget::getFileStatus(const QString& extension) const
{
    QString ext = extension.toLower();
    if (ext == "kgma" || ext == "kgm" || ext == "vpr") {
        return "待转换";
    } else if (ext == "kgg") {
        return "不支持";
    } else {
        return "未知";
    }
}

void FileWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void FileWidget::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QStringList files;

    for (const QUrl& url : urls) {
        if (url.isLocalFile()) {
            files.append(url.toLocalFile());
        }
    }

    if (!files.isEmpty()) {
        emit filesDropped(files);
    }

    event->acceptProposedAction();
}
