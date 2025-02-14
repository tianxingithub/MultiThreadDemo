#include "MultiThreadDemo.h"
#include "ui_MultiThreadDemo.h"

#include <QThread>
#include <QDateTime>
#include "Calculate.h"
#include "CalculateInputStruct.h"

namespace ThreadDemo
{    

    MultiThreadDemo::MultiThreadDemo(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::MultiThreadDemoClass())
    {
        m_CalculateStatus = false;
        ui->setupUi(this);

        connect(ui->btn_calculate,        &QPushButton::clicked, this, &MultiThreadDemo::btn_calculate_slot);
        connect(ui->btn_cancel_calculate, &QPushButton::clicked, this, &MultiThreadDemo::btn_cancel_calculate_slot);
        connect(ui->btn_test_multi_data,  &QPushButton::clicked, this, &MultiThreadDemo::btn_test_multi_data_slot);

		m_Thread = new QThread();
		m_Calculate = new Calculate();
        m_Calculate->moveToThread(m_Thread); // �ı�mCalculate���߳�������ϵ��������������߳���ִ��

        //! �ͷŶѿռ���Դ�������ڴ�й¶
        connect(m_Thread, &QThread::finished, m_Thread,    &QObject::deleteLater);
        connect(m_Thread, &QThread::finished, m_Calculate, &QObject::deleteLater);

        //! ע�⣺��ʹ�ÿ��߳�ͨ��ʱ��������ҪΪԪ�������ͣ�������Ҳ���Ͳ������������й� meta ʲô�ģ�
        qRegisterMetaType<CalculateInputStruct>("CalculateInputStruct"); // ���ṹ�� CalculateInputStruct ע��ΪԪ��������

        //! ���������źŲۣ����ڴ����߳�ִ�вۺ����������    
        connect(this, &MultiThreadDemo::startCalculateSignal,  m_Calculate, &Calculate::startCalculate,  Qt::QueuedConnection);         // Ĭ��ʹ��Qt::QueuedConnection����֤�ۺ�����ִ��˳��
        connect(this, &MultiThreadDemo::cancleCalculateSignal, m_Calculate, &Calculate::cancelCalculate, Qt::DirectConnection);

        connect(m_Calculate, &Calculate::calculateFinishedSignal, this, &MultiThreadDemo::calculate_finished_slot, Qt::QueuedConnection); // ���������ʾ��Ϣ
        connect(m_Calculate, &Calculate::updateProssorbarSignal,  this, &MultiThreadDemo::update_prossorbar_slot,  Qt::QueuedConnection);   // ÿ����һ����һ�����񣬸��½��������

        m_Thread->start(); // �����̣߳��߳�Ĭ�Ͽ����¼�ѭ���������߳��������¼�ѭ��״̬

        //!@ ������
//         m_Calculate->directDoSomeThing(); // ���������߳���ִ��
        connect(this, &MultiThreadDemo::doSomeThingSignal, m_Calculate, &Calculate::doSomeThingSlot, Qt::QueuedConnection);
        connect(this, &MultiThreadDemo::directDoSomeThingSignal, m_Calculate, &Calculate::directDoSomeThing, Qt::QueuedConnection);
        emit doSomeThingSignal();
        emit directDoSomeThingSignal();

        connect(this, &MultiThreadDemo::testMultiDataSignal, m_Calculate, &Calculate::testtMultiDataSlot, Qt::DirectConnection);
    }

    MultiThreadDemo::~MultiThreadDemo()
    {
        delete ui;
    }

    void MultiThreadDemo::btn_calculate_slot()
    {
        auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͼ������id�Ƿ���ͬ

        //! �������
        auto max_count_str = ui->line_edit_thread_max_count->text();
        if (max_count_str == "" || max_count_str.toInt() <= 0)
        {
            ui->calculate_message->append(u8"��������߳�������Ҫ����0��");
            return;
        }

        auto calculate_count_str = ui->line_edit_calculate_count->text();
        if (calculate_count_str == "" || calculate_count_str.toInt() <= 0)
        {
            ui->calculate_message->append(u8"���������Ҫ����0��");
            return;
        }

        //! �ж��Ƿ��ڼ���
        if (m_CalculateStatus)
        {
            ui->calculate_message->append(u8"���ڼ��㣬���Ժ�...");
            return;
        }
        m_CalculateStatus = true;

        //! ��Ӽ�����Ϣ
        QString start_msg =
            QString(u8"���μ������ %1�����߳���Ҫʱ��Ϊ %3s����ǰ�����߳����� %2\n")
            .arg(ui->line_edit_calculate_count->text())
            .arg(ui->line_edit_thread_max_count->text())
            .arg(ui->line_edit_calculate_count->text().toInt() * 0.5);
        start_msg += u8"��ʼ���㣬��ǰʱ�䣺" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        ui->calculate_message->append(start_msg);

        //! �趨�������
        CalculateInputStruct input;
        input.msg = "start";
        input.threadMaxCount = max_count_str.toInt();
        input.calculateCount = calculate_count_str.toInt();

        ui->calculate_prossorbar->reset();
        ui->calculate_prossorbar->setRange(0, input.calculateCount);
        ui->calculate_prossorbar->setValue(0);

        emit startCalculateSignal(input);
        m_StartTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zz");
    }

    void MultiThreadDemo::btn_cancel_calculate_slot()
    {
        emit cancleCalculateSignal();
    }

	void MultiThreadDemo::btn_test_multi_data_slot()
	{
        QVector<double> xDatas,yDatas;
        for (int i = 0; i < 10; i++)
        {
            xDatas.push_back(i);
            yDatas.push_back(i*i);
        }

        QVector<QStringList> datas;
        for (int i = 0; i < 10; i++)
        {
            QStringList row;
            row.push_back(QString::number(i));
            row.push_back(QString::number(i*i));
            datas.push_back(row);
        }

//         emit testMultiDataSignal(xDatas, yDatas);
        emit testMultiDataSignal(datas);
	}

	void MultiThreadDemo::calculate_finished_slot()
    {
        m_CalculateStatus = false;
        QString finished_msg = u8"������ɣ���ǰʱ�䣺" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        ui->calculate_message->append(finished_msg);
        ui->calculate_message->append(u8"=========================");
        ui->calculate_message->append("");
        ui->calculate_message->append("");

        int i = 1;
    }

    void MultiThreadDemo::update_prossorbar_slot()
    {
        auto cur_num = ui->calculate_prossorbar->value();
        if (cur_num < ui->calculate_prossorbar->maximum())
        {
            ui->calculate_prossorbar->setValue(cur_num + 1);
        }
    }

}