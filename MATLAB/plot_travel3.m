%% Plot travel 
%figure(3);
%plot(travel.time, travel.signals.values);

%figure(5);
%plot(scope_travel.time, scope_travel.signals.values);

figure(6);

load('optinput3.mat');
load('input2.mat');
load('travel2.mat');
load('pitch2.mat');
load('elevation2.mat');


subplot(511);
plot(input2(1,:), input2(2,:));
title('Input');

subplot(512)
plot(optinput3(1,:), optinput3(2,:));
hold on;
plot(input2(1,:), input2(2,:), 'g');

title('OptimalInput');

subplot(513)
plot(travel2(1,:), travel2(2,:));
title('Travel');
hold on;
plot(t,x1*(180/pi)-180, 'r');

subplot(514)
plot(pitch2(1,:), pitch2(2,:));
title('Pitch');
hold on;
plot(t,x3*(180/pi), 'r');

subplot(515)
plot(elevation2(1,:), elevation2(2,:));
title('Elevation');

