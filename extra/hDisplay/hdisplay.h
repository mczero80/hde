
#include "ui_hdisplay.h"

class hDisplay : public QDialog
{
  Q_OBJECT

 public:
  hDisplay(QWidget *parent = 0);

 public slots:
  void bg_clicked();
  void apply_clicked();
  void displayChanged(const QString& );
  void browse_clicked();
  void imageSelected(QListWidgetItem * );

 private:
  void applyDisplay();
  void applyApearance();
  void readCurentDir();
  void selCurentImg();
  void drawBgBtn();
  void drawImage();

  Ui::hDisplay ui;
 };
