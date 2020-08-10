# pip install librosa
import librosa , librosa.display
import matplotlib.pyplot as plt
import numpy as np
file = "blues.00000.wav"

# waveform
signal, sr = librosa.load(file,sr = 22050)
librosa.display.waveplot(signal, sr = sr)
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.show()

#fft-> spectrum
fft = np.fft.fft(signal)
magnitude = np.abs(fft)
frequency = np.linspace(0,sr,len(magnitude))

left_frequency = frequency[:int(len(frequency)/2)]
left_magnitude = magnitude[:int(len(magnitude)/2)]
plt.plot(frequency, magnitude)
plt.xlabel("frequency")
plt.ylabel("Magnitude")
plt.show()

plt.plot(left_frequency, left_magnitude)
plt.xlabel("frequency")
plt.ylabel("Magnitude")
plt.show()
#spectrogram
n_fft = 2048
hop_length = 512
stft = librosa.core.stft(signal,hop_length = hop_length, n_fft = n_fft)
spectrogram = np.abs(stft)

librosa.display.specshow(spectrogram, sr = sr, hop_length = hop_length)
plt.xlabel("Time")
plt.ylabel("Frequency")
plt.colorbar()
plt.show()

log_spectrogram = librosa.amplitude_to_db(spectrogram)

librosa.display.specshow(log_spectrogram, sr = sr, hop_length = hop_length)
plt.xlabel("Time")
plt.ylabel("Frequency")
plt.colorbar()
plt.show()

# MFCCs
MFFCs = librosa.feature.mfcc(signal,n_fft = n_fft, hop_length = hop_length, n_mfcc = 13 )
librosa.display.specshow(MFFCs, sr = sr, hop_length = hop_length)
plt.xlabel("Time")
plt.ylabel("MFFCs")
plt.colorbar()
plt.show()

#############################################################################################

print("End")
