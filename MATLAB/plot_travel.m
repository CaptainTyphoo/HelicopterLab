%% Plot travel 
%figure(3);
%plot(travel.time, travel.signals.values);

%figure(5);
%plot(scope_travel.time, scope_travel.signals.values);

figure(6);

load('input2.mat');
load('travel2.mat');
load('pitch2.mat');
load('elevation2.mat');


subplot(411);
plot(input2(1,:), input2(2,:));
title('Input');

subplot(412)
plot(travel2(1,:), travel2(2,:));
title('Travel');

subplot(413)
plot(pitch2(1,:), pitch2(2,:));
title('Pitch');
subplot(414)
plot(elevation2(1,:), elevation2(2,:));
title('Elevation');