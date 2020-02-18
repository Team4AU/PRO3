clear all, close all, clc

%% indlæs signal
[x] = csvread("test200Hzfirkant_01.csv");
x   = x';%transponer fra kolonner til rækker
fs  = 1600;% !!!!!OPDATER VED ÆNDRING!!!!!
N   = length(x);
t   = N/fs;
X   = fft(x);
k   = 0:N-1;

%% plot signal
figure
subplot(3,1,1)
plot(k*t/N,x)
xlabel('tid/sekunder'), title('signal')

%% frekvensspekter
X  = fft(x);

subplot(3,1,2)
plot(k(1:floor(end/2))*fs/N,10*log10(abs(X(floor(1:end/2)))))
xlabel('frekvens/Hz'), title('frekvensspekter')

%% Mest markante frekvens

[~,s0]=max(abs(X));
f0 = s0*(fs/N);
disp(['Frekvens:   ' num2str(f0) ' Hz'])
xline(f0);

%% plot 5 perioder
subplot (3,1,3)
plot(0:round(fs*5/f0),x(2:round(fs*5/f0)+2))
xlabel('tid / sekunder'), title('5 perioder af signalet')

%% effekt

P = abs(X).^2;            % effektspektrum, P(k)=|X(k)|^2

%% SNR

sides = 4; %tilføjer nærmeste samples til Psig

Psig   = sum(P(1,s0-sides:s0+sides));
P_rest = P(1,2:(end-1)/2);
P_rest (s0-sides:s0+sides) = zeros(1,sides*2+1);
Pnoise = sum(P_rest);
SNR= Psig/Pnoise;

SNR__dB = 10*log10(SNR);
disp(['SNR: ' num2str(SNR__dB) ' dB'])
