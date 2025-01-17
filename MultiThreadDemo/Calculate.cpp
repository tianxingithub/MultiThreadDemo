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
	for (int i = 0; i < 20; i++) 
	{
		thread_pool.start(new CalculateRunnable);
	}
	thread_pool.waitForDone(); // �ȴ������������
	emit CalculateFinished();
}
