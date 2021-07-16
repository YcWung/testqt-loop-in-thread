#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <thread>
#include <chrono>
#include <QDebug>

MainWindow::MainWindow() : QMainWindow(), ui(new Ui_MainWindow) {
  ui->setupUi(this);
  thread = new QThread(this);
  service  = new Service();
  service->moveToThread(thread);
  connect(ui->actionStart, &QAction::triggered, this, &MainWindow::Start);
  connect(ui->actionPause, &QAction::triggered, this, &MainWindow::Pause);
  connect(ui->actionStop, &QAction::triggered, this, &MainWindow::Stop);
  // connect(ui->actionStart, &QAction::triggered, service, &Service::Start);
  // connect(ui->actionPause, &QAction::triggered, service, &Service::Pause);
  // connect(ui->actionStop, &QAction::triggered, service, &Service::Stop);
  connect(ui->actionClear, &QAction::triggered, this, &MainWindow::Clear);
  connect(service, &Service::NewData, this, &MainWindow::GetNewData);
  connect(thread, &QThread::finished, service, &QObject::deleteLater);
  thread->start();
}

void MainWindow::Start() {
  QMetaObject::invokeMethod(service, "Start", Qt::QueuedConnection);
}
void MainWindow::Stop() {
  QMetaObject::invokeMethod(service, "Stop", Qt::BlockingQueuedConnection);
  Clear();
}
void MainWindow::Pause() {
  QMetaObject::invokeMethod(service, "Pause", Qt::BlockingQueuedConnection);
}

void MainWindow::Clear() {
  ui->centralwidget->clear();
}

void MainWindow::GetNewData(QString qs) { ui->centralwidget->setPlainText(qs); }

MainWindow::~MainWindow() {
  QMetaObject::invokeMethod(service, "Stop", Qt::BlockingQueuedConnection);
  thread->quit();
  thread->wait();
}

Service::Service(QObject *parent) : QObject(parent), state(0) {}

void Service::Start() {
  if (state == 0) {
    state = 1;
    Loop();
  }
}

void Service::Pause() {
  if (state == 1) {
    state = 2;
  } else if (state == 2) {
    state = 1;
  }
}

void Service::Stop() {
  state = 0;
}

void Service::Loop() {
  QString qs;
  int count = 1;
  while(1) {
    if (state == 0) {
      break;
    } else if (state == 1) {
      qs.clear();
      if (count > 100) {
        count = 1;
      }
      for (int i_c = 0; i_c < count; ++i_c) {
        qs.append(std::to_string(i_c).c_str());
        qs.append(":");
        qs.append(" ");
        for (int i = 0; i < 26*2; ++i) {
          qs.append('A' + i);
        }
        qs.append("\n");
      }
      ++count;
      emit NewData(qs);
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    else if (state == 2) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
  }
}
