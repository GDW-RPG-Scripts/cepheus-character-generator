#ifndef DRAFTORDRIFTDIALOG_HH
#define DRAFTORDRIFTDIALOG_HH

#include <QDialog>

namespace Ui {
  class DraftOrDriftDialog;
}

namespace Cepheus
{
  namespace Character
  {
    class Career;

    class DraftOrDriftDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit DraftOrDriftDialog(QWidget* = nullptr);
        ~DraftOrDriftDialog();

        bool HasSelection() const;

        const Career* GetCareer(bool&) const;

      public slots:
        void Select(int);

      private:
        Ui::DraftOrDriftDialog* mUi;

        int mSelected;
    };
  };
};

#endif // DRAFTORDRIFTDIALOG_HH
