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
    void StartCalculate(const CalculateInputStruct aInput); //!< �ü����࿪ʼ����

private:
    void btn_calculate_slot();
    void calculate_finished_slot();

private:
    Ui::MultiThreadDemoClass *ui;
    QThread*   mThread;    //!< ������ִ�е��߳�
    Calculate* mCalculate; //!< �����࣬����mThread�߳�����ִ�У�������濨��
    QString mStartTime; //!< ��¼��ʼ����ʱ��
};
