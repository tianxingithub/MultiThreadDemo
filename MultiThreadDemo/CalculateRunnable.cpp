#include "CalculateRunnable.h"
#include <QThread>

CalculateRunnable::~CalculateRunnable()
{
	auto test_thread_id = QThread::currentThreadId();
	int i = 1;
}

void CalculateRunnable::run()
{
	QThread::msleep(500);

	emit runnableFinishedSignal();
}
