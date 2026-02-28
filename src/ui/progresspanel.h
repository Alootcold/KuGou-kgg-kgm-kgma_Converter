#ifndef PROGRESSPANEL_H
#define PROGRESSPANEL_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

class ProgressPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressPanel(QWidget *parent = nullptr);
    ~ProgressPanel();

    void setProgress(int value);
    void setMaximum(int maximum);
    void setStatus(const QString& status);
    void setCurrentFile(const QString& fileName);
    void reset();

signals:
    void cancelled();

private:
    QProgressBar* m_progressBar;
    QLabel* m_statusLabel;
    QLabel* m_fileLabel;
};

#endif // PROGRESSPANEL_H
