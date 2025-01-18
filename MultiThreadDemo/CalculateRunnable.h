#pragma once
#include <QRunnable>
#include <QObject>

class CalculateRunnable : /*public QObject,*/ public QRunnable
{
public:
	~CalculateRunnable();
signals:
// 	void RunnableFinished();
protected:
	void run() override;
};

