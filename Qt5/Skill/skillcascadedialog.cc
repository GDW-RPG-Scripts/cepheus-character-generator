#include "skillcascadedialog.hh"
#include "ui_skillcascadedialog.h"

#include <map>

using namespace Cepheus::Character;

SkillCascadeDialog::SkillCascadeDialog(SkillCode skill, QWidget *parent) :
  QDialog(parent),
  mUi(new Ui::SkillCascadeDialog), mSelected(nullptr)
{
  mUi->setupUi(this);

  QString name = Skill::Name(skill);
  QList<QTreeWidgetItem*> items =
      mUi->treeWidget->findItems(name, Qt::MatchFixedString);

  if(items.size() == 0) {
    QTreeWidgetItem* vehicle =
        mUi->treeWidget->findItems("Vehicle", Qt::MatchFixedString)[0];
    for (int i = 0; i < vehicle->childCount(); i++) {
      QTreeWidgetItem* item = vehicle->child(i);
      if(item->text(0) == name) {
        items.append(item);
        break;
      }
    }
  }

  for (QTreeWidgetItem* item : items) {
    for(QTreeWidgetItem* p = item->parent(); p; p = p->parent()) {
      p->setFlags(Qt::ItemIsEnabled);
      p->setExpanded(true);
    }

    EnableChild(item);
  }
}

SkillCascadeDialog::~SkillCascadeDialog()
{
  delete mUi;
}

void
SkillCascadeDialog::EnableChild(QTreeWidgetItem* item)
{
  if(item->childCount() > 0) {
    item->setExpanded(true);
    item->setFlags(Qt::ItemIsEnabled);
    for(int i = 0; i < item->childCount(); i++)
      EnableChild(item->child(i));
  } else {
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
  }
}

void
SkillCascadeDialog::Select()
{
  QList<QTreeWidgetItem*> selection = mUi->treeWidget->selectedItems();

  if(selection.length() == 1)
    mSelected = selection[0];
}

void
SkillCascadeDialog::SelectAndAccept()
{
  Select();
  accept();
}

SkillCode
SkillCascadeDialog::Selection() const
{
  if(mSelected)
    return Skill::Code(mSelected->text(0));

  return SkillCode::NO_SKILL;
}
