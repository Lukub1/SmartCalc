#include "deposit.h"

#include "../s21_smartcalc_v1.h"
#include "QDebug"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QWidget(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_clicked() {
  QString total = "(P*I*T/365)/100";
  total.replace("P", ui->lineEdit_sum->text());
  total.replace("I", ui->lineEdit_rate->text());
  total.replace("T", ui->lineEdit_term->text());
  char *result;
  result = new char[total.size() + 1];
  memset(result, 0, total.size() + 1);
  memcpy(result, total.toLocal8Bit().data(), total.size());
  int error = 0;
  double res = polish(result, &error);
  res -= (res * (ui->lineEdit_taxRate->text().toDouble() / 100));
  ui->lineEdit_total->setText(QString::number(res));
}
