%GRAFICAR VALORES DE LOS CANALES DEL ADC 

clc; clear; close all;

serial = serialport("COM9",9600,'timeout',5);
muestras = 10000; %MUESTRAS REQUERIDAS
i = 0;

%FORMATO
figure('Name', 'Señales de 6 canales del ADC', 'NumberTitle', 'on','color',[1 1 1]); grid on; hold on;
title('Voltajes de 6 canales del ADC', 'FontName', 'Arial', 'FontSize', 12);
xlabel('time [s]', 'FontName', 'Arial', 'FontSize', 9);
ylabel('Amplitud', 'FontName', 'Arial', 'FontSize', 9);
xlim([0 100]);
ylim([0 4]);

while i<muestras
    %GRAFICA MOVIBLE 
    if mod(i,100) == 0 
       xlim([i i+100]);
    end
    
    %GUARDA VALORES
    valor1 = readline(serial); 
    
    %CARACTERES A NUMEROS
    Canal_7 = str2double(valor1);
    
    %CONVERSION
    voltaje_7(i) = (Canal_7*3.3)/4096;
    
    %GRAFICAS
    plot(voltaje_7, 'm');
    drawnow;
    
    i = i+1;  
end



