#ifndef AGINGDIALOG_HH
#define AGINGDIALOG_HH

#include <QDialog>

namespace Ui {
  class AgingDialog;
}

namespace Cepheus
{
  namespace Character
  {
    class Character;

    class AgingDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit AgingDialog(Character&,
                             const std::vector<int>&,
                             const std::vector<int>&,
                             QWidget *parent = nullptr);
        ~AgingDialog();

        int Selected() const;

      private slots:
        void Select(int);

      private:
        Ui::AgingDialog *mUi;

        Character& mCharacter;
        std::vector<int> mMental;
        std::vector<int> mPhysical;
    };
  };
};

#endif // AGINGDIALOG_HH
