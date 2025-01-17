#pragma once

#include <QtWidgets/QMainWindow>
#include "CalculateInputStruct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MultiThreadDemoClass; };
QT_END_NAMESPACE

class QThread;
class Calculate;

class MultiThreadDemo : public QMainWindow
{
    Q_OBJECT

public:
    MultiThreadDemo(QWidget *parent = nullptr);
    ~MultiThreadDemo();

signals:
    void StartCalculate(const CalculateInputStruct aInput); //!< 让计算类开始计算

private:
    void btn_calculate_slot();
    void calculate_finished_slot();

private:
    Ui::MultiThreadDemoClass *ui;
    QThread*   mThread;    //!< 计算类执行的线程
    Calculate* mCalculate; //!< 计算类，放在mThread线程里面执行，避免界面卡死
    QString mStartTime; //!< 记录开始计算时间
};
