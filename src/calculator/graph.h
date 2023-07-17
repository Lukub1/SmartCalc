#ifndef GRAPH_H
#define GRAPH_H

#include <QTimer>
#include <QVector>
#include <QWidget>

#ifdef __cplusplus
extern "C" {
#include "../s21_smartcalc_v1.h"
}
#endif

namespace Ui {
class graph;
}

class graph : public QWidget {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

 private slots:
  void on_pushButton_plot_clicked();
  void TimerSlot();

 private:
  Ui::graph *ui;
  double xBegin, xEnd, h, X;
  int n;
  char *form;
  QVector<double> x, y;
  QTimer *timer;
  int time;
};

#endif  // GRAPH_H
