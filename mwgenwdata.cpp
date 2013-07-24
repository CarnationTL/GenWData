#include "mwgenwdata.h"
#include "ui_mwgenwdata.h"


MWGenWData::MWGenWData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWGenWData)
{
    ui->setupUi(this);

}

MWGenWData::~MWGenWData()
{
    delete ui;
}

void MWGenWData::on_btnGenWData_clicked() {
    QFileDialog filedialog(this);
}

void MWGenWData::on_btnClose_clicked()
{

}
