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
    void startCalculateSignal(const CalculateInputStruct aInput); //!< �ü����࿪ʼ����
    void cancleCalculateSignal();                                 //!< ȡ������

private slots:
    void btn_calculate_slot();
    void btn_cancel_calculate_slot();
    void calculate_finished_slot();
    void update_prossorbar_slot();

private:
    Ui::MultiThreadDemoClass *ui;

    QThread*   m_Thread;        //!< ������ִ�е��߳�
    Calculate* m_Calculate;     //!< �����࣬����mThread�߳�����ִ�У�������濨��
    QString    m_StartTime;     //!< ��¼��ʼ����ʱ��
	bool       m_CalculateStatus; //!< ����״̬
};