#include "base.h"
#include "mainui.h"
#include "utils.h"
#include "../globals.h"
#include <pangomm/init.h>

#include <thread>

void MainUI::init() {
  auto& self = getInstance();

  Pango::init();

  self.uiThread = std::thread(MainUI::mainRoutine);
  self.uiThread.join();
}

bool MainUI::draw(const ui::ContextPtr& cr) {
  using namespace drawing;

  cr->rectangle(0, 0, WIDTH, HEIGHT);
  cr->set_source(COLOUR_BLACK);
  cr->fill();
  return getInstance().currentScreen->draw(cr);
}

bool MainUI::keypress(ui::Key key) {
  if (globKeyPre(key)) return true;
  if (currentScreen->keypress(key)) return true;
  return globKeyPost(key);
}

bool MainUI::globKeyPre(ui::Key key) {
  using namespace ui;
  switch (key) {
  case QUIT:
    GLOB.running = false;
    break;
  default:
    return false;
  }
  return true;
}