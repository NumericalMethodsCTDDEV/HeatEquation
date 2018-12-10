#include "dataModifier.h"
#include "backend.h"
#include "config.h"
#include <string>

DataModifier::DataModifier(QChartView *chart, QLineEdit *curTime, QComboBox *comboBoxU,
                           QComboBox *comboBoxK, QComboBox *comboBoxDT, QComboBox *comboBoxDX,
                           QComboBox *comboBoxMethod, QComboBox *comboBoxStartProfile)
    : chart(chart), curTime(curTime), comboBoxU(comboBoxU), comboBoxK(comboBoxK),
      comboBoxDT(comboBoxDT), comboBoxDX(comboBoxDX), comboBoxMethod(comboBoxMethod),
      comboBoxStartProfile(comboBoxStartProfile)
{
}

DataModifier::~DataModifier()
{
    ConfigSingleton::releaseConfigs();
    delete solver_ptr;
}

void DataModifier::start()
{
    ConfigSingleton::releaseConfigs();
    wasStartPressed = true;
    double u = comboBoxU->currentText().toDouble();
    double k = comboBoxK->currentText().toDouble();
    double dt = comboBoxDT->currentText().toDouble();
    double dx = comboBoxDX->currentText().toDouble();
    int method_id = comboBoxMethod->currentIndex();
    int start_profile_id = comboBoxStartProfile->currentIndex();
    ConfigSingleton::createConfigs(u, k, dt, dx, method_id, start_profile_id);
    try
    {
        solver_ptr = create_solver();
        update();
    }
    catch (std::runtime_error *e)
    {
        QMessageBox *message_box = new QMessageBox;
        message_box->setText(e->what());
        message_box->show();
        message_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    }
}

template <typename T>
static inline std::pair<T, T> _find_min_max(const std::vector<T> &v)
{
    T mi = std::numeric_limits<T>::max();
    T ma = std::numeric_limits<T>::min();
    for (const auto &x : v)
    {
        if (x > ma)
            ma = x;
        if (x < mi)
            mi = x;
    }
    return {mi, ma};
}

static inline void rebuildChartWithNewData(QChart *chart, const std::vector<double> &x,
                                           const std::vector<double> &y)
{
    chart->removeAllSeries();
    //    std::pair<double, double> min_max_x = _find_min_max(x);
    //    std::pair<double, double> min_max_y = _find_min_max(y);
    //    chart->axisX()->setRange(min_max_x.first - 0.2 * fabs(min_max_x.first),
    //                             min_max_x.second + 0.2 * fabs(min_max_x.second));
    //    chart->axisY()->setRange(min_max_y.first - 0.2 * fabs(min_max_y.first),
    //                             min_max_y.second + 0.2 * fabs(min_max_y.second));
    QLineSeries *series = new QLineSeries();

    size_t minSz = std::min(x.size(), y.size());

    for (size_t i = 0; i != minSz; ++i)
    {
        series->append(x[i], y[i]);
    }

    chart->addSeries(series);
    chart->update();
}

void DataModifier::update()
{
    const std::vector<double> &T = solver_ptr->get_T();
    const std::vector<double> &x = solver_ptr->get_x();
    double cur_t = solver_ptr->get_cur_t();
    curTime->setText(QString::number(cur_t));
    rebuildChartWithNewData(chart->chart(), x, T);
}

void DataModifier::step()
{
    if (!wasStartPressed)
        return;
    try
    {
        solver_ptr->do_step();
    }
    catch (std::runtime_error *e)
    {
        QMessageBox *message_box = new QMessageBox;
        message_box->setText(e->what());
        message_box->show();
        message_box->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    }
    update();
}
