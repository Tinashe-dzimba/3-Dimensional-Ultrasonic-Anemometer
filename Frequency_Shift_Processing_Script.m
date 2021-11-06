

n2 = length(a);

yfft = fft(data);%% Computes FFT of template signal
xfft = fft(a); %% Computes FFT of sampled signal


xshift = fftshift(xfft);
yshift = fftshift(yfft);

   %Frequency axis for sampled signal:
   dF_samp = fs/n2;                      
   f_samp = -fs/2:dF_samp:fs/2-dF_samp;          
   
   %Frequency axis for template signal:
   dF_data = fs/N;                     
   f_data = -fs/2:dF_data:fs/2-dF_data;    
  


%% Sampled signal frequency plot
figure();
subplot(311);
plot(f_samp,10*log10(abs(xshift)));
xlabel('Frequency Shift(Hz)')
ylabel('Magnitude')
title('Frequency spectrum of sampled signal')


%% Template Signal frequency plot
subplot(312)
plot(f_data,10*log10(abs(yshift)));
xlabel('Frequency (Hz)')
ylabel('Magnitude')
title('Frequency spectrum of example signal')

