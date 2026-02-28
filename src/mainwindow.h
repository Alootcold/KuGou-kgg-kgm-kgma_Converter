#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileWidget;
class ConvertThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFilesClicked();
    void onSelectFolderClicked();
    void onStartConvertClicked();
    void onCancelConvertClicked();
    void onOutputDirClicked();
    void onOpenOutputDirClicked();
    void onClearListClicked();
    void onFormatChanged(int index);

    void onConvertProgress(int current, int total, const QString& filename);
    void onConvertFinished(const QString& outputDir);
    void onConvertError(const QString& msg);

    void onFilesDropped(const QStringList& files);

private:
    Ui::MainWindow *ui;
    FileWidget* m_fileWidget;
    ConvertThread* m_convertThread;

    QString m_outputDir;
    QString m_outputFormat;

    void setupUI();
    void setupConnections();
    void updateButtonsState(bool isConverting);
    QString getDefaultOutputDir() const;
    void showWarningMessage(const QString& title, const QString& msg);
};
#endif // MAINWINDOW_H
