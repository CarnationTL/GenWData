#include "mwgenwdata.h"
#include "ui_mwgenwdata.h"
#include <QSettings>
#include <QProgressDialog>

#define D_CNT 256
#define INVALUE -1

#define S_ITEM_AMP "amp"
#define S_ITEM_TIME "time"
#define S_ITEM_DATA "data"
#define S_ITEM_TYPE "type"


MWGenWData::MWGenWData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWGenWData)
{
    ui->setupUi(this);
    _dcnt = D_CNT;


    plot = ui->qwtPlot;
    plot->setAutoDelete (true);
    ui->rbSin->setChecked (true);
    _type = SINE;
    toggleDutycHide (false);
    pc = NULL;
    _amp = -1.0;
    _time = -1.0;
    _dutyc = -1.0;
}

MWGenWData::~MWGenWData()
{
    delete ui;
}

void MWGenWData::on_btnGenWData_clicked() {


    if(_type == INVALUE) {
        QMessageBox::warning (this, "INFO", "please select the wave type, thanks!");
        return;
    }

    QFileDialog fp;
    QString fn = fp.getSaveFileName (this, "Save Data File", ".", "Data (*.wdata)");
    if(fn.isEmpty())
        return;
    if(!fn.endsWith ("*.wdata")) { fn.append (".wdata");
    }

    QSettings set(fn, QSettings::IniFormat);
    QStringList sl;
    for(int i = 0; i < _dcnt; i++) {
        sl << QString::number(i, 10);
    }

    switch (_type) {
    case SINE:
        set.setValue (S_ITEM_TYPE, "SINE");
        break;
    case SAW:
        set.setValue (S_ITEM_TYPE, "SAW");
        break;
    case SQU:
        set.setValue (S_ITEM_TYPE, "SQU");
        break;
    case TRI:
        set.setValue (S_ITEM_TYPE, "TRI");
        break;
    case CUS:
        set.setValue (S_ITEM_TYPE, "CUS");
        break;
    default:
        break;
    }

    //AMP
    set.setValue (S_ITEM_AMP, QString::number (ui->sbAMP->value (), 'g', 3));
    //TIME
    set.setValue (S_ITEM_TIME, QString::number (ui->sbTIME->value (), 'g', 3));

    set.setValue(S_ITEM_DATA, sl);

    QStringList list =  set.value (S_ITEM_DATA).toStringList ();
    for(int i = 0; i < list.length (); i++) {
        qDebug () << list.at (i).toDouble ();
    }

    qDebug () << fn ;

    //read form file
    QSettings setread(fn);
    qDebug () << setread.value (S_ITEM_AMP).toDouble ();
} 


void MWGenWData::on_btnClose_clicked() {
    QApplication::closeAllWindows ();
}

void MWGenWData::on_rbSin_clicked() {
    _type = SINE;
    toggleDutycHide (false);
}

void MWGenWData::on_rbSquare_clicked() {
    _type = SQU;
    toggleDutycHide (true);
}

void MWGenWData::on_rbSaw_clicked() {
    _type = SAW;
    toggleDutycHide (false);
}

void MWGenWData::on_rbTri_clicked() {
    _type = TRI;
    toggleDutycHide (false);
}

void MWGenWData::on_rbCus_clicked() {
    _type = CUS;
}

void MWGenWData::toggleDutycHide(bool f) {
    if(f == true) {
        ui->lbDUTY->show ();
        ui->sbDUTY->show ();
    } else {
        ui->lbDUTY->hide ();
        ui->sbDUTY->hide ();
    }
}


//do plot for regular curves
void MWGenWData::doPlot() {

    if(pc == NULL) {
        pc = new QwtPlotCurve("test");
    }

    if(pc->dataSize () >= 0) {
        //QwtSetSeriesData *sdata;
        plot->setAxisScale (QwtPlot::xBottom, 0.0, 10.0);
        plot->setAxisScale (QwtPlot::yLeft, -1.0, 1.0);
        pc->setData (new SinusData());
        pc->attach (plot);
        plot->show ();
        plot->replot ();
    }

}


//do plot for cus curves
void MWGenWData::doPlotCus() {
    pc = new QwtPlotCurve("test");
    //QwtSetSeriesData *sdata;
    plot->setAxisAutoScale (QwtPlot::xBottom, true);
    plot->setAxisAutoScale (QwtPlot::yLeft, true);
    pc->setData (new TriData());
    pc->attach (plot);
    plot->show ();
    plot->replot ();
}

void MWGenWData::on_sbAMP_valueChanged(double arg1) {
    if(arg1 >= 0.0) {
        _amp = arg1;
    }

    switch (_type) {
        case SINE:
            doPlot();
            break;
        case SAW :
            doPlot();
            break;
        case TRI :
            doPlot();
            break;
        case SQU :
            doPlot();
            break;
        default:
            break;
    }
}

void MWGenWData::on_sbTIME_valueChanged(double arg1) {
    if(arg1 > 0) {
        _time = arg1;
    }
    switch (_type) {
        case SINE:
            doPlot();
            break;
        case SAW :
            doPlot();
            break;
        case TRI :
            doPlot();
            break;
        case SQU :
            doPlot();
            break;
        default:
            break;
    }
}

void MWGenWData::on_sbDUTY_valueChanged(double arg1) {
    if(arg1 >= 0.0) {
        _dutyc = arg1;
    }
    switch (_type) {
        case SINE:
            doPlot();
            break;
        case SAW :
            doPlot();
            break;
        case TRI :
            doPlot();
            break;
        case SQU :
            doPlot();
            break;
        default:
            break;
    }
}
