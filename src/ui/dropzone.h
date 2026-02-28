#ifndef DROPZONE_H
#define DROPZONE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class DropZone : public QWidget
{
    Q_OBJECT

public:
    explicit DropZone(QWidget *parent = nullptr);
    ~DropZone();

    void setPlaceholderText(const QString& text);
    void setAcceptDropsEnabled(bool accept);

signals:
    void filesDropped(const QStringList& files);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    QLabel* m_label;
    bool m_highlight;

    void updateStyle();
};

#endif // DROPZONE_H
