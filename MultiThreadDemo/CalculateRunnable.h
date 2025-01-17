#pragma once
#include <QRunnable>

class CalculateRunnable : public QRunnable
{
public:
	CalculateRunnable();
	~CalculateRunnable();
protected:
	void run() override;
};

