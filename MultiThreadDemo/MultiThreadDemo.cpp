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
    mIsCalculating = false ;
    ui->setupUi(this);

    connect(ui->btn_calculate, &QPushButton::clicked, this, &MultiThreadDemo::btn_calculate_slot);

    mThread    = new QThread();
    mCalculate = new Calculate();

    mCalculate->moveToThread(mThread); // �ı�mCalculate���߳�������ϵ��������������߳���ִ��

	//! �ͷŶѿռ���Դ�������ڴ�й¶
	connect(mThread, &QThread::finished, mThread, &QObject::deleteLater);
	connect(mThread, &QThread::finished, mCalculate, &QObject::deleteLater);

    //! ע�⣺��ʹ�ÿ��߳�ͨ��ʱ��������ҪΪԪ�������ͣ�������Ҳ���Ͳ������������й� meta ʲô�ģ�
	qRegisterMetaType<CalculateInputStruct>("CalculateInputStruct"); // ���ṹ�� CalculateInputStruct ע��ΪԪ��������

	//! ���������źŲۣ����ڴ����߳�ִ�вۺ����������    
	connect(this, &MultiThreadDemo::StartCalculate, mCalculate, &Calculate::startCalculateSlot, Qt::QueuedConnection); // Ĭ��ʹ��Qt::QueuedConnection����֤�ۺ�����ִ��˳��
	connect(mCalculate, &Calculate::CalculateFinished, this, &MultiThreadDemo::calculate_finished_slot, Qt::QueuedConnection); 
	connect(mCalculate, &Calculate::UpdateProssorbar, this, &MultiThreadDemo::update_prossorbar_slot, Qt::QueuedConnection);

    mThread->start(); // �����̣߳��߳�Ĭ�Ͽ����¼�ѭ���������߳��������¼�ѭ��״̬
}

MultiThreadDemo::~MultiThreadDemo()
{
    delete ui;
}

void MultiThreadDemo::btn_calculate_slot()
{
	auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͼ������id�Ƿ���ͬ

    if (mIsCalculating)
    {
        ui->calculate_message->append(u8"���ڼ��㣬���Ժ�...");
        return;
    }
    mIsCalculating    = true;

    QString start_msg = 
        QString(u8"���μ������ %1�����߳���Ҫʱ��Ϊ %3s����ǰ�����߳����� %2\n")
        .arg(ui->line_edit_calculate_count->text())
        .arg(ui->line_edit_thread_max_count->text())
        .arg(ui->line_edit_calculate_count->text().toInt()*0.5);
    start_msg += u8"��ʼ���㣬��ǰʱ�䣺" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    ui->calculate_message->append(start_msg);

    auto max_count_str  = ui->line_edit_thread_max_count->text();
    if (max_count_str   == "" || max_count_str.toInt() <= 0)
    {
        ui->calculate_message->append(u8"��������߳�������Ҫ����0��");
        return;
    }
    auto calculate_count_str = ui->line_edit_calculate_count->text();
    if (calculate_count_str  == "" || calculate_count_str.toInt() <= 0)
    {
        ui->calculate_message->append(u8"���������Ҫ����0��");
        return;
    }

    CalculateInputStruct input;
	input.msg            = "start";
	input.threadMaxCount = max_count_str.toInt();
	input.calculateCount = calculate_count_str.toInt();

    ui->calculate_prossorbar->reset();
    ui->calculate_prossorbar->setRange(0, input.calculateCount);
    ui->calculate_prossorbar->setValue(0);

    emit StartCalculate(input);
    mStartTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zz");
}

void MultiThreadDemo::calculate_finished_slot()
{
    mIsCalculating       = false;
	QString finished_msg = u8"������ɣ���ǰʱ�䣺" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	ui->calculate_message->append(finished_msg);
    ui->calculate_message->append(u8"=========================");
    ui->calculate_message->append("");
    ui->calculate_message->append("");

    int i = 1;
}

void MultiThreadDemo::update_prossorbar_slot()
{
    auto cur_num = ui->calculate_prossorbar->value();
    if (cur_num < ui->calculate_prossorbar->maximum())
    {
        ui->calculate_prossorbar->setValue(cur_num + 1);
    }    
}
