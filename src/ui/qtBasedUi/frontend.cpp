/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "../frontend.h"
#include "dataModifier.h"

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtGui/QFontDatabase>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets>

static inline QComboBox *createComboBox()
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

QT_CHARTS_USE_NAMESPACE

static inline QChartView *createChartView(const QSize &sz, const QString &title,
                                          const QString &yAxisName)
{
    QLineSeries *series = new QLineSeries();
    //    QPen pen(QColor(Qt::green));
    //    pen.setWidth(5);
    //    series->setPen(pen);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->createDefaultAxes();
    chart->axisX()->setTitleText("x");
    chart->axisY()->setTitleText(yAxisName);
    QSize screenSize = QSize(sz.width() / 2, sz.height() / 2);
    chart->setMinimumSize(QSize(screenSize.width() / 3, screenSize.height() / 3));
    chart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

int showUi(int argc, char **argv)
{

    QApplication app(argc, argv);
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    const QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QChartView *chart =
        createChartView(QSize(screenGeometry.width(), screenGeometry.height()), "T(x)", "T");
    QLineEdit *comboBoxCurTime = new QLineEdit;
    QComboBox *comboBoxU = createComboBox();
    QComboBox *comboBoxK = createComboBox();
    QComboBox *comboBoxDT = createComboBox();
    QComboBox *comboBoxDX = createComboBox();
    QComboBox *comboBoxMethod = createComboBox();
    QComboBox *comboBoxStartProfile = createComboBox();
    DataModifier *dataModifier =
        new DataModifier(chart, comboBoxCurTime, comboBoxU, comboBoxK, comboBoxDT, comboBoxDX,
                         comboBoxMethod, comboBoxStartProfile);

    QGridLayout *configsLayout = new QGridLayout;

    {
        QLabel *labelU = new QLabel("u");
        QLabel *labelK = new QLabel("k");
        QLabel *labelDT = new QLabel("dt");
        QLabel *labelDX = new QLabel("dx");
        QLabel *labelMethod = new QLabel("Схема");
        QLabel *labelStartProfile = new QLabel("Начальный профиль");
        comboBoxMethod->addItem("Явная схема \"по потоку\"");
        comboBoxMethod->addItem("Явная схема \"против потока\"");
        comboBoxMethod->addItem("Неявная схема \"по потоку\"");
        comboBoxMethod->addItem("Неявная схема \"против потока\"");
        comboBoxMethod->addItem("Чехарда");
        comboBoxMethod->setEditable(false);
        comboBoxStartProfile->addItem("Ступенька");
        comboBoxStartProfile->addItem("Трапеция");
        comboBoxStartProfile->setEditable(false);

        configsLayout->addWidget(labelU, 0, 0);
        configsLayout->addWidget(comboBoxU, 0, 1);

        configsLayout->addWidget(labelK, 1, 0);
        configsLayout->addWidget(comboBoxK, 1, 1);

        configsLayout->addWidget(labelDT, 0, 2);
        configsLayout->addWidget(comboBoxDT, 0, 3);

        configsLayout->addWidget(labelDX, 1, 2);
        configsLayout->addWidget(comboBoxDX, 1, 3);

        configsLayout->addWidget(labelMethod, 0, 4);
        configsLayout->addWidget(comboBoxMethod, 0, 5);

        configsLayout->addWidget(labelStartProfile, 1, 4);
        configsLayout->addWidget(comboBoxStartProfile, 1, 5);
    }

    QHBoxLayout *animationControllLayout = new QHBoxLayout;

    {
        QPushButton *startButton = new QPushButton;
        {
            QPalette pal = startButton->palette();
            pal.setColor(QPalette::Button, QColor(Qt::green));
            startButton->setText(QStringLiteral("Старт"));
            startButton->setAutoFillBackground(true);
            startButton->setPalette(pal);
        }
        QObject::connect(startButton, &QPushButton::clicked, dataModifier, &DataModifier::start);
        animationControllLayout->addWidget(startButton);

        QPushButton *stepButton = new QPushButton;
        stepButton->setText("Сделать шаг по t");
        QObject::connect(stepButton, &QPushButton::clicked, dataModifier, &DataModifier::step);
        animationControllLayout->addWidget(stepButton);
    }

    QHBoxLayout *curTimeLayout = new QHBoxLayout;
    {
        QLabel *labelCurTime = new QLabel("Current time");
        comboBoxCurTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        comboBoxCurTime->setText("0");
        comboBoxCurTime->setReadOnly(true);

        curTimeLayout->addWidget(labelCurTime);
        curTimeLayout->addWidget(comboBoxCurTime);
    }

    mainLayout->addLayout(configsLayout);
    mainLayout->addLayout(animationControllLayout);
    mainLayout->addWidget(chart);
    mainLayout->addLayout(curTimeLayout);

    widget->resize(screenGeometry.width(), screenGeometry.height());
    widget->show();

    return app.exec();
}
