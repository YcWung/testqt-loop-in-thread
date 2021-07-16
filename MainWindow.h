#include <QThread>
#include <QMainWindow>

class Ui_MainWindow;

class Service : public QObject {
  Q_OBJECT
public:
  Service(QObject* parent = nullptr);
public slots:
  void Start();
  void Stop();
  void Pause();
signals:
  void NewData(QString);
private:
  void Loop();
  int state;
};

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();
  void GetNewData(QString);
  void Start();
  void Pause();
  void Stop();
  void Clear();
private:
  Ui_MainWindow* ui;
  Service* service;
  QThread* thread;
};
