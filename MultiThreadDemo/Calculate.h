#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class QThreadPool;

class Calculate  : public QObject
{
	Q_OBJECT

public:
	Calculate(QObject *parent=nullptr);
	~Calculate();

public slots:
	void startCalculateSlot(const CalculateInputStruct aInput);
	void cancelCalculateSlot();

signals:
	void CalculateFinished(); //!< ���߳�ͨ��
	void UpdateProssorbar();

private:
	QThreadPool* mThreadPool; //!< ���������ϼ����ʱ��ʹ��
};
