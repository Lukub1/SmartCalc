#include "credit.h"

#include "../s21_smartcalc_v1.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  connect(ui->pushButton_calc, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  ui->tableWidget->setColumnCount(1);
  int error = 0;
  if (ui->radioButton_an->isChecked()) {
    ui->tableWidget->setRowCount(1);
    QString total = "(sum*rate/(12*100))/(1-((1+rate/(12*100))^(~term*12)))";
    total.replace("sum", ui->lineEdit_sum->text());
    total.replace("rate", ui->lineEdit_rate->text());
    total.replace("term", ui->lineEdit_term->text());
    char *result;
    result = new char[total.size() + 1];
    memset(result, 0, total.size() + 1);
    memcpy(result, total.toLocal8Bit().data(), total.size());
    double sum = polish(result, &error);
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(sum));
    ui->tableWidget->setItem(0, 0, item);
    double total_cred = sum * ui->lineEdit_term->text().toDouble() * 12;
    ui->lineEdit_overpay->setText(
        QString::number(total_cred - ui->lineEdit_sum->text().toDouble()));
    ui->lineEdit_total->setText(QString::number(total_cred, 'g', 6));
  } else if (ui->radioButton_dif->isChecked()) {
    char *result;
    double overpay = 0, total = 0;
    int mounth = ui->lineEdit_term->text().toInt() * 12;
    ui->tableWidget->setRowCount(mounth);
    for (int i = 0; i < mounth; i++) {
      QString ep = "OD/(mounth*12)+(OD-(OD/(mounth*12))*I)*(%/100)/12";
      ep.replace("OD", ui->lineEdit_sum->text());
      ep.replace("mounth", ui->lineEdit_term->text());
      ep.replace("I", QString::number(i));
      ep.replace("%", ui->lineEdit_rate->text());
      result = new char[ep.size() + 1];
      memset(result, 0, ep.size() + 1);
      memcpy(result, ep.toLocal8Bit().data(), ep.size());
      double pay = polish(result, &error);
      total += pay;
      QTableWidgetItem *item = new QTableWidgetItem(QString::number(pay));
      ui->tableWidget->setItem(i, 0, item);
    }
    overpay = total - ui->lineEdit_sum->text().toDouble();
    ui->lineEdit_overpay->setText(QString::number(overpay));
    ui->lineEdit_total->setText(QString::number(total));
  }
}
