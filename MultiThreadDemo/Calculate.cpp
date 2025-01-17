#include "Calculate.h"
#include <QThread>
#include <QThreadPool>

#include "CalculateRunnable.h"

Calculate::Calculate(QObject* parent/*=nullptr*/)
{

}

Calculate::~Calculate()
{

}

void Calculate::startCalculateSlot(const CalculateInputStruct aInput)
{
	auto test_thread_id = QThread::currentThreadId(); // 查看当前线程的id和界面类、任务类的id是否相同

	QThreadPool thread_pool;
	thread_pool.setMaxThreadCount(aInput.threadMaxCount); // 设置线程池的最大线程数为1
	for (int i = 0; i < 20; i++) 
	{
		thread_pool.start(new CalculateRunnable);
	}
	thread_pool.waitForDone(); // 等待所有任务完成
	emit CalculateFinished();
}
