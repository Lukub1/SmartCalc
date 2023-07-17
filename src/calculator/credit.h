#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

extern "C" {
#include "../s21_smartcalc_v1.h"
}
namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
