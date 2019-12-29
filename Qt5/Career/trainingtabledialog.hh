#ifndef SKILLTABLEDIALOG_HH
#define SKILLTABLEDIALOG_HH

#include <QDialog>

namespace Ui {
  class SkillTableDialog;
}

namespace Cepheus
{
  namespace Character
  {
    class Character;
    class TrainingTable;

    class SkillTableDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit SkillTableDialog(Character&,
                                  const TrainingTable&, const TrainingTable&,
                                  const TrainingTable&, const TrainingTable&,
                                  int = 0, QWidget* = nullptr);

        void AddBenefits() const;

      private slots:
        void Select(int);

      private:
        Ui::SkillTableDialog* mUi;

        int mIndex;
        int mSkills;
        Character& mCharacter;
        const TrainingTable &mPersonal, &mService, &mSpecialist, &mAdvanced;
    };
  };
};

#endif // SKILLTABLEDIALOG_HH
