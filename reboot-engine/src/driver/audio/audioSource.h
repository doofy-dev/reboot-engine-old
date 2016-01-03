#pragma once
#include <cstdlib>
#include <iostream>
#include <al.h>
#include <alc.h>
#include <windows.h>

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

namespace reboot {
	namespace driver {
		class AudioSource {
		private:
			const char* m_File;
			FILE *fp = NULL;
		public:
			AudioSource(const char* file);
			~AudioSource();

			void play();

		};
	}
}