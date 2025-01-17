#include "MultiThreadDemo.h"
#include "ui_MultiThreadDemo.h"

#include <QThread>
#include <QDateTime>
#include "Calculate.h"
#include "CalculateInputStruct.h"

MultiThreadDemo::MultiThreadDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MultiThreadDemoClass())
{
    ui->setupUi(this);

    connect(ui->btn_calculate, &QPushButton::clicked, this, &MultiThreadDemo::btn_calculate_slot);

    mThread    = new QThread();
    mCalculate = new Calculate();

    mCalculate->moveToThread(mThread); // �ı�mCalculate���߳�������ϵ��������������߳���ִ��

	//! �ͷŶѿռ���Դ�������ڴ�й¶
	connect(mThread, &QThread::finished, mThread, &QObject::deleteLater);
	connect(mThread, &QThread::finished, mCalculate, &QObject::deleteLater);

	//! ���������źŲۣ����ڴ����߳�ִ�вۺ����������
    //! ע�⣺��ʹ�ÿ��߳�ͨ��ʱ��������ҪΪԪ�������ͣ�������Ҳ���Ͳ�������������й� meta ʲô�ģ�
    qRegisterMetaType<CalculateInputStruct>("CalculateInputStruct");// ���ṹ�� CalculateInputStruct ע��ΪԪ�������ͣ�����Ǽ̳���QObject���࣬����ע��
	connect(this, &MultiThreadDemo::StartCalculate, mCalculate, &Calculate::startCalculateSlot, Qt::QueuedConnection);              // Ĭ��ʹ��Qt::QueuedConnection����֤�ۺ�����ִ��˳��
	connect(mCalculate, &Calculate::CalculateFinished, this, &MultiThreadDemo::calculate_finished_slot, Qt::QueuedConnection); // �г���������Ϊִ��˳�����⣬��������ȷ��Ӧ������Ҫ�õ� DirectConnection

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
            mStartTime;
	QString end_time_str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zz");

    int i = 1;
}
