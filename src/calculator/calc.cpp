#include "calc.h"

#include "ui_calc.h"

calc::calc(QWidget *parent) : QWidget(parent), ui(new Ui::calc) {
  ui->setupUi(this);
  connect(ui->pushButton_grahp, SIGNAL(clicked()), this, SLOT(click_button()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(click_button()));
}

calc::~calc() { delete ui; }

void calc::click_button() {
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "График") {
    graphic = new graph();
    graphic->setWindowTitle("График");
    graphic->show();

  } else if (button->text() == "Кредитный") {
    cred = new credit();
    cred->setWindowTitle("Кредитный калькулятор");
    cred->show();
  }
  this->close();
}
