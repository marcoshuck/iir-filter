%       UTN - FRP
%
%       Low Pass
%   IIR Digital Filter
%
%     by Marcos Huck
%   <marcos@huck.com.ar>

clear all;
clc;

cutoff = 50; % Cutoff frequency in Hertz
sample = 1000; % Sample frequency in Hertz
order = 2; % Filter order

normalizedFrequency = cutoff / (sample / 2);

[num, den] = butter(order, normalizedFrequency);

transferFunction = filt(num, den, 1/sample);