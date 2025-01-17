#include "MultiThreadDemo.h"
#include "ui_MultiThreadDemo.h"

#include <QThread>
#include "Calculate.h"

MultiThreadDemo::MultiThreadDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MultiThreadDemoClass())
{
    ui->setupUi(this);

    mThread    = new QThread();
    mCalculate = new Calculate();

    mCalculate->moveToThread(mThread); // 改变mCalculate的线程依附关系，将计算类放在线程中执行

	//! 释放堆空间资源，避免内存泄露
	connect(mThread, &QThread::finished, mThread, &QObject::deleteLater);
	connect(mThread, &QThread::finished, mCalculate, &QObject::deleteLater);

	//! 连接其他信号槽，用于触发线程执行槽函数里的任务
    //! 注意：在使用跨线程通信时，参数需要为元数据类型（具体我也解释不清楚，反正是有关 meta 什么的）
    // 将结构体 CalculateInputStruct 注册为元数据类型，如果是继承自QObject的类，则不用注册
	connect(this, &MultiThreadDemo::StartCalculate, mCalculate, &Calculate::startCalculateSlot,Qt::QueuedConnection);              // 默认使用Qt::QueuedConnection，保证槽函数的执行顺序
	connect(mCalculate, &Calculate::CalculateFinished, this, &MultiThreadDemo::calculate_finished_slot/*, Qt::DirectConnection*/); // 有场景可能因为执行顺序问题，而不能正确响应，就需要用到 DirectConnection

    mThread->start(); //启动线程，线程默认开启事件循环，并且线程正处于事件循环状态
}

MultiThreadDemo::~MultiThreadDemo()
{
    delete ui;
}

void MultiThreadDemo::btn_calculate_slot()
{
    auto test_thread_id = QThread::currentThreadId(); // 查看当前线程的id和计算类的id是否相同

    CalculateInputStruct input;
	input.msg = "start";
	input.threadMaxCount = ui->line_edit_thread_max_count->text().toInt();

    emit StartCalculate(input);
}

void MultiThreadDemo::calculate_finished_slot()
{

}
