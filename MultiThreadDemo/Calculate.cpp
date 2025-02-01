#include "Calculate.h"
#include <QThread>
#include <QThreadPool>

#include "CalculateRunnable.h"

Calculate::Calculate(QObject* parent/*=nullptr*/)
{
	m_ThreadPool = nullptr;
}

Calculate::~Calculate()
{

}

void Calculate::startCalculate(const CalculateInputStruct aInput)
{
	auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͽ����ࡢ�������id�Ƿ���ͬ

	m_ThreadPool = new QThreadPool();
	m_ThreadPool->setMaxThreadCount(aInput.threadMaxCount); // �����̳߳ص�����߳���Ϊ1
	for (int i = 0; i < aInput.calculateCount; i++)
	{
		CalculateRunnable* runnable = new CalculateRunnable;
		runnable->setAutoDelete(true); // ��������������Զ�ɾ��
		m_ThreadPool->start(runnable);

		//! ������Ӧ��ʽΪ��Ϣ����ʱ������emit CalculateFinished(); ������Ӧ��������ʹ��ֱ����Ӧ
		connect(runnable, &CalculateRunnable::runnableFinishedSignal, this, [&]() {emit updateProssorbarSignal(); }, Qt::DirectConnection); 		
	}
	m_ThreadPool->waitForDone(); // �ȴ������������
	emit calculateFinishedSignal();

	delete m_ThreadPool;
	m_ThreadPool = nullptr;
}

void Calculate::cancelCalculate()
{
	if (m_ThreadPool)
	{
		m_ThreadPool->clear(); // ����̳߳�
// 		delete mThreadPool;
// 		mThreadPool = nullptr;
	}	
}
