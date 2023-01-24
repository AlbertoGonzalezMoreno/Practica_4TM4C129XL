%%Programa de lectura y graficación del ADC por: Alberto González Moreno
clc
clear all 
close all
%Restea todos los puertos
instrreset
txt = '5';
precision = 3;
signal = ['A' 'B' 'C' 'D' 'E'];
tams = size(signal);
index = 1:(precision + 3):(tams(1,2)*(precision + 3));
valores = 2:(precision + 3);
A = input("A qué número de puerto COM te deseas conectar? R: ");
B = input("Inserta la velocidad R: ");
s = serial(['COM' num2str(A)],'BaudRate',B);
s.Terminator = 0;
%Abre el puerto serial 
 fopen(s);
 contador = 1;
figure(1)
title('Voltaje ADC');
xlabel('Tiempo (s)');
ylabel('Voltaje (V)');
axis([0 100 0 3.5])
grid off;
hold on;
    ylim([0 3.4]);
   xlim([0 20]);
fprintf(s,txt);
while true
        C = fscanf(s,"%s");
    for i = 1:tams(1,2)
     selector(i)=C(index(1,i));
    end
    
        for i = 1:(tams(1,2))
            switch selector(i)
                case signal(1,i)
                N = str2num(C(valores + ((i-1) * (precision + 3))));
                voltaje(i,contador) = N(1,1);
            end
        end 
%         fprintf("\n Lectura ADC1: %f Lectura ADC2: %f \n",voltaje(1:contador),voltaje(2,contador));
         hola(contador + 1)=3.4;
    contador = contador + 1;
    if(mod(contador,10) == 0)
        for i = 1:tams(1,2)
        subplot(tams(1,2),1,i)
        plot(voltaje(i,:),'b'); title (['Lectura ADC' num2str(i)]);
        hold on;
        plot(hola,'w');
        drawnow
        end
                if(contador == 500)
                    contador = 1;
                    clear voltaje;
                      clf;
                end
    end
    fprintf(s,txt);
end
