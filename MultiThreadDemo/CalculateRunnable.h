#pragma once
#include <QRunnable>
#include <QObject>

class CalculateRunnable : public QObject, public QRunnable
{
	Q_OBJECT
public:
	~CalculateRunnable();
signals:
	void RunnableFinished();
protected:
	void run() override;
};

