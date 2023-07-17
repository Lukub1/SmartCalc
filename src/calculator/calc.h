#ifndef CALC_H
#define CALC_H

#include <QWidget>

#include "credit.h"
#include "deposit.h"
#include "graph.h"

namespace Ui {
class calc;
}

class calc : public QWidget {
  Q_OBJECT

 public:
  explicit calc(QWidget *parent = nullptr);
  ~calc();
 private slots:
  void click_button();

 private:
  Ui::calc *ui;
  graph *graphic;
  credit *cred;
  deposit *dep;
};

#endif  // CALC_H
