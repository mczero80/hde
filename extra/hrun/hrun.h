#include "ui_hrun.h"
#include <QProcess>

class hrun : public QDialog
{
  Q_OBJECT

 public:
  hrun(QWidget *parent = 0);

 public slots:
  void ok_clicked();
  void browse_clicked();
  void runStarted();
  void runError( QProcess::ProcessError );
  //void runFinished ( int, QProcess::ExitStatus );

 private:
  Ui::hrun ui;
  void saveChanges();
};
