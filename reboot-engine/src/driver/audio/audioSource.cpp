#include "audioSource.h"

namespace reboot {
	namespace driver {
		AudioSource::AudioSource(const char* file):m_File(file) {
			fp = fopen(file, "rb");                                            //Open the WAVE file
			if (!fp) {
				std::cout << "Could not open file!" << std::endl;
			}//Could not open file

			 //Variables to store info about the WAVE file (all of them is not needed for OpenAL)
			char type[4];
			DWORD size, chunkSize;
			short formatType, channels;
			DWORD sampleRate, avgBytesPerSec;
			short bytesPerSample, bitsPerSample;
			DWORD dataSize;

			fread(type, sizeof(char), 4, fp);
			fread(&size, sizeof(DWORD), 1, fp);                                           //Continue to read the file
			fread(type, sizeof(char), 4, fp);                                             //Continue to read the file
			fread(type, sizeof(char), 4, fp);

			//Now we know that the file is a acceptable WAVE file
			//Info about the WAVE data is now read and stored
			fread(&chunkSize, sizeof(DWORD), 1, fp);
			fread(&formatType, sizeof(short), 1, fp);
			fread(&channels, sizeof(short), 1, fp);
			fread(&sampleRate, sizeof(DWORD), 1, fp);
			fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
			fread(&bytesPerSample, sizeof(short), 1, fp);
			fread(&bitsPerSample, sizeof(short), 1, fp);

			fread(type, sizeof(char), 4, fp);
		
			fread(&dataSize, sizeof(DWORD), 1, fp);                                        //The size of the sound data is read

																						   //Display the info about the WAVE file
			std::cout << "Chunk Size: " << chunkSize << std::endl;
			std::cout << "Format Type: " << formatType << std::endl;
			std::cout << "Channels: " << channels << std::endl;
			std::cout << "Sample Rate: " << sampleRate << std::endl;
			std::cout << "Average Bytes Per Second: " << avgBytesPerSec << std::endl;
			std::cout << "Bytes Per Sample: " << bytesPerSample << std::endl;
			std::cout << "Bits Per Sample: " << bitsPerSample << std::endl;
			std::cout << "Data Size: " << dataSize << std::endl;

			unsigned char* buf = new unsigned char[dataSize];                            //Allocate memory for the sound data
			std::cout << fread(buf, sizeof(BYTE), dataSize, fp) << " bytes loaded"<<std::endl;

			//Now OpenAL needs to be initialized 
			ALCdevice *device;                                                          //Create an OpenAL Device
			ALCcontext *context;                                                        //And an OpenAL Context
			device = alcOpenDevice(NULL);                                               //Open the device
				context = alcCreateContext(device, NULL);                                   //Give the device a context
			alcMakeContextCurrent(context);                                             //Make the context the current
		
			ALuint source;                                                              //Is the name of source (where the sound come from)
			ALuint buffer;                                                           //Stores the sound data
			ALuint frequency = sampleRate;;                                               //The Sample Rate of the WAVE file
			ALenum format = 0;                                                            //The audio format (bits per sample, number of channels)

			alGenBuffers(1, &buffer);                                                    //Generate one OpenAL Buffer and link to "buffer"
			alGenSources(1, &source);                                                   //Generate one OpenAL Source and link to "source"
			
																						 //Figure out the format of the WAVE file
			if (bitsPerSample == 8)
			{
				if (channels == 1)
					format = AL_FORMAT_MONO8;
				else if (channels == 2)
					format = AL_FORMAT_STEREO8;
			}
			else if (bitsPerSample == 16)
			{
				if (channels == 1)
					format = AL_FORMAT_MONO16;
				else if (channels == 2)
					format = AL_FORMAT_STEREO16;
			}
		
			alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer
																					//Sound setting variables
			ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };                                    //Position of the source sound
			ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound
			ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };                                  //Position of the listener
			ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
			ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
																						//First direction vector, then vector pointing up) 
																						//Listener                                                                               
			alListenerfv(AL_POSITION, ListenerPos);                                  //Set position of the listener
			alListenerfv(AL_VELOCITY, ListenerVel);                                  //Set velocity of the listener
			alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

																						//Source
			alSourcei(source, AL_BUFFER, buffer);                                 //Link the buffer to the source
			alSourcef(source, AL_PITCH, 1.0f);                                 //Set the pitch of the source
			alSourcef(source, AL_GAIN, 1.0f);                                 //Set the gain of the source
			alSourcefv(source, AL_POSITION, SourcePos);                                 //Set the position of the source
			alSourcefv(source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
			alSourcei(source, AL_LOOPING, AL_FALSE);                                 //Set if source is looping sound

																					 //PLAY 
			alSourcePlay(source);                                                       //Play the sound buffer linked to the source
		
	/*																					//Clean-up
			fclose(fp);                                                                 //Close the WAVE file
			delete[] buf;                                                               //Delete the sound data buffer
			alDeleteSources(1, &source);                                                //Delete the OpenAL Source
			alDeleteBuffers(1, &buffer);                                                 //Delete the OpenAL Buffer
			alcMakeContextCurrent(NULL);                                                //Make no context current
			alcDestroyContext(context);                                                 //Destroy the OpenAL Context
			alcCloseDevice(device);                                                     //Close the OpenAL Device*/
		}
	}
}