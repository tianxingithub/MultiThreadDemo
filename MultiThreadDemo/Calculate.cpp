#include "Calculate.h"
#include <QThread>
#include <QThreadPool>

#include "CalculateRunnable.h"

namespace ThreadDemo
{

	Calculate::Calculate(QObject* parent/*=nullptr*/)
	{
		m_ThreadPool = nullptr;
	}

	Calculate::~Calculate()
	{

	}

	void Calculate::startCalculate(const CalculateInputStruct aInput)
	{
		auto test_thread_id = QThread::currentThreadId(); // 查看当前线程的id和界面类、任务类的id是否相同

		m_ThreadPool = new QThreadPool();
		m_ThreadPool->setMaxThreadCount(aInput.threadMaxCount); // 设置线程池的最大线程数为1
		for (int i = 0; i < aInput.calculateCount; i++)
		{
			CalculateRunnable* runnable = new CalculateRunnable(aInput.calculateCount - i);
			runnable->setAutoDelete(true); // 设置任务结束后自动删除
			m_ThreadPool->start(runnable);

			//! 设置响应方式为消息队列时，会在emit CalculateFinished(); 后再响应，故这里使用直接响应
			connect(runnable, &CalculateRunnable::runnableFinishedSignal, this, [&]() {emit updateProssorbarSignal(); }, Qt::DirectConnection);
		}
		m_ThreadPool->waitForDone(); // 等待所有任务完成
		emit calculateFinishedSignal();

		delete m_ThreadPool;
		m_ThreadPool = nullptr;
	}

	void Calculate::cancelCalculate()
	{
		if (m_ThreadPool)
		{
			m_ThreadPool->clear(); // 清空线程池
			// 		delete mThreadPool;
			// 		mThreadPool = nullptr;
		}
	}

}