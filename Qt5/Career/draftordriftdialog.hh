/**
 * Cepheus Character Generator, an RPG character generator for the Cepheus
 * Engine and derived RPG systems.
 *
 * Copyright (C) 2019 Michael N. Henry <mike.henry@mikehenry.se>
 *
 * This file is part of the Cepheus Character Generator.
 *
 * Cepheus Character Generator is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * Cepheus Character Generator is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have
 * received a copy of the GNU General Public License along with Cepheus
 * Character Generator. If not, see <http://www.gnu.org/licenses/>.
 */

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

        const Career* GetCareer(int&) const;

      public slots:
        void Select(int);

      private:
        Ui::DraftOrDriftDialog* mUi;

        int mSelected;
    };
  };
};

#endif // DRAFTORDRIFTDIALOG_HH
