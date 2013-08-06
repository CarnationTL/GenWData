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

#define PI 3.1415926
namespace Ui {
class MWGenWData;
}


class SinusData: public QwtSyntheticPointData
{
public:
    SinusData(double amp):
        QwtSyntheticPointData( 100 )
    {
        _amp = amp;
    }
    virtual double y( double x ) const
    {
        double frequency = 1;
		return _amp * sin(PI / 180.0 * (360.0 * frequency * x)); 
        //return (_amp * qSin( x ));
    }
private:
    double _amp;
};


class TriData: public QwtSyntheticPointData
{
public:
    TriData(double amp):
        QwtSyntheticPointData( 100 )
    {
        _amp = amp;
    }
    virtual double y( double x ) const {
        double frequency = 1;
		double	phase_i = fmod((360.0 * frequency * x), 360.0);
		double	percentPeriod = phase_i / 360.0;
		double	dat = _amp * 4.0 * percentPeriod;

		if(percentPeriod <= 0.25)
		{
			return dat;
		}
		else if(percentPeriod <= 0.75)
		{
            return (2.0 * _amp - dat);
		}
		else
		{
		    return (dat - 4.0 * _amp);
		}
    }
private:
    double _amp;
};

class SawData: public QwtSyntheticPointData
{
public:
    SawData(double amp):
        QwtSyntheticPointData( 100 )
    {
        _amp = amp;
    }
    virtual double y( double x ) const {
#if 1
        double t = 0;
        double *phase = &t;
        double frequency = 1;
        double	phase_i = fmod((*phase + 360.0 * frequency * x), 360.0);
		double	percentPeriod = phase_i / 360.0;
        double	dat = _amp * 2.0 * percentPeriod;
        return (percentPeriod <= 0.5 ? dat : dat - 2.0 * _amp);
#endif
    }
private:
    double _amp;
};


class SquData: public QwtSyntheticPointData
{
public:
    SquData(double amp, double duc):
        QwtSyntheticPointData( 100 ) {
        _amp = amp;
        _dutyc = duc;
    }
    virtual double y( double x ) const {
        double frequency = 1;
        double	phase_i = fmod((360.0 * frequency * x), 360.0);
        //set the dutyCycle of Square wave
        return (phase_i / 360.0 <= _dutyc / 100.0 ? _amp: -_amp);
       // *phase = fmod(*phase + frequency * 360.0 * numElements, 360.0);
    }
private:
    double _amp;
    double _dutyc;
};

class CurveDataN
{
public:
    CurveDataN(double x, double y, int segsize) {
        xv.append(x);
        yv.append(y);
        _segsize = segsize;
    }
    ~CurveDataN() {

    }
    QVector <QPointF> getData() {
        return ret;
    }
    void appendP(double x, double y) {
        xv.append(x);
        xv.append(y);
        interval = double(xv.at (xv.size () - 1)) / double (xv.size () * _segsize);
    }
private:
    QVector <QPointF> ret;
    QVector <double> xv;
    QVector <double> yv;
    QVector <double> klst;
    double interval;
    int _segsize;

    void GenPoints() {
        int tsize = xv.size() * _segsize;
        for(int i = 0; i < tsize; i++) {

        }
    }

};


class CusData: public QwtSyntheticPointData
{
public:
    CusData(double x, double y, int tsize):
        QwtSyntheticPointData(tsize) {
        xv.append (x);
        yv.append (y);
        segsize = tsize;
    }
    virtual double y(double x) const {
        int i = 0;
        double k = 2;
        if(x >= 0 && x <= 1) {
            return 1 * x;
        } else if(x > 1 && x <= 2) {
            return -2 * x;
        } else if(x > 2 && x <= 3) {
            return  3 * x;
        } else if(x > 3 && x <= 4) {
            return 4 * x;
        }

#if 0

        for(; i < xv.size (); i++) {
            if(xv.size () <= 1) {
                k = 0;
                break;
            }
            if(x <= xv.at (xv.size () - 1) && x >= xv.at (xv.size () - 2)) {
                double dy = yv.at (yv.size () - 1) - yv.at (yv.size () - 2);
                double dx = xv.at (xv.size () - 1) - xv.at (xv.size () - 2);
                if(dx != 0.0) {
                    k = dy - dx;
                    break;
                } else {
                    k = 0;
                    break;
                }
            } else if(x >= xv.at (i) && x < xv.at (i + 1) ){
                k = (yv.at (i + 1) - yv.at (i)) / (xv.at (i + 1) - xv.at (i));
                break;
            }
        }
        return k * x;
#endif

        //return k * x;
    }

    void appendP(double x, double y) {
        xv.append (x);
        yv.append (y);

        klst.clear ();
        GenKlist ();

        this->setSize (yv.size () * segsize);
    }
private:
    void GenKlist() {
        for(int i = 0; i < xv.size (); i++) {
            if(i == 0) {
                double dx = xv.at (1) - xv.at (0);
                if(dx != 0.0) {
                    double k = (yv.at (1) - yv.at (0)) / dx;
                    klst.append (k);
                } else {
                    return;
                }
            } else if ( i == xv.size () - 1) {
                double dy = yv.at (yv.size () - 1) - yv.at (yv.size () - 2);
                double dx = xv.at (xv.size () - 1) - xv.at (xv.size () - 2);
                if(dx != 0.0) {
                    double k = dy / dx;
                    klst.append (k);
                } else {
                    return;
                }
            } else {
                double dx = xv.at (i) - xv.at (i - 1);
                double dy = yv.at (i) - yv.at (i - 1);
                if(dx != 0.0) {
                    double k = dy / dx;
                    klst.append (k);
                } else {
                    return;
                }
            }
        }
    }
    QVector <double> xv;
    QVector <double> yv;
    QVector <double> klst;
    int segsize;
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

    void on_btnLoad_clicked();

    void on_sbstartTime_valueChanged(double arg1);

    void on_sbEndTime_valueChanged(double arg1);

    void on_sbStartY_valueChanged(double arg1);

    void on_sbEndY_valueChanged(double arg1);

    void on_btnConfirmSeg_clicked();

private:
    Ui::MWGenWData *ui;
    int _dcnt;
    enum {SINE, SAW, TRI, SQU, CUS };
    int _type;
    void toggleDutycHide(bool f);
    QwtPlot *plot;
    QwtPlotCurve *pc;
    void doPlot(int t);
    void doPlot(QStringList strdata);
    void doPlotCus();

    double _amp;
    double _time;
    double _dutyc;
    void readSetting(QString fn);
    void setrbCheck(int t);
    void setTimeSp(double time);

    QString consSdata(QString x, QString y);
    QStringList deconsSdata(QString xy);

};

#endif // MWGENWDATA_H

