function snr=SNR_singlech(I,In)
% I :original signal
% In:noisy signal(ie. original signal + noise signal)
snr=0;
Ps=sum(sum((I-mean(mean(I))).^2));%signal power
Pn=sum(sum((I-In).^2));           %noise power
snr=10*log10(Ps/Pn);