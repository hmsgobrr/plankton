#include "pt/audio.h"
#include "pt/Log.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

static ma_device device;

void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

}

namespace pt {

void initAudioDevice() {
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = 2;
    config.dataCallback = dataCallback;

    ma_result initres = ma_device_init(NULL, &config, &device);
    if (initres != MA_SUCCESS) {
        PT_CORE_ERROR("Audio device init failed: {}", initres);
        return;
    }

    ma_device_start(&device);
}

void shutdownAudioDevice() {
    ma_device_uninit(&device);
}

} // namespace pt
