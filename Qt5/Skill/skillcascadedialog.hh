#ifndef WEAPONSKILLDIALOG_HH
#define WEAPONSKILLDIALOG_HH

#include "skill.hh"

#include <QDialog>

namespace Ui {
  class SkillCascadeDialog;
}

class QTreeWidgetItem;

namespace Cepheus
{
  namespace Character
  {
    class SkillCascadeDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit SkillCascadeDialog(SkillCode, QWidget *parent = nullptr);
        ~SkillCascadeDialog();

        SkillCode Selection() const;

      private slots:
        void Select();
        void SelectAndAccept();

      private:
        void EnableChild(QTreeWidgetItem*);

        Ui::SkillCascadeDialog *mUi;

        QTreeWidgetItem* mSelected;
    };
  };
};

#endif // WEAPONSKILLDIALOG_HH
