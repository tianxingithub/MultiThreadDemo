#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class Calculate  : public QObject
{
	Q_OBJECT

public:
	Calculate(QObject *parent=nullptr);
	~Calculate();

public slots:
	void startCalculateSlot(const CalculateInputStruct aInput);

signals:
	void CalculateFinished(); //!< 跨线程通信
};
