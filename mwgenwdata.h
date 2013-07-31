#ifndef MWGENWDATA_H
#define MWGENWDATA_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <qwt_plot.h>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_point_data.h>
#include <Qwt/qwt_series_data.h>
#include <Qwt/qwt_plot.h>

namespace Ui {
class MWGenWData;
}


class SinusData: public QwtSyntheticPointData
{
public:
    SinusData():
        QwtSyntheticPointData( 100 )
    {
    }
    virtual double y( double x ) const
    {
        return qSin( x );
    }
};


class TriData: public QwtSyntheticPointData
{
public:
    TriData():
        QwtSyntheticPointData( 100 )
    {
    }
    virtual double y( double x ) const {



        return qAsin ( x );
    }
};

class SawData: public QwtSyntheticPointData
{
public:
    SawData():
        QwtSyntheticPointData( 100 )
    {
    }
    virtual double y( double x ) const {
#if 0
		double	phase_i = fmod((*phase + 360.0 * frequency * i), 360.0);
		double	percentPeriod = phase_i / 360.0;
		double	dat = amplitude * 2.0 * percentPeriod;
		sawtoothWave[i] = percentPeriod <= 0.5 ? dat : dat - 2.0 * amplitude;
        return qAsin ( x );
#endif
    }
};


class SquData: public QwtSyntheticPointData
{
public:
#if 0
    SawData():
        QwtSyntheticPointData( 100 ) {
    }
    virtual double y( double x ) const {
        return qAsin ( x );
    }
#endif
};



class MWGenWData : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MWGenWData(QWidget *parent = 0);
    ~MWGenWData();
    
private slots:
    void on_btnGenWData_clicked();

    void on_btnClose_clicked();

    void on_rbSin_clicked();

    void on_rbSquare_clicked();

    void on_rbSaw_clicked();

    void on_rbTri_clicked();

    void on_rbCus_clicked();

    void on_sbAMP_valueChanged(double arg1);

    void on_sbTIME_valueChanged(double arg1);

    void on_sbDUTY_valueChanged(double arg1);

private:
    Ui::MWGenWData *ui;
    int _dcnt;
    enum {SINE, SAW, TRI, SQU, CUS };
    int _type;
    void toggleDutycHide(bool f);
    QwtPlot *plot;
    QwtPlotCurve *pc;
    void doPlot();
    void doPlotCus();

    double _amp;
    double _time;
    double _dutyc;
};

#endif // MWGENWDATA_H
