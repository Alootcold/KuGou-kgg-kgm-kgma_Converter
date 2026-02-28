#ifndef STYLESHEET_H
#define STYLESHEET_H

#include <QObject>
#include <QWidget>
#include <QString>

class StyleSheet : public QObject
{
    Q_OBJECT

public:
    explicit StyleSheet(QObject *parent = nullptr);
    ~StyleSheet();

    static void applyDefaultStyle(QWidget* widget);
    static QString getButtonStyle();
    static QString getTableStyle();
    static QString getProgressBarStyle();

private:
    static QString getDefaultStyleSheet();
};

#endif // STYLESHEET_H
