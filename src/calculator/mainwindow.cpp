#include "mainwindow.h"

#include "../s21_smartcalc_v1.h"
#include "QDebug"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(click_button_eq()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_proc, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_brackets_open, SIGNAL(clicked()), this,
          SLOT(click_button()));
  connect(ui->pushButton_brackets_close, SIGNAL(clicked()), this,
          SLOT(click_button()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(click_button_clear()));
  connect(ui->pushButton_mode, SIGNAL(clicked()), this,
          SLOT(click_button_mode()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_plusMinus, SIGNAL(clicked()), this,
          SLOT(click_button_plusminus()));

  ui->pushButton_eq->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::click_button() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->pushButton_eq->isChecked() &&
      !(button->text() == "+" || button->text() == "-" ||
        button->text() == "*" || button->text() == "/")) {
    ui->pushButton_eq->setChecked(false);
    click_button_clear();
  } else {
    ui->pushButton_eq->setChecked(false);
  }
  if (ui->lineEdit_result->text() == "0") {
    click_button_clear();
  }
  if (button->text() == "=") {
  } else {
    ui->lineEdit_result->insert(button->text());
  }
}
void MainWindow::click_button_clear() {
  ui->lineEdit_result->setText("");
  ui->lineEdit_X->setText("X");
}

char *translate_to_string(QString string) {
  char *result;
  result = new char[string.size() + 10];
  memset(result, 0, string.size() + 10);
  memcpy(result, string.toLocal8Bit().data(), string.size() + 10);
  return result;
}

void MainWindow::click_button_eq() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  char *str;
  QString string = ui->lineEdit_result->text().trimmed();
  string.replace("x", ui->lineEdit_X->text());
  string.replace("X", ui->lineEdit_X->text());
  if (string.isEmpty()) ui->lineEdit_result->setText("0");
  str = translate_to_string(string);
  char *result;
  result = new char[strlen(str)];
  memset(result, 0, strlen(str));
  convert_string(str, result);
  int error = 0;
  double res = polish(result, &error);
  if (error) {
    ui->lineEdit_result->setText("ERROR");
  } else {
    ui->lineEdit_result->setText(QString::number(res, 'g', 15));
  }
}

void MainWindow::click_button_plusminus() {
  QString string = ui->lineEdit_result->text().trimmed();
  char *result, *str;
  result = new char[string.size() + 1];
  if (string.isEmpty()) ui->lineEdit_result->setText("0");
  str = new char[string.size() + 1];
  memset(str, 0, string.size() + 1);
  memcpy(str, string.toLocal8Bit().data(), string.size());
  memset(result, 0, string.size() + 1);
  if (reverse_sign(str, result)) {
    ui->lineEdit_result->setText(result);
  } else {
    ui->lineEdit_result->setText(string);
  }
}

void MainWindow::click_button_mode() {
  mode = new calc();
  mode->setWindowTitle("");
  mode->show();
}
