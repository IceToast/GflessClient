#include "otpdialog.h"
#include "ui_otpdialog.h"
#include <QMessageBox>

OtpDialog::OtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtpDialog)
{
    ui->setupUi(this);
}

OtpDialog::~OtpDialog()
{
    delete ui;
}

QString OtpDialog::getOtpCode() const
{
    return ui->otpCodeLineEdit->text().trimmed();
}

void OtpDialog::on_confirmButton_clicked()
{
    if (getOtpCode().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the OTP code");
        return;
    }

    accept();
}

void OtpDialog::on_cancelButton_clicked()
{
    reject();
}
