#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PKPlusAudioProcessor::PKPlusAudioProcessor()
    : juce::AudioProcessor (juce::AudioProcessor::BusesProperties().withInput("Input", juce::AudioChannelSet::mono(), true)),
      presetManager(*this)
{ 
    // Add the parameters and listeners from the midi processor.
    midiProcessor.addParameters(*this);
}

PKPlusAudioProcessor::~PKPlusAudioProcessor() = default;

//==============================================================================
const juce::String PKPlusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PKPlusAudioProcessor::acceptsMidi() const { return true; }
bool PKPlusAudioProcessor::producesMidi() const { return true; }
bool PKPlusAudioProcessor::isMidiEffect() const { return true; }
double PKPlusAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int PKPlusAudioProcessor::getNumPrograms() { return 1; }
int PKPlusAudioProcessor::getCurrentProgram() { return 0; }
void PKPlusAudioProcessor::setCurrentProgram (int) { }
const juce::String PKPlusAudioProcessor::getProgramName (int) { return {}; }
void PKPlusAudioProcessor::changeProgramName (int, const juce::String&) { }

//==============================================================================
void PKPlusAudioProcessor::releaseResources() {}
bool PKPlusAudioProcessor::isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout&) const { return true; }

void PKPlusAudioProcessor::prepareToPlay (double sampleRate, int) 
{
    midiProcessor.prepareToPlay(sampleRate);
}

void PKPlusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    // The real processing is made in the MidiProcessor class.
    midiProcessor.process(midiMessages, buffer.getNumSamples(), getPlayHead());
}

//==============================================================================
bool PKPlusAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* PKPlusAudioProcessor::createEditor()
{
    return new PKPlusAudioProcessorEditor(*this);
}

//==============================================================================
void PKPlusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement xml("PluginState");

    auto* xml_params = new juce::XmlElement("Params");
    for (auto& param : getParameters()) {
        xml_params->setAttribute(ParamHelper::getParamID(param), param->getValue());
    }
    // Store the name of the current preset.
    uiSettings.presetName = presetManager.getCurrentPreset();

    xml.addChildElement(xml_params);
    xml.addChildElement(uiSettings.getXml());

    copyXmlToBinary(xml, destData);
}

void PKPlusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr) {
        auto params = xml->getChildByName("Params");
        if (params != nullptr) {
            for (auto& param: getParameters()) {
                param->setValueNotifyingHost(
                        static_cast<float>(params->getDoubleAttribute(ParamHelper::getParamID(param),
                                                                      param->getValue())));
            }
        }

        uiSettings = UISettings(xml->getChildByName("UISettings"));
        presetManager.setCurrentPreset(uiSettings.presetName);
    }
}

void PKPlusAudioProcessor::saveEditorSize(int w, int h)
{
    uiSettings.width = w;
    uiSettings.height = h;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PKPlusAudioProcessor();
}
