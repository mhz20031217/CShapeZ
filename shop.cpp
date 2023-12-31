#include "shop.h"

using std::to_string;

Shop::Shop(int &money, qreal &moneyRatio, qreal &itemRatio, int &nextW, int &nextH, QObject *parent)
  : money(money), moneyRatio(moneyRatio), itemRatio(itemRatio), nextW(nextW), nextH(nextH)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  QWidget *wMoneyRatio, *wItemRatio, *wNextMap;
  wMoneyRatio = new QWidget;
  wItemRatio = new QWidget;
  wNextMap = new QWidget;

  QHBoxLayout *lMoneyRatio = new QHBoxLayout(wMoneyRatio);
  QHBoxLayout *lItemRatio= new QHBoxLayout(wItemRatio);
  QHBoxLayout *lNextMap = new QHBoxLayout(wNextMap);

  QLabel *tMoneyRatio = new QLabel("Money Ratio\t$1000");
  QLabel *tItemRatio = new QLabel("Item Ratio\t$4000");
  QLabel *tNextMap = new QLabel("Next Map Size\t$2000");

  dMoneyRatio = new QLabel(to_string(moneyRatio).c_str());
  dItemRatio = new QLabel(to_string(itemRatio).c_str());
  dNextMap = new QLabel((to_string(nextW)+" x "+to_string(nextH)).c_str());

  QPushButton *bMoneyRatio = new QPushButton("Upgrade");
  QPushButton *bItemRatio = new QPushButton("Upgrade");
  QPushButton *bNextMap= new QPushButton("Upgrade");
  connect(bMoneyRatio, &QPushButton::clicked, this, &Shop::handleMoneyRatio);
  connect(bItemRatio, &QPushButton::clicked, this, &Shop::handleItemRatio);
  connect(bNextMap, &QPushButton::clicked, this, &Shop::handleNextMap);

  lMoneyRatio->addWidget(tMoneyRatio);
  lMoneyRatio->addWidget(dMoneyRatio);
  lMoneyRatio->addWidget(bMoneyRatio);
  lItemRatio->addWidget(tItemRatio);
  lItemRatio->addWidget(dItemRatio);
  lItemRatio->addWidget(bItemRatio);
  lNextMap->addWidget(tNextMap);
  lNextMap->addWidget(dNextMap);
  lNextMap->addWidget(bNextMap);

  layout->addWidget(wMoneyRatio);
  layout->addWidget(wItemRatio);
  layout->addWidget(wNextMap);
}

void Shop::handleMoneyRatio()
{
  if (money < 1000 || moneyRatio >= 4.0) {
    return;
  }
  moneyRatio += 0.1;
  dMoneyRatio->setText(to_string(moneyRatio).c_str());
  money -= 1000;
}

void Shop::handleItemRatio()
{
  if (money < 4000 || itemRatio >= 0.8) {
    return;
  }
  itemRatio += 0.1;
  dItemRatio->setText(to_string(itemRatio).c_str());
  money -= 4000;
}

void Shop::handleNextMap()
{
  if (money < 2000 || nextW >= 512) {
    return;
  }
  nextW *= 2; nextH *= 2;
  dNextMap->setText((to_string(nextW)+" x "+to_string(nextH)).c_str());
  money -= 2000;
}
