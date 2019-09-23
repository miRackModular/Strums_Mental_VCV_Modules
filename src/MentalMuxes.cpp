///////////////////////////////////////////////////
//
//   Multiplexers VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

struct MentalMuxes : Module {
	enum ParamIds {
		NUM_PARAMS
	};  
	enum InputIds {		
		INPUT_1A,
    INPUT_2A,
    SELECT_A,
    INPUT_1B,
    INPUT_2B,
    SELECT_B, 
    INPUT_1C,
    INPUT_2C,
    INPUT_3C,
    INPUT_4C,
    SELECT_C,     
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_A,
    OUTPUT_B,
    OUTPUT_C,        
		NUM_OUTPUTS
	};
  enum LightIds {
    LEVEL_LED_A1,
    LEVEL_LED_A2,
    LEVEL_LED_B1,
    LEVEL_LED_B2,
    LEVEL_LED_C1,
    LEVEL_LED_C2,
    LEVEL_LED_C3,
    LEVEL_LED_C4,    
    NUM_LIGHTS
  };
  
	MentalMuxes() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);}
	void process(const ProcessArgs& args) override;
};

void MentalMuxes::process(const ProcessArgs& args)
{
  
  float signal_in_a1 = inputs[INPUT_1A].getVoltage();
  float signal_in_a2 = inputs[INPUT_2A].getVoltage();
  float select_a = inputs[SELECT_A].getVoltage();
  
  if (select_a > 0.0 )
  {
    outputs[OUTPUT_A].setVoltage(signal_in_a2);    
    lights[LEVEL_LED_A2].value = std::abs((signal_in_a2 / 3));
    lights[LEVEL_LED_A1].value = 0.0;
  }
  else
  {
    outputs[OUTPUT_A].setVoltage(signal_in_a1);    
    lights[LEVEL_LED_A1].value = std::abs((signal_in_a1 / 3));
    lights[LEVEL_LED_A2].value = 0.0;
  }
  float signal_in_b1 = inputs[INPUT_1B].getVoltage();
  float signal_in_b2 = inputs[INPUT_2B].getVoltage();
  float select_b = inputs[SELECT_B].getVoltage();
  
  if (select_b > 0.0 )
  {
    outputs[OUTPUT_B].setVoltage(signal_in_b2);    
    lights[LEVEL_LED_B2].value = std::abs((signal_in_b2 / 3));
    lights[LEVEL_LED_B1].value = 0.0;
  }
  else
  {
    outputs[OUTPUT_B].setVoltage(signal_in_b1);    
    lights[LEVEL_LED_B1].value = std::abs((signal_in_b1 / 3));
    lights[LEVEL_LED_B2].value = 0.0;
  }
  
  float signal_in_c1 = inputs[INPUT_1C].getVoltage();
  float signal_in_c2 = inputs[INPUT_2C].getVoltage();
  float signal_in_c3 = inputs[INPUT_3C].getVoltage();
  float signal_in_c4 = inputs[INPUT_4C].getVoltage();
  float select_c = inputs[SELECT_C].getVoltage();
  int selector = round(std::abs(select_c));
  if (selector > 3) selector = 3;
    
  if (selector == 0 )
  {
    outputs[OUTPUT_C].setVoltage(signal_in_c1);    
    lights[LEVEL_LED_C1].value = std::abs((signal_in_c1 / 3));
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;
       
  }
  if (selector == 1 )
  {
    outputs[OUTPUT_C].setVoltage(signal_in_c2);    
    lights[LEVEL_LED_C2].value = std::abs((signal_in_c2 / 3));
    lights[LEVEL_LED_C1].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;
  }
  if (selector == 2 )
  {
    outputs[OUTPUT_C].setVoltage(signal_in_c3);    
    lights[LEVEL_LED_C3].value = std::abs((signal_in_c3 / 3));
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;    
  }
  if (selector == 3 )
  {
    outputs[OUTPUT_C].setVoltage(signal_in_c4);    
    lights[LEVEL_LED_C4].value = std::abs((signal_in_c4 / 3));
    lights[LEVEL_LED_C1].value = 0.0;
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
struct MentalMuxesWidget : ModuleWidget {
  MentalMuxesWidget(MentalMuxes *module){

    setModule(module);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MentalMuxes.svg")));

	int group_offset = 90;
  addInput(createInput<GateInPort>(Vec(3, 75), module, MentalMuxes::SELECT_A));  
	addInput(createInput<InPort>(Vec(3, 25), module, MentalMuxes::INPUT_1A));
  addInput(createInput<InPort>(Vec(3, 50), module, MentalMuxes::INPUT_2A));  
  
  addOutput(createOutput<OutPort>(Vec(33, 75), module, MentalMuxes::OUTPUT_A));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41, 32), module, MentalMuxes::LEVEL_LED_A1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41, 58), module, MentalMuxes::LEVEL_LED_A2));
  
  addInput(createInput<GateInPort>(Vec(3, group_offset + 75), module, MentalMuxes::SELECT_B));  
	addInput(createInput<InPort>(Vec(3, group_offset + 25), module, MentalMuxes::INPUT_1B));
  addInput(createInput<InPort>(Vec(3, group_offset + 50), module, MentalMuxes::INPUT_2B));  
  
  addOutput(createOutput<OutPort>(Vec(33,group_offset + 75), module, MentalMuxes::OUTPUT_B));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset + 32), module, MentalMuxes::LEVEL_LED_B1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset + 58), module, MentalMuxes::LEVEL_LED_B2));
  
  addInput(createInput<CVInPort>(Vec(3, group_offset * 2 + 125), module, MentalMuxes::SELECT_C));  
	addInput(createInput<InPort>(Vec(3, group_offset * 2 + 25), module, MentalMuxes::INPUT_1C));
  addInput(createInput<InPort>(Vec(3, group_offset * 2 + 50), module, MentalMuxes::INPUT_2C));
  addInput(createInput<InPort>(Vec(3, group_offset * 2 + 75), module, MentalMuxes::INPUT_3C));
  addInput(createInput<InPort>(Vec(3, group_offset * 2 + 100), module, MentalMuxes::INPUT_4C));    
  
  addOutput(createOutput<OutPort>(Vec(33,group_offset * 2 + 125), module, MentalMuxes::OUTPUT_C));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 32), module, MentalMuxes::LEVEL_LED_C1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 58), module, MentalMuxes::LEVEL_LED_C2));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 82), module, MentalMuxes::LEVEL_LED_C3));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 108), module, MentalMuxes::LEVEL_LED_C4));
	  
}
};

Model *modelMentalMuxes = createModel<MentalMuxes, MentalMuxesWidget>("MentalMuxes");