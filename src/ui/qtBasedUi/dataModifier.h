#ifndef DATAMODIFIER_H
#define DATAMODIFIER_H

#include <QObject>
#include <QtCharts>
#include <QtWidgets/QLineEdit>
#include "abstractSolver.h"

class DataModifier : public QObject
{
    Q_OBJECT

    QChartView *chart;
    QLineEdit *curTime;
    QComboBox *comboBoxU;
    QComboBox *comboBoxK;
    QComboBox *comboBoxDT;
    QComboBox *comboBoxDX;
    QComboBox *comboBoxMethod;
    QComboBox *comboBoxStartProfile;
    Solver *solver_ptr;

    bool wasStartPressed = false;

    void update();

public:
    DataModifier(QChartView *, QLineEdit *, QComboBox *, QComboBox *, QComboBox *, QComboBox *,
                 QComboBox *, QComboBox *);
    ~DataModifier();
    void start();
    void step();
};

#endif // DATAMODIFIER_H
