#ifndef InputDialog_H
#define InputDialog_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QGridLayout>
class InputDialog : public QWidget
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog() = default;
private:
    int startValue;
    int endValue;
    int maxValue;
    QSpinBox* endValuesBox;
    QSpinBox* startValuesBox;
signals:
    void gotAllValues(int startValue, int endValue) const;

public slots:
    void setup();
    void setValue(int);
    void checkAllValues();
};

#endif // InputDialog_H
