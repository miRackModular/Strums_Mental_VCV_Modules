#include "mental.hpp"
#include <math.h>
#include "dsp.hpp"

Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	plugin->slug = "mental";
	plugin->name = "mental";

    createModel<MentalSubMixerWidget>(plugin, "MentalSubMixer", "Mental Sub Mixer");
    createModel<MentalMultsWidget>(plugin, "MentalMults", "Mental Mults");
    createModel<MentalMixerWidget>(plugin, "MentalMixer", "Mental Mixer");
    createModel<MentalTestWidget>(plugin, "MentalTest", "Mental Testbench");
    createModel<MentalFoldWidget>(plugin, "MentalFold", "Mental Wave Folder");
    createModel<MentalClipWidget>(plugin, "MentalClip", "Mental Wave Clipper");
    createModel<MentalGatesWidget>(plugin, "MentalGates", "Mental Gates");
    createModel<MentalABSwitchesWidget>(plugin, "MentalABSwitches", "Mental A/B Switches");
    createModel<MentalNoiseGateWidget>(plugin, "MentalNoiseGate", "Mental Noise Gate");
    createModel<MentalQuantiserWidget>(plugin, "MentalQuantiser", "Mental Quantiser");
    createModel<MentalChordWidget>(plugin, "MentalChord", "Mental Chord");
    createModel<MentalMuxesWidget>(plugin, "MentalMuxes", "Mental Muxes");
    createModel<MentalLogicWidget>(plugin, "MentalLogic", "Mental Logic");
    createModel<MentalButtonsWidget>(plugin, "MentalButtons", "Mental Buttons");
    createModel<MentalTemplateWidget>(plugin, "MentalTemplate", "Mental Template");
}