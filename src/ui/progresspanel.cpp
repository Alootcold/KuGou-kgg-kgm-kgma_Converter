#include "progresspanel.h"

ProgressPanel::ProgressPanel(QWidget *parent)
    : QWidget(parent)
{
    m_progressBar = new QProgressBar(this);
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);

    m_statusLabel = new QLabel("准备就绪", this);
    m_fileLabel = new QLabel("", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_progressBar);
    layout->addWidget(m_statusLabel);
    layout->addWidget(m_fileLabel);

    setStyleSheet(R"(
        QProgressBar {
            border: 1px solid #ddd;
            border-radius: 4px;
            text-align: center;
            height: 25px;
        }
        QProgressBar::chunk {
            background-color: #1DB954;
            border-radius: 3px;
        }
        QLabel {
            color: #666;
            font-size: 12px;
        }
    )");
}

ProgressPanel::~ProgressPanel()
{
}

void ProgressPanel::setProgress(int value)
{
    m_progressBar->setValue(value);
}

void ProgressPanel::setMaximum(int maximum)
{
    m_progressBar->setMaximum(maximum);
}

void ProgressPanel::setStatus(const QString& status)
{
    m_statusLabel->setText(status);
}

void ProgressPanel::setCurrentFile(const QString& fileName)
{
    m_fileLabel->setText("当前文件: " + fileName);
}

void ProgressPanel::reset()
{
    m_progressBar->setValue(0);
    m_statusLabel->setText("准备就绪");
    m_fileLabel->setText("");
}
