#include "mainwindow.h"
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameState(scene, this)){
  setCentralWidget(view);

  QMenu *fileMenu = menuBar()->addMenu("&File");
  QMenu *helpMenu = menuBar()->addMenu("&Help");

  {
    QAction *newGameAction = fileMenu->addAction("&New Game");
    newGameAction->setShortcut(Qt::CTRL | Qt::Key_N);
    QAction *pauseAction = fileMenu->addAction("&Pause/Break");
    pauseAction->setShortcut(Qt::CTRL | Qt::Key_P);
    connect(pauseAction, &QAction::triggered, game, &GameState::pause);
    QAction *loadAction = fileMenu->addAction("&Load");
    loadAction->setShortcut(Qt::CTRL | Qt::Key_L);
    QAction *saveAction = fileMenu->addAction("&Save");
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    QAction *screenshotAction = fileMenu->addAction("Screenshot");
    QAction *quitAction = fileMenu->addAction("&Quit");
    quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);
  }

  {
    QAction *manualAction = helpMenu->addAction("&Manual");
    QAction *aboutAction = helpMenu->addAction("&About");
  }

  QToolBar *machineBar = new QToolBar("Machines", this);
  addToolBar(machineBar);
  QAction *miner = machineBar->addAction("Miner");
  //  connect(miner, &QAction::triggered, game, &GameState::selectMachine);
  miner->setShortcut(Qt::Key_1);
  QAction *belt = machineBar->addAction("Belt");
  belt->setShortcut(Qt::Key_2);
  QAction *cutter = machineBar->addAction("Cutter");
  cutter->setShortcut(Qt::Key_3);
  QAction *mixer = machineBar->addAction("Mixer");
  mixer->setShortcut(Qt::Key_4);
  QAction *rotator = machineBar->addAction("Rotator");
  rotator->setShortcut(Qt::Key_5);
  QAction *trash = machineBar->addAction("Trash");
  trash->setShortcut(Qt::Key_6);

  machines = {miner, belt, cutter, mixer, rotator, trash};
  for (auto x : machines) {
    x->setCheckable(true);
    connect(x, &QAction::triggered, this, &MainWindow::handleMachineChange);
  }
}

MainWindow::~MainWindow() {}

void MainWindow::handleMachineChange(bool checked) {
  if (!checked) {
    game->selectMachine(0);
    for (auto x: machines) {
      x->setChecked(false);
    }
  } else {
    for (int i = 0; i < machines.size(); i ++) {
      if (machines[i] == sender()) {
        assert(machines[i]->isChecked());
        game->selectMachine(i + 1); // #TODO: better solution
      } else {
        machines[i]->setChecked(false);
      }
    }
  }
}