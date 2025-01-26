#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class QThreadPool;

/**
 * ���̼߳�����
 * 1. �����ⲿ�����������������
 * 2. ����������ഫ���������
 * 3. ���½�����ʾ������
 */
class Calculate  : public QObject
{
	Q_OBJECT

public:
	Calculate(QObject *parent=nullptr);
	~Calculate();

public slots:
	void startCalculate(const CalculateInputStruct aInput); 
	void cancelCalculate();

signals:
	void calculateFinishedSignal(); 
	void updateProssorbarSignal();

private:
	QThreadPool* mThreadPool; //!< ���������ϼ����ʱ��ʹ��
};
