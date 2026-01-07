// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common/types.h"

namespace Core::Loader {
class SymbolsResolver;
}

namespace Libraries::Voice {

constexpr s32 SCE_VOICE_ERROR_ARGUMENT_INVALID = -2142369787; // 0x804e0805

struct OrbisVoiceInitParam {
    s32 app_type;
    s32 align;
    void* on_event;
    void* user_data;
    u8 reserved[12];
};

struct OrbisVoiceStartParam {
    void* container;
    u32 mem_size;
    u8 reserved[20];
};

struct OrbisVoicePortParam {
    // Empty in fpPS4 reference
};

struct OrbisVoicePortInfo {
    s32 port_type;
    s32 state;
    u32* edge;
    u32 byte_count;
    u32 frame_size;
    u16 edge_count;
    u16 reserved;
};

struct OrbisVoiceResourceInfo {
    u16 max_in_voice_port;
    u16 max_out_voice_port;
    u16 max_in_device_port;
    u16 max_out_device_port;
};

s32 PS4_SYSV_ABI sceVoiceConnectIPortToOPort(u32 input_port, u32 output_port);
s32 PS4_SYSV_ABI sceVoiceCreatePort(u32 port_id, const OrbisVoicePortParam* param);
s32 PS4_SYSV_ABI sceVoiceDeletePort(u32 port_id);
s32 PS4_SYSV_ABI sceVoiceDisconnectIPortFromOPort(u32 input_port, u32 output_port);
s32 PS4_SYSV_ABI sceVoiceEnd();
s32 PS4_SYSV_ABI sceVoiceGetBitRate(u32 port_id, u32* bitrate);
s32 PS4_SYSV_ABI sceVoiceGetMuteFlag();
s32 PS4_SYSV_ABI sceVoiceGetPortAttr();
s32 PS4_SYSV_ABI sceVoiceGetPortInfo(u32 port_id, OrbisVoicePortInfo* info);
s32 PS4_SYSV_ABI sceVoiceGetResourceInfo(OrbisVoiceResourceInfo* info);
s32 PS4_SYSV_ABI sceVoiceGetVolume();
s32 PS4_SYSV_ABI sceVoiceInit(OrbisVoiceInitParam* param, u32 version);
s32 PS4_SYSV_ABI sceVoiceInitHQ();
s32 PS4_SYSV_ABI sceVoicePausePort();
s32 PS4_SYSV_ABI sceVoicePausePortAll();
s32 PS4_SYSV_ABI sceVoiceReadFromOPort(u32 output_port, void* data, u32* size);
s32 PS4_SYSV_ABI sceVoiceResetPort();
s32 PS4_SYSV_ABI sceVoiceResumePort();
s32 PS4_SYSV_ABI sceVoiceResumePortAll();
s32 PS4_SYSV_ABI sceVoiceSetBitRate();
s32 PS4_SYSV_ABI sceVoiceSetMuteFlag(u32 port_id, bool muted);
s32 PS4_SYSV_ABI sceVoiceSetMuteFlagAll();
s32 PS4_SYSV_ABI sceVoiceSetThreadsParams();
s32 PS4_SYSV_ABI sceVoiceSetVolume(u32 port_id, float volume);
s32 PS4_SYSV_ABI sceVoiceStart(OrbisVoiceStartParam* param);
s32 PS4_SYSV_ABI sceVoiceStop();
s32 PS4_SYSV_ABI sceVoiceUpdatePort();
s32 PS4_SYSV_ABI sceVoiceVADAdjustment();
s32 PS4_SYSV_ABI sceVoiceVADSetVersion();
s32 PS4_SYSV_ABI sceVoiceWriteToIPort();

void RegisterLib(Core::Loader::SymbolsResolver* sym);
} // namespace Libraries::Voice
