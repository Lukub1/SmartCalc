#include "graph.h"

#include "../s21_smartcalc_v1.h"
#include "ui_graph.h"

graph::graph(QWidget *parent) : QWidget(parent), ui(new Ui::graph) {
  ui->setupUi(this);
  h = 0.1;
  xBegin = ui->lineEdit_min->text().toDouble();
  xEnd = ui->lineEdit_max->text().toDouble();

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(xBegin, xEnd);
  n = (xEnd - xBegin) / h + 2;
}

graph::~graph() { delete ui; }

void graph::on_pushButton_plot_clicked() {
  xBegin = (ui->lineEdit_min->text().toDouble() > -1000000)
               ? ui->lineEdit_min->text().toDouble()
               : -1000000;
  xEnd = (ui->lineEdit_max->text().toDouble() < 1000000)
             ? ui->lineEdit_max->text().toDouble()
             : 1000000;

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(xBegin, xEnd);
  n = (xEnd - xBegin) / h + 2;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
  ui->widget->clearGraphs();
  timer->start(20);
  X = xBegin;

  x.clear();
  y.clear();
}

void graph::TimerSlot() {
  char *str;
  int error = 0;
  QString string = ui->lineEdit->text().trimmed();
  string.replace("x", QString::number(X));
  string.replace("X", QString::number(X));
  str = new char[string.size() + 10];
  memset(str, 0, string.size() + 10);
  memcpy(str, string.toLocal8Bit().data(), string.size() + 10);
  qDebug() << str;
  char *result;
  result = new char[strlen(str)];
  memset(result, 0, strlen(str));
  convert_string(str, result);
  form = result;

  if (time <= 20 * n) {
    if (X <= xEnd) {
      double res_y = polish(result, &error);
      qDebug() << result << X << res_y;
      x.push_back(X);
      y.push_back(res_y);
      X += h;
    }
    time += 20;
  } else {
    time = 0;
    timer->stop();
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->rescaleAxes();
  ui->widget->replot();
}
