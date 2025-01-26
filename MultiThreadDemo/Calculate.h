#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class QThreadPool;

/**
 * 多线程计算类
 * 1. 解析外部参数，遍历计算情况
 * 2. 负责给任务类传递输入参数
 * 3. 更新界面显示进度条
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
	QThreadPool* mThreadPool; //!< 用于在中上计算的时候使用
};
