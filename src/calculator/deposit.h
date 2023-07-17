#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
extern "C" {
#include "../s21_smartcalc_v1.h"
}
namespace Ui {
class deposit;
}

class deposit : public QWidget {
  Q_OBJECT

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::deposit *ui;
};

#endif  // DEPOSIT_H
