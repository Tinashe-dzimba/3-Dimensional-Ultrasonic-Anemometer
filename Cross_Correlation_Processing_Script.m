fs = (4*10^6);% Sampling frequency (samples per second)
dt = 1/fs;% Seconds per sample
StopTime = 0.001;             % Lenght of Signal
t = (0:dt:StopTime-dt)';     % Time steps of signal
F = 40*10^3;                      % Sine wave frequency (hertz)
data = sin(2*pi*F*t);%% Template 40kHz Signal


N = length(data);
fid = fopen('test.txt');%% Text file where our sampled data is saved to. 
a = fscanf(fid,'%f');%% Array holding our saved data 

[sim,lag] = xcorr(data,a);
[~,I] = max(abs(sim));




 figure();
 subplot(311)
 plot(data);
 subplot(312)
 plot(a(1:5000));
 subplot(313)
 plot(lag,abs(sim));
title(sprintf('Delay of %f sec',lag(I)/(fs)));
