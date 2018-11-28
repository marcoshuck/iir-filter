%       UTN - FRP
%
%       High Pass
%   IIR Digital Filter
%
%     by Marcos Huck
%   <marcos@huck.com.ar>

clear all;
clc;

cutoff = 100; % Cutoff frequency in Hertz
sample = 1000; % Sample frequency in Hertz
order = 2; % Filter order

normalizedFrequency = cutoff / (sample / 2);

[num, den] = butter(order, normalizedFrequency, 'high');

transferFunction = filt(num, den, 1/sample);

bode(transferFunction);