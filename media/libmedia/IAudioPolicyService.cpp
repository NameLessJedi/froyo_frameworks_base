/*
**
** Copyright 2009, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "IAudioPolicyService"
#include <utils/Log.h>

#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>

#include <media/IAudioPolicyService.h>

namespace android {

enum {
    SET_DEVICE_CONNECTION_STATE = IBinder::FIRST_CALL_TRANSACTION,
    GET_DEVICE_CONNECTION_STATE,
    SET_PHONE_STATE,
    SET_RINGER_MODE,
    SET_FORCE_USE,
    GET_FORCE_USE,
    GET_OUTPUT,
    START_OUTPUT,
    STOP_OUTPUT,
    RELEASE_OUTPUT,
    GET_INPUT,
    START_INPUT,
    STOP_INPUT,
    RELEASE_INPUT,
    INIT_STREAM_VOLUME,
    SET_STREAM_VOLUME,
    GET_STREAM_VOLUME
};

class BpAudioPolicyService : public BpInterface<IAudioPolicyService>
{
public:
    BpAudioPolicyService(const sp<IBinder>& impl)
        : BpInterface<IAudioPolicyService>(impl)
    {
    }

    virtual status_t setDeviceConnectionState(
                                    AudioSystem::audio_devices device,
                                    AudioSystem::device_connection_state state,
                                    const char *device_address)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(device));
        data.writeInt32(static_cast <uint32_t>(state));
        data.writeCString(device_address);
        remote()->transact(SET_DEVICE_CONNECTION_STATE, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual AudioSystem::device_connection_state getDeviceConnectionState(
                                    AudioSystem::audio_devices device,
                                    const char *device_address)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(device));
        data.writeCString(device_address);
        remote()->transact(GET_DEVICE_CONNECTION_STATE, data, &reply);
        return static_cast <AudioSystem::device_connection_state>(reply.readInt32());
    }

    virtual status_t setPhoneState(int state)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(state);
        remote()->transact(SET_PHONE_STATE, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t setRingerMode(uint32_t mode, uint32_t mask)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(mode);
        data.writeInt32(mask);
        remote()->transact(SET_RINGER_MODE, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t setForceUse(AudioSystem::force_use usage, AudioSystem::forced_config config)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(usage));
        data.writeInt32(static_cast <uint32_t>(config));
        remote()->transact(SET_FORCE_USE, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual AudioSystem::forced_config getForceUse(AudioSystem::force_use usage)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(usage));
        remote()->transact(GET_FORCE_USE, data, &reply);
        return static_cast <AudioSystem::forced_config> (reply.readInt32());
    }

    virtual audio_io_handle_t getOutput(
                                        AudioSystem::stream_type stream,
                                        uint32_t samplingRate,
                                        uint32_t format,
                                        uint32_t channels,
                                        AudioSystem::output_flags flags)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(stream));
        data.writeInt32(samplingRate);
        data.writeInt32(static_cast <uint32_t>(format));
        data.writeInt32(channels);
        data.writeInt32(static_cast <uint32_t>(flags));
        remote()->transact(GET_OUTPUT, data, &reply);
        return static_cast <audio_io_handle_t> (reply.readInt32());
    }

    virtual status_t startOutput(audio_io_handle_t output, AudioSystem::stream_type stream)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(output);
        data.writeInt32(stream);
        remote()->transact(START_OUTPUT, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t stopOutput(audio_io_handle_t output, AudioSystem::stream_type stream)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(output);
        data.writeInt32(stream);
        remote()->transact(STOP_OUTPUT, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual void releaseOutput(audio_io_handle_t output)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(output);
        remote()->transact(RELEASE_OUTPUT, data, &reply);
    }

    virtual audio_io_handle_t getInput(
                                    int inputSource,
                                    uint32_t samplingRate,
                                    uint32_t format,
                                    uint32_t channels,
                                    AudioSystem::audio_in_acoustics acoustics)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(inputSource);
        data.writeInt32(samplingRate);
        data.writeInt32(static_cast <uint32_t>(format));
        data.writeInt32(channels);
        data.writeInt32(static_cast <uint32_t>(acoustics));
        remote()->transact(GET_INPUT, data, &reply);
        return static_cast <audio_io_handle_t> (reply.readInt32());
    }

    virtual status_t startInput(audio_io_handle_t input)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(START_INPUT, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t stopInput(audio_io_handle_t input)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(STOP_INPUT, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual void releaseInput(audio_io_handle_t input)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(RELEASE_INPUT, data, &reply);
    }

    virtual status_t initStreamVolume(AudioSystem::stream_type stream,
                                    int indexMin,
                                    int indexMax)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(stream));
        data.writeInt32(indexMin);
        data.writeInt32(indexMax);
        remote()->transact(INIT_STREAM_VOLUME, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t setStreamVolumeIndex(AudioSystem::stream_type stream, int index)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(stream));
        data.writeInt32(index);
        remote()->transact(SET_STREAM_VOLUME, data, &reply);
        return static_cast <status_t> (reply.readInt32());
    }

    virtual status_t getStreamVolumeIndex(AudioSystem::stream_type stream, int *index)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAudioPolicyService::getInterfaceDescriptor());
        data.writeInt32(static_cast <uint32_t>(stream));
        remote()->transact(GET_STREAM_VOLUME, data, &reply);
        int lIndex = reply.readInt32();
        if (index) *index = lIndex;
        return static_cast <status_t> (reply.readInt32());
    }
};

IMPLEMENT_META_INTERFACE(AudioPolicyService, "android.media.IAudioPolicyService");

// ----------------------------------------------------------------------


status_t BnAudioPolicyService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case SET_DEVICE_CONNECTION_STATE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::audio_devices device = static_cast <AudioSystem::audio_devices>(data.readInt32());
            AudioSystem::device_connection_state state = static_cast <AudioSystem::device_connection_state>(data.readInt32());
            const char *device_address = data.readCString();
            reply->writeInt32(static_cast <uint32_t>(setDeviceConnectionState(device, state, device_address)));
            return NO_ERROR;
        } break;

        case GET_DEVICE_CONNECTION_STATE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::audio_devices device = static_cast <AudioSystem::audio_devices>(data.readInt32());
            const char *device_address = data.readCString();
            reply->writeInt32(static_cast <uint32_t>(getDeviceConnectionState(device, device_address)));
            return NO_ERROR;
        } break;

        case SET_PHONE_STATE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            reply->writeInt32(static_cast <uint32_t>(setPhoneState(data.readInt32())));
            return NO_ERROR;
        } break;

        case SET_RINGER_MODE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            uint32_t mode = data.readInt32();
            uint32_t mask = data.readInt32();
            reply->writeInt32(static_cast <uint32_t>(setRingerMode(mode, mask)));
            return NO_ERROR;
        } break;

        case SET_FORCE_USE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::force_use usage = static_cast <AudioSystem::force_use>(data.readInt32());
            AudioSystem::forced_config config = static_cast <AudioSystem::forced_config>(data.readInt32());
            reply->writeInt32(static_cast <uint32_t>(setForceUse(usage, config)));
            return NO_ERROR;
        } break;

        case GET_FORCE_USE: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::force_use usage = static_cast <AudioSystem::force_use>(data.readInt32());
            reply->writeInt32(static_cast <uint32_t>(getForceUse(usage)));
            return NO_ERROR;
        } break;

        case GET_OUTPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::stream_type stream = static_cast <AudioSystem::stream_type>(data.readInt32());
            uint32_t samplingRate = data.readInt32();
            uint32_t format = data.readInt32();
            uint32_t channels = data.readInt32();
            AudioSystem::output_flags flags = static_cast <AudioSystem::output_flags>(data.readInt32());

            audio_io_handle_t output = getOutput(stream,
                                                 samplingRate,
                                                 format,
                                                 channels,
                                                 flags);
            reply->writeInt32(static_cast <int>(output));
            return NO_ERROR;
        } break;

        case START_OUTPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t output = static_cast <audio_io_handle_t>(data.readInt32());
            uint32_t stream = data.readInt32();
            reply->writeInt32(static_cast <uint32_t>(startOutput(output, (AudioSystem::stream_type)stream)));
            return NO_ERROR;
        } break;

        case STOP_OUTPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t output = static_cast <audio_io_handle_t>(data.readInt32());
            uint32_t stream = data.readInt32();
            reply->writeInt32(static_cast <uint32_t>(stopOutput(output, (AudioSystem::stream_type)stream)));
            return NO_ERROR;
        } break;

        case RELEASE_OUTPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t output = static_cast <audio_io_handle_t>(data.readInt32());
            releaseOutput(output);
            return NO_ERROR;
        } break;

        case GET_INPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            int inputSource = data.readInt32();
            uint32_t samplingRate = data.readInt32();
            uint32_t format = data.readInt32();
            uint32_t channels = data.readInt32();
            AudioSystem::audio_in_acoustics acoustics = static_cast <AudioSystem::audio_in_acoustics>(data.readInt32());
            audio_io_handle_t input = getInput(inputSource,
                                               samplingRate,
                                               format,
                                               channels,
                                               acoustics);
            reply->writeInt32(static_cast <int>(input));
            return NO_ERROR;
        } break;

        case START_INPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t input = static_cast <audio_io_handle_t>(data.readInt32());
            reply->writeInt32(static_cast <uint32_t>(startInput(input)));
            return NO_ERROR;
        } break;

        case STOP_INPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t input = static_cast <audio_io_handle_t>(data.readInt32());
            reply->writeInt32(static_cast <uint32_t>(stopInput(input)));
            return NO_ERROR;
        } break;

        case RELEASE_INPUT: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            audio_io_handle_t input = static_cast <audio_io_handle_t>(data.readInt32());
            releaseInput(input);
            return NO_ERROR;
        } break;

        case INIT_STREAM_VOLUME: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::stream_type stream = static_cast <AudioSystem::stream_type>(data.readInt32());
            int indexMin = data.readInt32();
            int indexMax = data.readInt32();
            reply->writeInt32(static_cast <uint32_t>(initStreamVolume(stream, indexMin,indexMax)));
            return NO_ERROR;
        } break;

        case SET_STREAM_VOLUME: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::stream_type stream = static_cast <AudioSystem::stream_type>(data.readInt32());
            int index = data.readInt32();
            reply->writeInt32(static_cast <uint32_t>(setStreamVolumeIndex(stream, index)));
            return NO_ERROR;
        } break;

        case GET_STREAM_VOLUME: {
            CHECK_INTERFACE(IAudioPolicyService, data, reply);
            AudioSystem::stream_type stream = static_cast <AudioSystem::stream_type>(data.readInt32());
            int index;
            status_t status = getStreamVolumeIndex(stream, &index);
            reply->writeInt32(index);
            reply->writeInt32(static_cast <uint32_t>(status));
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

// ----------------------------------------------------------------------------

}; // namespace android
