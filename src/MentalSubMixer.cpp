///////////////////////////////////////////////////
//
//   Mental Plugin
//   Sub Mixer VCV Module
//   Built from fundamental VCMixer 
//
//   Strum 2017-19
//   strum@softhome.net
//
///////////////////////////////////////////////////

#include "mental.hpp"

struct MentalSubMixer : Module
{
	enum ParamIds
	{
		MIX_PARAM,
		CH_VOL_PARAM,
		CH_PAN_PARAM = CH_VOL_PARAM + 4,
		NUM_PARAMS = CH_PAN_PARAM + 4
	};
	enum InputIds
	{
		MIX_CV_INPUT,
		CH_INPUT,
		CH_VOL_INPUT = CH_INPUT + 4,
		CH_PAN_INPUT = CH_VOL_INPUT + 4,
		NUM_INPUTS = CH_PAN_INPUT + 4
	};
	enum OutputIds
	{
		MIX_OUTPUT_L, MIX_OUTPUT_R,
		CH_OUTPUT,
		NUM_OUTPUTS = CH_OUTPUT + 4
	};

	float channel_ins[4];
	float pan_cv_ins[4];
	float pan_positions[4]; 
	float channel_outs_l[4];
	float channel_outs_r[4];
	float left_sum = 0.0;
	float right_sum = 0.0;
	
	MentalSubMixer()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
		configParam(MentalSubMixer::MIX_PARAM, 0.0, 1.0, 0.5, "");
		for (int i = 0; i < 4; ++i)
		{
			configParam(MentalSubMixer::CH_VOL_PARAM + i, 0.0, 1.0, 0.0, "");
			configParam(MentalSubMixer::CH_PAN_PARAM + i, 0.0, 1.0, 0.5, "");
		}
	};

	void process(const ProcessArgs& args) override;
};


void MentalSubMixer::process(const ProcessArgs& args)
{
	left_sum = 0.0;
	right_sum = 0.0;

	for (int i = 0 ; i < 4 ; i++)
	{
		channel_ins[i] = inputs[CH_INPUT + i].getVoltage() * params[CH_VOL_PARAM + i].getValue() * clamp(inputs[CH_VOL_INPUT + i].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
		
    	pan_cv_ins[i] = inputs[CH_PAN_INPUT + i].getVoltage()/5;
    	pan_positions[i] = pan_cv_ins[i] + params[CH_PAN_PARAM + i].getValue();   
    	if (pan_positions[i] < 0) pan_positions[i] = 0;
    	if (pan_positions[i] > 1) pan_positions[i] = 1;
    	channel_outs_l[i]= channel_ins[i] * (1-pan_positions[i])* 2;
    	channel_outs_r[i]= channel_ins[i] * pan_positions[i] * 2;      
        
    	left_sum += channel_outs_l[i];
    	right_sum += channel_outs_r[i];
    }
    
    float mix_l = left_sum * params[MIX_PARAM].getValue() * clamp(inputs[MIX_CV_INPUT].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
    float mix_r = right_sum * params[MIX_PARAM].getValue() * clamp(inputs[MIX_CV_INPUT].normalize(10.0f) / 10.0f, 0.0f, 1.0f);

    outputs[MIX_OUTPUT_L].setVoltage(mix_l);
    outputs[MIX_OUTPUT_R].setVoltage(mix_r);

   	outputs[CH_OUTPUT ].setVoltage(channel_ins[0]);
	outputs[CH_OUTPUT + 1].setVoltage(channel_ins[1]);
	outputs[CH_OUTPUT + 2].setVoltage(channel_ins[2]);
	outputs[CH_OUTPUT + 3].setVoltage(channel_ins[3]);
}

////////////////////////////////////////////////////////////
struct MentalSubMixerWidget : ModuleWidget
{
	MentalSubMixerWidget(MentalSubMixer *module)
	{
		setModule(module);
  		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MentalSubMixer.svg")));

	    int stripwidth = 28;
		// master section
	  	addOutput(createOutput<OutPort>(Vec( 6 + stripwidth, 20), module, MentalSubMixer::MIX_OUTPUT_L));
		addOutput(createOutput<OutPort>(Vec( 6 + stripwidth * 2 , 20), module, MentalSubMixer::MIX_OUTPUT_R));
		addParam(createParam<LrgKnob>(Vec( 9 + stripwidth , 50), module, MentalSubMixer::MIX_PARAM));
		addInput(createInput<CVInPort>(Vec( 6 + stripwidth * 1.5 , 100), module, MentalSubMixer::MIX_CV_INPUT));
		// channel strips
		for (int i = 0 ; i < 4 ; i++)
		{
			// input
			addInput(createInput<InPort>(Vec( 6 + stripwidth * i , box.size.y - 182 ), module, MentalSubMixer::CH_INPUT + i));
			// gain
			addParam(createParam<SmlKnob>(Vec( 9 + stripwidth * i , box.size.y - 148 ), module, MentalSubMixer::CH_VOL_PARAM + i));
			addInput(createInput<CVInPort>(Vec( 6 + stripwidth * i , box.size.y - 126 ), module, MentalSubMixer::CH_VOL_INPUT + i));
			// pan
			addParam(createParam<SmlKnob>(Vec( 9 + stripwidth * i , box.size.y - 92 ), module, MentalSubMixer::CH_PAN_PARAM + i));
			addInput(createInput<CVInPort>(Vec( 6 + stripwidth * i , box.size.y - 70 ), module, MentalSubMixer::CH_PAN_INPUT + i));
			// output
			addOutput(createOutput<OutPort>(Vec( 6 + stripwidth * i , box.size.y - 40 ), module, MentalSubMixer::CH_OUTPUT + i));
		}
	}
};

Model *modelMentalSubMixer = createModel<MentalSubMixer, MentalSubMixerWidget>("MentalSubMixer");