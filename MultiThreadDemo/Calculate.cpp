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
	auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͽ����ࡢ�������id�Ƿ���ͬ

	QThreadPool thread_pool;
	thread_pool.setMaxThreadCount(aInput.threadMaxCount); // �����̳߳ص�����߳���Ϊ1
	for (int i = 0; i < aInput.calculateCount; i++)
	{
		CalculateRunnable* runnable = new CalculateRunnable;
		runnable->setAutoDelete(true); // ��������������Զ�ɾ��
		thread_pool.start(runnable);

// 		connect(runnable, &CalculateRunnable::RunnableFinished, this, [&]() {emit UpdateProssorbar(); }, Qt::QueuedConnection);
	}
	thread_pool.waitForDone(); // �ȴ������������
	emit CalculateFinished();
}
