#include "dropzone.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>

DropZone::DropZone(QWidget *parent)
    : QWidget(parent)
    , m_label(nullptr)
    , m_highlight(false)
{
    setMinimumSize(200, 100);

    m_label = new QLabel("拖拽文件到此处", this);
    m_label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->addWidget(m_label);

    setAcceptDrops(true);
    updateStyle();
}

DropZone::~DropZone()
{
}

void DropZone::setPlaceholderText(const QString& text)
{
    if (m_label) {
        m_label->setText(text);
    }
}

void DropZone::setAcceptDropsEnabled(bool accept)
{
    QWidget::setAcceptDrops(accept);
}

void DropZone::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        m_highlight = true;
        updateStyle();
        event->acceptProposedAction();
    }
}

void DropZone::dragLeaveEvent(QDragLeaveEvent* event)
{
    Q_UNUSED(event);
    m_highlight = false;
    updateStyle();
}

void DropZone::dropEvent(QDropEvent* event)
{
    m_highlight = false;
    updateStyle();

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

void DropZone::updateStyle()
{
    if (m_highlight) {
        setStyleSheet(R"(
            QWidget {
                border: 2px dashed #1DB954;
                border-radius: 8px;
                background-color: #E8FFE8;
            }
            QLabel {
                font-size: 14px;
                color: #1DB954;
            }
        )");
    } else {
        setStyleSheet(R"(
            QWidget {
                border: 2px dashed #ddd;
                border-radius: 8px;
                background-color: #fafafa;
            }
            QLabel {
                font-size: 14px;
                color: #999;
            }
        )");
    }
}
