#include "CalculateRunnable.h"
#include <QThread>

CalculateRunnable::CalculateRunnable()
{
	setAutoDelete(true);
}

CalculateRunnable::~CalculateRunnable()
{
	auto test_thread_id = QThread::currentThreadId();
	int i = 1;
}

void CalculateRunnable::run()
{
	QThread::msleep(500);
}
