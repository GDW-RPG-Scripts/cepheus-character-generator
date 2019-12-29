#include "agingdialog.hh"
#include "ui_agingdialog.h"

#include "character.hh"

#include <QPushButton>

using namespace Cepheus::Character;

AgingDialog::AgingDialog(Character& character,
                         const std::vector<int>& mental,
                         const std::vector<int>& physical,
                         QWidget *parent) :
  QDialog(parent),
  mUi(new Ui::AgingDialog),
  mCharacter(character), mMental(mental), mPhysical(physical)
{
  mUi->setupUi(this);

  mUi->physicalButtonGroup1->setId(mUi->strRadioButton1, 0x01 << 0); // 0x01
  mUi->physicalButtonGroup1->setId(mUi->dexRadioButton1, 0x02 << 0); // 0x02
  mUi->physicalButtonGroup1->setId(mUi->endRadioButton1, 0x03 << 0); // 0x03

  mUi->physicalButtonGroup2->setId(mUi->strRadioButton2, 0x01 << 2); // 0x04
  mUi->physicalButtonGroup2->setId(mUi->dexRadioButton2, 0x02 << 2); // 0x08
  mUi->physicalButtonGroup2->setId(mUi->endRadioButton2, 0x03 << 2); // 0x0C

  mUi->physicalButtonGroup3->setId(mUi->strRadioButton3, 0x01 << 4); // 0x10
  mUi->physicalButtonGroup3->setId(mUi->dexRadioButton3, 0x02 << 4); // 0x20
  mUi->physicalButtonGroup3->setId(mUi->endRadioButton3, 0x03 << 4); // 0x30

  mUi->mentalButtonGroup->setId(mUi->intRadioButton, 0x01 << 6); // 0x40
  mUi->mentalButtonGroup->setId(mUi->eduRadioButton, 0x02 << 6); // 0x80

  mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

  mUi->strLineEdit->setText(QString::number(mCharacter.Str()));
  mUi->dexLineEdit->setText(QString::number(mCharacter.Dex()));
  mUi->endLineEdit->setText(QString::number(mCharacter.End()));
  mUi->intLineEdit->setText(QString::number(mCharacter.Int()));
  mUi->eduLineEdit->setText(QString::number(mCharacter.Edu()));

  mUi->strModLabel->setText(MOD(mCharacter.GetMod(Str)));
  mUi->dexModLabel->setText(MOD(mCharacter.GetMod(Dex)));
  mUi->endModLabel->setText(MOD(mCharacter.GetMod(End)));
  mUi->intModLabel->setText(MOD(mCharacter.GetMod(Int)));
  mUi->eduModLabel->setText(MOD(mCharacter.GetMod(Edu)));

  switch (physical.size()) {
    case 3:
      mUi->physicalLabel3->setEnabled(true);
      mUi->physicalStepsLabel3->setText(tr("%1 steps").arg(physical[2]));
      mUi->physicalStepsLabel3->setEnabled(true);
      mUi->strRadioButton3->setEnabled(true);
      mUi->dexRadioButton3->setEnabled(true);
      mUi->endRadioButton3->setEnabled(true);
    case 2:
      mUi->physicalLabel2->setEnabled(true);
      mUi->physicalStepsLabel2->setText(tr("%1 steps").arg(physical[1]));
      mUi->physicalStepsLabel2->setEnabled(true);
      mUi->strRadioButton2->setEnabled(true);
      mUi->dexRadioButton2->setEnabled(true);
      mUi->endRadioButton2->setEnabled(true);
    case 1:
      mUi->physicalLabel1->setEnabled(true);
      mUi->physicalStepsLabel1->setText(tr("%1 steps").arg(physical[0]));
      mUi->physicalStepsLabel1->setEnabled(true);
      mUi->strRadioButton1->setEnabled(true);
      mUi->dexRadioButton1->setEnabled(true);
      mUi->endRadioButton1->setEnabled(true);
    default:
      break;
  }

  switch (mental.size()) {
    case 1:
      mUi->mentalLabel->setEnabled(true);
      mUi->mentalStepsLabel->setText(tr("%1 steps").arg(mental[0]));
      mUi->mentalStepsLabel->setEnabled(true);
      mUi->intRadioButton->setEnabled(true);
      mUi->eduRadioButton->setEnabled(true);
    default:
      break;
  }
}

AgingDialog::~AgingDialog()
{
  delete mUi;
}

void
AgingDialog::Select(int id)
{
  mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
        (mPhysical.size() < 1 || (mPhysical.size() >= 1 && mUi->physicalButtonGroup1->checkedId() > 0)) &&
        (mPhysical.size() < 2 || (mPhysical.size() >= 2 && mUi->physicalButtonGroup2->checkedId() > 0)) &&
        (mPhysical.size() < 3 || (mPhysical.size() >= 3 && mUi->physicalButtonGroup3->checkedId() > 0)) &&
        (  mMental.size() < 1 ||   (mMental.size() >= 1 && mUi->   mentalButtonGroup->checkedId() > 0)));
}

int
AgingDialog::Selected() const
{
  return
      (mPhysical.size() < 1 ? 0 : mUi->physicalButtonGroup1->checkedId()) |
      (mPhysical.size() < 2 ? 0 : mUi->physicalButtonGroup2->checkedId()) |
      (mPhysical.size() < 3 ? 0 : mUi->physicalButtonGroup3->checkedId()) |
      (  mMental.size() < 1 ? 0 : mUi->   mentalButtonGroup->checkedId());
}
