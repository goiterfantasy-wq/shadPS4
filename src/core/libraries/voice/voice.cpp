// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/logging/log.h"
#include "core/libraries/error_codes.h"
#include "core/libraries/libs.h"
#include "core/libraries/voice/voice.h"

namespace Libraries::Voice {

s32 PS4_SYSV_ABI sceVoiceConnectIPortToOPort(u32 input_port, u32 output_port) {
    LOG_INFO(Lib_Voice, "called input_port={} output_port={}", input_port, output_port);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceCreatePort(u32 port_id, const OrbisVoicePortParam* param) {
    LOG_INFO(Lib_Voice, "called port_id={}", port_id);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceDeletePort(u32 port_id) {
    LOG_INFO(Lib_Voice, "called port_id={}", port_id);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceDisconnectIPortFromOPort(u32 input_port, u32 output_port) {
    LOG_INFO(Lib_Voice, "called input_port={} output_port={}", input_port, output_port);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceEnd() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetBitRate(u32 port_id, u32* bitrate) {
    LOG_INFO(Lib_Voice, "called port_id={}", port_id);
    if (bitrate) {
        *bitrate = 48000;
    }
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetMuteFlag() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetPortAttr() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetPortInfo(u32 port_id, OrbisVoicePortInfo* info) {
    LOG_INFO(Lib_Voice, "called port_id={}", port_id);

    if (!info) {
        return SCE_VOICE_ERROR_ARGUMENT_INVALID;
    }

    info->port_type = 0;
    info->state = 3;
    info->byte_count = 0;
    info->frame_size = 1;
    info->edge_count = 0;
    info->reserved = 0;

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetResourceInfo(OrbisVoiceResourceInfo* info) {
    LOG_ERROR(Lib_Voice, "called");

    if (!info) {
        return SCE_VOICE_ERROR_ARGUMENT_INVALID;
    }

    info->max_in_voice_port = 2;
    info->max_out_voice_port = 4;
    info->max_in_device_port = 0;
    info->max_out_device_port = 5;

    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceGetVolume() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceInit(OrbisVoiceInitParam* param, u32 version) {
    LOG_INFO(Lib_Voice, "called version={}", version);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceInitHQ() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoicePausePort() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoicePausePortAll() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceReadFromOPort(u32 output_port, void* data, u32* size) {
    LOG_INFO(Lib_Voice, "called output_port={}", output_port);
    if (size) {
        *size = 0;
    }
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceResetPort() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceResumePort() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceResumePortAll() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceSetBitRate() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceSetMuteFlag(u32 port_id, bool muted) {
    LOG_INFO(Lib_Voice, "called port_id={} muted={}", port_id, muted);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceSetMuteFlagAll() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceSetThreadsParams() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceSetVolume(u32 port_id, float volume) {
    LOG_INFO(Lib_Voice, "called port_id={} volume={:.2f}", port_id, volume);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceStart(OrbisVoiceStartParam* param) {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceStop() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceUpdatePort() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceVADAdjustment() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceVADSetVersion() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceWriteToIPort() {
    LOG_INFO(Lib_Voice, "called");
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceQoSInit(void* mem_block, u32 mem_size, s32 app_type) {
    LOG_INFO(Lib_Voice, "called mem_size={} app_type={}", mem_size, app_type);
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceQoSCreateLocalEndpoint(s32* local_id, s32 user_id, s32 device_in_id, s32 device_out_id) {
    LOG_INFO(Lib_Voice, "called user_id={} device_in_id={} device_out_id={}", user_id, device_in_id, device_out_id);
    if (local_id) {
        *local_id = 0;
    }
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVoiceQoSGetLocalEndpointAttribute(s32 local_id, s32 attribute_id, void* attribute_value, s32 attribute_size) {
    LOG_INFO(Lib_Voice, "called local_id={} attribute_id={} attribute_size={}", local_id, attribute_id, attribute_size);
    return ORBIS_OK;
}

void RegisterLib(Core::Loader::SymbolsResolver* sym) {
    LIB_FUNCTION("oV9GAdJ23Gw", "libSceVoice", 1, "libSceVoice", sceVoiceConnectIPortToOPort);
    LIB_FUNCTION("nXpje5yNpaE", "libSceVoice", 1, "libSceVoice", sceVoiceCreatePort);
    LIB_FUNCTION("b7kJI+nx2hg", "libSceVoice", 1, "libSceVoice", sceVoiceDeletePort);
    LIB_FUNCTION("ajVj3QG2um4", "libSceVoice", 1, "libSceVoice", sceVoiceDisconnectIPortFromOPort);
    LIB_FUNCTION("Oo0S5PH7FIQ", "libSceVoice", 1, "libSceVoice", sceVoiceEnd);
    LIB_FUNCTION("cJLufzou6bc", "libSceVoice", 1, "libSceVoice", sceVoiceGetBitRate);
    LIB_FUNCTION("Pc4z1QjForU", "libSceVoice", 1, "libSceVoice", sceVoiceGetMuteFlag);
    LIB_FUNCTION("elcxZTEfHZM", "libSceVoice", 1, "libSceVoice", sceVoiceGetPortAttr);
    LIB_FUNCTION("CrLqDwWLoXM", "libSceVoice", 1, "libSceVoice", sceVoiceGetPortInfo);
    LIB_FUNCTION("Z6QV6j7igvE", "libSceVoice", 1, "libSceVoice", sceVoiceGetResourceInfo);
    LIB_FUNCTION("jjkCjneOYSs", "libSceVoice", 1, "libSceVoice", sceVoiceGetVolume);
    LIB_FUNCTION("9TrhuGzberQ", "libSceVoice", 1, "libSceVoice", sceVoiceInit);
    LIB_FUNCTION("IPHvnM5+g04", "libSceVoice", 1, "libSceVoice", sceVoiceInitHQ);
    LIB_FUNCTION("x0slGBQW+wY", "libSceVoice", 1, "libSceVoice", sceVoicePausePort);
    LIB_FUNCTION("Dinob0yMRl8", "libSceVoice", 1, "libSceVoice", sceVoicePausePortAll);
    LIB_FUNCTION("cQ6DGsQEjV4", "libSceVoice", 1, "libSceVoice", sceVoiceReadFromOPort);
    LIB_FUNCTION("udAxvCePkUs", "libSceVoice", 1, "libSceVoice", sceVoiceResetPort);
    LIB_FUNCTION("gAgN+HkiEzY", "libSceVoice", 1, "libSceVoice", sceVoiceResumePort);
    LIB_FUNCTION("jbkJFmOZ9U0", "libSceVoice", 1, "libSceVoice", sceVoiceResumePortAll);
    LIB_FUNCTION("TexwmOHQsDg", "libSceVoice", 1, "libSceVoice", sceVoiceSetBitRate);
    LIB_FUNCTION("gwUynkEgNFY", "libSceVoice", 1, "libSceVoice", sceVoiceSetMuteFlag);
    LIB_FUNCTION("oUha0S-Ij9Q", "libSceVoice", 1, "libSceVoice", sceVoiceSetMuteFlagAll);
    LIB_FUNCTION("clyKUyi3RYU", "libSceVoice", 1, "libSceVoice", sceVoiceSetThreadsParams);
    LIB_FUNCTION("QBFoAIjJoXQ", "libSceVoice", 1, "libSceVoice", sceVoiceSetVolume);
    LIB_FUNCTION("54phPH2LZls", "libSceVoice", 1, "libSceVoice", sceVoiceStart);
    LIB_FUNCTION("Ao2YNSA7-Qo", "libSceVoice", 1, "libSceVoice", sceVoiceStop);
    LIB_FUNCTION("jSZNP7xJrcw", "libSceVoice", 1, "libSceVoice", sceVoiceUpdatePort);
    LIB_FUNCTION("hg9T73LlRiU", "libSceVoice", 1, "libSceVoice", sceVoiceVADAdjustment);
    LIB_FUNCTION("wFeAxEeEi-8", "libSceVoice", 1, "libSceVoice", sceVoiceVADSetVersion);
    LIB_FUNCTION("YeJl6yDlhW0", "libSceVoice", 1, "libSceVoice", sceVoiceWriteToIPort);

    LIB_FUNCTION("U8IfNl6/Css", "libSceVoiceQoS", 1, "libSceVoiceQoS", sceVoiceQoSInit);
    LIB_FUNCTION("lvNClhNHzxI", "libSceVoiceQoS", 1, "libSceVoiceQoS", sceVoiceQoSCreateLocalEndpoint);
    LIB_FUNCTION("eZu2RP0Ma3w", "libSceVoiceQoS", 1, "libSceVoiceQoS", sceVoiceQoSGetLocalEndpointAttribute);
};

} // namespace Libraries::Voice
