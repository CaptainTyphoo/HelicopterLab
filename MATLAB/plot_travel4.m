%% Plot travel 
%figure(3);
%plot(travel.time, travel.signals.values);

%figure(5);
%plot(scope_travel.time, scope_travel.signals.values);

figure(6);
folder='helicopter4\';
load([folder, 'optinput4.mat']);
load([folder, 'input4.mat']);
load([folder, 'travel4.mat']);
load([folder, 'pitch4.mat']);
load([folder, 'elevation4.mat']);



subplot(611);
plot(input4(1,:), input4(2,:));
title('Input');

subplot(612)
plot(optinput4(1,:), optinput4(2,:));
hold on;
plot(input4(1,:), input4(2,:), 'g');

title('OptimalInput');

subplot(613)
plot(travel4(1,:), travel4(2,:));
title('Travel');
hold on;
plot(t,x1*(180/pi)-180, 'r');

subplot(614)
plot(pitch4(1,:), pitch4(2,:));
title('Pitch');
hold on;
plot(t,x3*(180/pi), 'r');

subplot(615)
plot(optinput4(1,:), optinput4(3,:));
title('input 2');
hold on;
plot(input4(1,:), input4(3,:), 'g'); % I mayv have broken this

subplot(616)
plot(elevation4(1,:), elevation4(2,:));
title('Elevation');
hold on;
plot(t,x5*(180/pi), 'r');

