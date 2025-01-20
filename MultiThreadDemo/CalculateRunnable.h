#pragma once
#include <QRunnable>
#include <QObject>

/*
 *	QRunnable�̳�QObect��ʵ���źŲ�
 */
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

