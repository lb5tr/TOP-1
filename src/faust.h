#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <memory>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

#include <plog/Log.h>

#include "module.h"

using FaustDSP = dsp;

enum OPTTYPE {
  FLOAT,
  BOOL
};

class FaustOptions : public UI {

  std::string boxPrefix;

public:

  module::Data *data;

  FaustOptions() {}
  FaustOptions(module::Data *data) : data (data) {}

  void openTabBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void openHorizontalBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void openVerticalBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void closeBox() override {
    uint last = 0;
    uint secLast = 0;
    std::string::size_type found = 0;
    while (found != std::string::npos) {
      secLast = last;
      last = found;
      found = boxPrefix.find("/", last + 1);
    }
    boxPrefix.erase(boxPrefix.begin() + secLast, boxPrefix.end());
  }
  void addHorizontalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    registerOption(label, zone, 0, min, max, 0, FLOAT);
  }

  void addVerticalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    addHorizontalBargraph(label, zone, min, max);
  }

  void addButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
  }

  void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
  }

  void addVerticalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  void addHorizontalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  void addNumEntry(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  virtual void registerOption(
    const char* label,
    FAUSTFLOAT* ptr,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step,
    OPTTYPE type) {

    // TODO: do something with the rest of this stuff
    bool matched = 0;
    std::string fullLabel = boxPrefix + label;
    for (auto &opt : data->fields) {
      if (opt.first == fullLabel) {
        opt.second->dataPtr = ptr;
        matched = 1;
        break;
      }
    }
    if (!matched) {
      LOGF << "Unmatched option " << fullLabel;
    }
  }
};

// Possibly this should extend Module
class FaustWrapper {

protected:

  FaustOptions opts;

  FAUSTFLOAT **inBuffer;
  FAUSTFLOAT **outBuffer;

public:

  dsp *fDSP;

  FaustWrapper() {};

  virtual ~FaustWrapper() {
    delete fDSP;
  };

  FaustWrapper(dsp *DSP, module::Data *data);

  virtual void process(uint nframes) {
    prepBuffers(nframes);
    fDSP->
      compute(nframes, inBuffer, outBuffer);
    postBuffers(nframes);
  }

protected:

  virtual void initBuffers();

  /**
   * Copy the relevant data into inBuffer
   */
  virtual void prepBuffers(uint nframes);

  /**
   * Put the data back into the chain
   */
  virtual void postBuffers(uint nframes);
};
