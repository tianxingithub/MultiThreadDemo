#include "MultiThreadDemo.h"
#include "ui_MultiThreadDemo.h"

#include <QThread>
#include <QDateTime>
#include "Calculate.h"

MultiThreadDemo::MultiThreadDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MultiThreadDemoClass())
{
    ui->setupUi(this);

    mThread    = new QThread();
    mCalculate = new Calculate();

    mCalculate->moveToThread(mThread); // �ı�mCalculate���߳�������ϵ��������������߳���ִ��

	//! �ͷŶѿռ���Դ�������ڴ�й¶
	connect(mThread, &QThread::finished, mThread, &QObject::deleteLater);
	connect(mThread, &QThread::finished, mCalculate, &QObject::deleteLater);

	//! ���������źŲۣ����ڴ����߳�ִ�вۺ����������
    //! ע�⣺��ʹ�ÿ��߳�ͨ��ʱ��������ҪΪԪ�������ͣ�������Ҳ���Ͳ�������������й� meta ʲô�ģ�
    // ���ṹ�� CalculateInputStruct ע��ΪԪ�������ͣ�����Ǽ̳���QObject���࣬����ע��
	connect(this, &MultiThreadDemo::StartCalculate, mCalculate, &Calculate::startCalculateSlot,Qt::QueuedConnection);              // Ĭ��ʹ��Qt::QueuedConnection����֤�ۺ�����ִ��˳��
	connect(mCalculate, &Calculate::CalculateFinished, this, &MultiThreadDemo::calculate_finished_slot/*, Qt::DirectConnection*/); // �г���������Ϊִ��˳�����⣬��������ȷ��Ӧ������Ҫ�õ� DirectConnection

    mThread->start(); //�����̣߳��߳�Ĭ�Ͽ����¼�ѭ���������߳��������¼�ѭ��״̬
}

MultiThreadDemo::~MultiThreadDemo()
{
    delete ui;
}

void MultiThreadDemo::btn_calculate_slot()
{
    auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͼ������id�Ƿ���ͬ

    CalculateInputStruct input;
	input.msg = "start";
	input.threadMaxCount = ui->line_edit_thread_max_count->text().toInt();

    emit StartCalculate(input);
    mStartTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zz");
}

void MultiThreadDemo::calculate_finished_slot()
{
	QString end_time_str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    auto time = end_time_str + " - " + mStartTime;
    int i = 1;
}
