#include "Calculate.h"
#include <QThread>
#include <QThreadPool>

#include "CalculateRunnable.h"

Calculate::Calculate(QObject* parent/*=nullptr*/)
{
	mThreadPool = nullptr;
}

Calculate::~Calculate()
{

}

void Calculate::startCalculateSlot(const CalculateInputStruct aInput)
{
	auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͽ����ࡢ�������id�Ƿ���ͬ

	mThreadPool = new QThreadPool();
	mThreadPool->setMaxThreadCount(aInput.threadMaxCount); // �����̳߳ص�����߳���Ϊ1
	for (int i = 0; i < aInput.calculateCount; i++)
	{
		CalculateRunnable* runnable = new CalculateRunnable;
		runnable->setAutoDelete(true); // ��������������Զ�ɾ��
		mThreadPool->start(runnable);

		//! ������Ӧ��ʽΪ��Ϣ����ʱ������emit CalculateFinished(); ������Ӧ��������ʹ��ֱ����Ӧ
		connect(runnable, &CalculateRunnable::RunnableFinished, this, [&]() {emit UpdateProssorbar(); }, Qt::DirectConnection); 		
	}
	mThreadPool->waitForDone(); // �ȴ������������
	emit CalculateFinished();

	delete mThreadPool;
	mThreadPool = nullptr;
}

void Calculate::cancelCalculateSlot()
{
	if (mThreadPool)
	{
		mThreadPool->clear(); // ����̳߳�
// 		delete mThreadPool;
// 		mThreadPool = nullptr;
	}	
}
