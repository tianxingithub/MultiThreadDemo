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

    mCalculate->moveToThread(mThread); // 改变mCalculate的线程依附关系，将计算类放在线程中执行

	//! 释放堆空间资源，避免内存泄露
	connect(mThread, &QThread::finished, mThread, &QObject::deleteLater);
	connect(mThread, &QThread::finished, mCalculate, &QObject::deleteLater);

    //! 注意：在使用跨线程通信时，参数需要为元数据类型（具体我也解释不清楚，理解是有关 meta 什么的）
	qRegisterMetaType<CalculateInputStruct>("CalculateInputStruct"); // 将结构体 CalculateInputStruct 注册为元数据类型

	//! 连接其他信号槽，用于触发线程执行槽函数里的任务    
	connect(this, &MultiThreadDemo::StartCalculate, mCalculate, &Calculate::startCalculateSlot, Qt::QueuedConnection); // 默认使用Qt::QueuedConnection，保证槽函数的执行顺序
	connect(mCalculate, &Calculate::CalculateFinished, this, &MultiThreadDemo::calculate_finished_slot, Qt::QueuedConnection); 
	connect(mCalculate, &Calculate::UpdateProssorbar, this, &MultiThreadDemo::update_prossorbar_slot, Qt::QueuedConnection);

    mThread->start(); // 启动线程，线程默认开启事件循环，并且线程正处于事件循环状态
}

MultiThreadDemo::~MultiThreadDemo()
{
    delete ui;
}

void MultiThreadDemo::btn_calculate_slot()
{
	auto test_thread_id = QThread::currentThreadId(); // 查看当前线程的id和计算类的id是否相同

    if (mIsCalculating)
    {
        ui->calculate_message->append(u8"正在计算，请稍后...");
        return;
    }
    mIsCalculating    = true;

    QString start_msg = 
        QString(u8"本次计算次数 %1，单线程需要时间为 %3s，当前计算线程数量 %2\n")
        .arg(ui->line_edit_calculate_count->text())
        .arg(ui->line_edit_thread_max_count->text())
        .arg(ui->line_edit_calculate_count->text().toInt()*0.5);
    start_msg += u8"开始计算，当前时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    ui->calculate_message->append(start_msg);

    auto max_count_str  = ui->line_edit_thread_max_count->text();
    if (max_count_str   == "" || max_count_str.toInt() <= 0)
    {
        ui->calculate_message->append(u8"计算最大线程数量需要大于0！");
        return;
    }
    auto calculate_count_str = ui->line_edit_calculate_count->text();
    if (calculate_count_str  == "" || calculate_count_str.toInt() <= 0)
    {
        ui->calculate_message->append(u8"计算次数需要大于0！");
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
	QString finished_msg = u8"计算完成，当前时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
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
