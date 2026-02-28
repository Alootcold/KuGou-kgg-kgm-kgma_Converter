#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QMap>
#include <QDragEnterEvent>
#include <QDropEvent>

class FileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileWidget(QWidget *parent = nullptr);
    ~FileWidget();

    void addFiles(const QStringList& files);
    void removeFile(int row);
    void clearAll();
    QStringList getAllFiles() const;
    int getFileCount() const;

signals:
    void filesDropped(const QStringList& files);

private slots:
    void onRemoveButtonClicked(int row);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupUI();
    void addFile(const QString& filePath);
    QString getFileType(const QString& filePath) const;
    QString getFileSize(qint64 bytes) const;
    QString getFileStatus(const QString& extension) const;

    QTableWidget* m_tableWidget;
    QMap<int, QString> m_filePaths;
};

#endif // FILEWIDGET_H
