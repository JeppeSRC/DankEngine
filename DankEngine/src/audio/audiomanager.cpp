#include "audiomanager.h"
#include "application.h"
#include "utils/asset/fileutils.h"

#define JELLY_BEAN_MR1	17

namespace dank {

	SLObjectItf AudioManager::engineObject = nullptr, AudioManager::bufferQueuePlayerObject = nullptr;
	SLEngineItf AudioManager::engineInterface;

	SLObjectItf AudioManager::outputMixObject;
	SLEnvironmentalReverbItf AudioManager::outputMixInterface;

	void AudioManager::Init() {
		slCreateEngine(&engineObject, 0, 0, 0, 0, 0);
		(*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
		(*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineInterface);

		SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
		SLboolean req[1] = { SL_BOOLEAN_FALSE };
		(*engineInterface)->CreateOutputMix(engineInterface, &outputMixObject, 1, ids, req);
		(*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
		
		(*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB, &outputMixInterface);
		SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
		
		(*outputMixInterface)->SetEnvironmentalReverbProperties(outputMixInterface, &reverbSettings);
		
		//Jni code for getting the buffer size and sample rate
		/*char buildversionsdk[50];
		__system_property_get("ro.build.version.sdk", buildversionsdk);
		int sampleRate, bufSize;
		if (ToInt(std::string(buildversionsdk)) >= JELLY_BEAN_MR1) {
			NativeApp* app = NativeApp::app;
			JNIEnv* env;
			app->activity->vm->AttachCurrentThread(&env, NULL);

			jclass nativeclass = env->GetObjectClass(app->activity->clazz);
			jclass audiomanagerclass = env->FindClass("android/media/AudioManager");

			jmethodID getSystemService = env->GetMethodID(nativeclass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
			jmethodID getProperty = env->GetMethodID(audiomanagerclass, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;");

			char audioMethodStringChars[] = "audio";
			char sampleRateStringChars[] = "android.media.property.OUTPUT_SAMPLE_RATE";
			char framesPerBufferStringChars[] = "android.media.property.OUTPUT_FRAMES_PER_BUFFER";

			jstring audioMethodString = env->NewStringUTF(audioMethodStringChars);
			jstring sampleRateString = env->NewStringUTF(sampleRateStringChars);
			jstring framesPerBufferString = env->NewStringUTF(framesPerBufferStringChars);

			jobject audiomanager = env->CallObjectMethod(app->activity->clazz, getSystemService, audioMethodString);
			jstring sampleRateObject = (jstring)env->CallObjectMethod(audiomanager, getProperty, sampleRateString);
			jstring bufSizeObject = (jstring)env->CallObjectMethod(audiomanager, getProperty, framesPerBufferString);

			const char* sampleRateStr = env->GetStringUTFChars(sampleRateObject, 0);
			const char* bufSizeStr = env->GetStringUTFChars(bufSizeObject, 0);

			sampleRate = ToInt(std::string(sampleRateStr));
			bufSize = ToInt(std::string(bufSizeStr));

			env->ReleaseStringUTFChars(sampleRateObject, sampleRateStr);
			env->ReleaseStringUTFChars(bufSizeObject, bufSizeStr);
		}
		LOGI("[AudioManager] Sample rate: %d, Buffer size: %d", sampleRate, bufSize);

		//Create buffer queue audio player
		SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_8,
			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
			SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN
		};

		if (sampleRate) {
			format_pcm.samplesPerSec = sampleRate * 1000; // because it needs to be in milli seconds
		}

		SLDataSource audioSrc = { &loc_bufq, &format_pcm };

		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
		SLDataSink audioSink = { &loc_outmix, NULL };

		const SLInterfaceID ids[3] = { SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND };
		const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

		(*engineInterface)->CreateAudioPlayer(engineInterface, &bufferQueuePlayerObject, &audioSrc, &audioSink, sampleRate ? 2 : 3, ids, req);
		(*bufferQueuePlayerObject)->Realize(bufferQueuePlayerObject, SL_BOOLEAN_FALSE);
		(*bufferQueuePlayerObject)->GetInterface(bufferQueuePlayerObject, SL_IID_PLAY, &bufferQueuePlay);
		(*bufferQueuePlayerObject)->GetInterface(bufferQueuePlayerObject, SL_IID_BUFFERQUEUE, &bufferQueuePlayerBuffer);
		(*bufferQueuePlayerBuffer)->RegisterCallback(bufferQueuePlayerBuffer, bufferQueuePlayerCallback, NULL);
		if (sampleRate == 0) {
			(*bufferQueuePlayerObject)->GetInterface(bufferQueuePlayerObject, SL_IID_EFFECTSEND, &bufferQueuePlayerEffectSend);
		}

		(*bufferQueuePlayerObject)->GetInterface(bufferQueuePlayerObject, SL_IID_VOLUME, &bufferQueuePlayerVolume);
		(*bufferQueuePlay)->SetPlayState(bufferQueuePlay, SL_PLAYSTATE_PLAYING);*/
	}

	void AudioManager::Destroy() {
		(*outputMixObject)->Destroy(outputMixObject);
		(*engineObject)->Destroy(engineObject);
	}
}