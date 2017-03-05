#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent): QWidget(parent)
{
    setup();
}

void InputDialog::setup()
{

    startValuesBox = new QSpinBox(this);
    endValuesBox = new QSpinBox(this);
    QDialogButtonBox* finishBox{new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)};
    QObject::connect(finishBox, SIGNAL(accepted()), this, SLOT(checkAllValues()));
    QObject::connect(finishBox, SIGNAL(rejected()), this, SLOT(close()));
    QGridLayout* mainLayout{new QGridLayout(this)};
    mainLayout->addWidget(new QLabel("Xuất phát: "), 0, 0);
    mainLayout->addWidget(startValuesBox, 0, 1);
    mainLayout->addWidget(new QLabel("Đích: "), 1, 0);
    mainLayout->addWidget(endValuesBox, 1, 1);
    mainLayout->addWidget(finishBox, 2, 0, 1, 2);
    setLayout(mainLayout);
}

void InputDialog::setValue(int maxInt)
{
    startValuesBox->setRange(1, maxInt);
    endValuesBox->setRange(1, maxInt);
    setWindowTitle("Nhập giá trị đầu cuối");
    show();
}

void InputDialog::checkAllValues()
{
    if (startValuesBox->value() == endValuesBox->value()) QMessageBox::warning(this, "Giá trị không phù hợp", "Đỉnh xuất phát và đích trùng nhau, vui lòng chọn lại");
    else
    {
        emit gotAllValues(startValuesBox->value(), endValuesBox->value());
        close();
    }
}

