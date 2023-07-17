#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graph.h>

#include <QMainWindow>

#include "calc.h"

#ifdef __cplusplus
extern "C" {
#include "../s21_smartcalc_v1.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void click_button();
  void click_button_clear();
  void click_button_eq();
  void click_button_plusminus();
  void click_button_mode();

 private:
  Ui::MainWindow *ui;
  calc *mode;
};
#endif  // MAINWINDOW_H
