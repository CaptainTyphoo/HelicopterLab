%% Plot travel 
%figure(3);
%plot(travel.time, travel.signals.values);

%figure(5);
%plot(scope_travel.time, scope_travel.signals.values);

figure(6);

load('helicopter2\input2.mat');
load('helicopter2\travel2.mat');
load('helicopter2\pitch2.mat');
load('helicopter2\elevation2.mat');

%set(groot, 'defaultAxesColorOrder', co);
%colord = get(gca,'ColorOrder')
subplot(411);
plot(input2(1,:), input2(2,:));
title('Input');
hleg = legend('$p_c$');
set(hleg, 'Interpreter', 'Latex');
box('on');
grid('on');
ylim([ -0.55, 0.55]);
ylabel('Rad');
xlabel('t');

subplot(412)
plot(travel2(1,:), travel2(2,:));
title('Travel');
box('on');
grid('on');
hleg = legend('$\lambda$');
set(hleg, 'Interpreter', 'Latex');
ylim([ -270, 180]);
ylabel('deg');
xlabel('t');


subplot(413)
plot(input2(1,:), input2(2,:)*(180/pi), '--', 'linewidth', 2);
hold on;
plot(pitch2(1,:), pitch2(2,:), 'r-');
plot(t, u*(180/pi), 'g:', 'linewidth', 2);
hold off;
title('Pitch');
hleg = legend('$p_c$','$p$', '$opt$');
set(hleg, 'Interpreter', 'Latex');
box('on');
grid('on');
ylim([ -35, 35]);
ylabel('deg');
xlabel('t');

subplot(414)
plot(elevation2(1,:), elevation2(2,:));
box('on');
grid('on');
hleg = legend('$e$');
set(hleg, 'Interpreter', 'Latex');
ylim([ -30, 30]);
ylabel('deg');
xlabel('t');
title('Elevation');