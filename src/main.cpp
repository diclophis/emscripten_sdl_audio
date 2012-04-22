// Vanilla Linux OpenGL+GLUT+SOIL App

#include <stdio.h>
#include <dirent.h>
#include <vector>

#include "modplug.h"

#include "SDL.h"
#include "SDL_audio.h"

static std::vector<ModPlugFile *> m_Sounds;

static short int *outData;


void mixaudio(void *unused, Uint8 *stream, int len) {
  //Engine::CurrentGameDoAudio((short *)stream, len);
}


char *path_cat (const char *str1, char *str2) {
	size_t str1_len = strlen(str1);
	size_t str2_len = strlen(str2);
	char *result;
	result = (char*)malloc((str1_len+str2_len+1)*sizeof *result);
	strcpy (result,str1);
	int i,j;
	for(i=str1_len, j=0; ((i<(str1_len+str2_len)) && (j<str2_len));i++, j++) {
		result[i]=str2[j];
	}
	result[str1_len+str2_len]='\0';
	return result;
}


int is_not_dot_or_dot_dot(const struct dirent *dp) {
  if (strcmp(".", dp->d_name) == 0 || strcmp("..", dp->d_name) == 0) {
    return 0;
  } else {
    return 1;
  }
}


int alphasort(const struct dirent **a, const struct dirent **b) {
  return strcmp((*a)->d_name,(*b)->d_name);
}


int main(int argc, char** argv) {
  struct dirent *dp;
  struct dirent **dps;
  const char *dir_path="../../assets/sounds/";
  DIR *dir = opendir(dir_path);
  if (dir) {
    while ((dp=readdir(dir)) != NULL) {
      char *tmp;
      tmp = path_cat(dir_path, dp->d_name);
      if (strcmp(".", dp->d_name) == 0 || strcmp("..", dp->d_name) == 0) {
      } else {
        FILE *fd = fopen(tmp, "rb");
        fseek(fd, 0, SEEK_END);
        unsigned int len = ftell(fd);
        rewind(fd);
        //Engine::PushBackFileHandle(SOUNDS, fd, 0, len);
      }
    
      free(tmp);
      tmp=NULL;
    }
    closedir(dir);
  }

  outData = (short int *)calloc(512, sizeof(short int));

  // Set 16-bit stereo audio at 44.1Khz
  SDL_AudioSpec fmt;
  fmt.freq = 44100;
  fmt.format = AUDIO_S16;
  fmt.channels = 2;
  fmt.samples = 512;
  fmt.callback = mixaudio;
  fmt.userdata = NULL;

  // Open the audio device and start playing sound!
  if (SDL_OpenAudio(&fmt, NULL) < 0) {
    printf("No audio: %s\n", SDL_GetError());
  } else {
    SDL_PauseAudio(0);
  }

  throw 0;

  return 0;
}
