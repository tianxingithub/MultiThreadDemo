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
	void CalculateFinished(); //!< 跨线程通信
	void UpdateProssorbar();

private:
	QThreadPool* mThreadPool; //!< 用于在中上计算的时候使用
};
