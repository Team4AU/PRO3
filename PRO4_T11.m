clear all, close all

[x]=csvread("test200Hzfirkant_01.csv");
x=x';
x=x(1,1:end);
x=x(1,end/2:end);
fs=1000;

N=length(x);
t=N/fs;
X = fft(x);
k = 0:N-1;

figure
subplot(2,1,1)
plot(x)
title('raw')

subplot(2,1,2)
X=fft(x);
k = 0:N-1;
plot(k*fs/t,abs(X)*2/N)
title('ingen vinduer')
hold on;