#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(button);

    setResizable(true, true);
    lastUIWidth.referTo(processorRef.state.getChildWithName("uiState").getPropertyAsValue("width", nullptr));
    lastUIHeight.referTo(processorRef.state.getChildWithName("uiState").getPropertyAsValue("height", nullptr));
    setSize(lastUIWidth.getValue(), lastUIHeight.getValue());

    lastUIWidth.addListener(this);
    lastUIHeight.addListener(this);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();

    button.setBounds(bounds.removeFromBottom(30).withSizeKeepingCentre(50, 24));

    lastUIWidth = getWidth();
    lastUIHeight = getHeight();
}

void AudioPluginAudioProcessorEditor::valueChanged(juce::Value &)
{
    setSize(lastUIWidth.getValue(), lastUIHeight.getValue());
}
