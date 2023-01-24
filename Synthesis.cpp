#include <iostream>
#include <vector>
#include <sndfile.hh>

std::vector<double> concatenate(std::vector<std::vector<double>> samples) {
    std::vector<double> output;
    for (const auto& sample : samples) {
        output.insert(output.end(), sample.begin(), sample.end());
    }
    return output;
}

void save_wav(std::string filename, std::vector<double> samples, int sample_rate) {
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.channels = 1;
    info.samplerate = sample_rate;
    SNDFILE* file = sf_open(filename.c_str(), SFM_WRITE, &info);
    sf_write_double(file, samples.data(), samples.size());
    sf_close(file);
}

int main() {
    // load sound samples
    std::vector<std::vector<double>> samples;
    SF_INFO info;
    for (int i = 1; i <= 5; i++) {
        std::string filename = "sample" + std::to_string(i) + ".wav";
        SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &info);
        std::vector<double> sample(info.frames);
        sf_read_double(file, sample.data(), sample.size());
        samples.push_back(sample);
        sf_close(file);
    }

    // concatenate samples
    std::vector<double> output = concatenate(samples);

    // save as wav
    save_wav("output.wav", output, info.samplerate);
    return 0;
}
