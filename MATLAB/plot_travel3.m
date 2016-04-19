%% Plot travel 
%figure(3);
%plot(travel.time, travel.signals.values);

%figure(5);
%plot(scope_travel.time, scope_travel.signals.values);

figure(3);
folder='helicopter3\';
load([folder, 'optinput3.mat']);
load([folder, 'input3.mat']);
load([folder, 'travel3.mat']);
load([folder, 'pitch3.mat']);
load([folder, 'elevation3.mat']);


subplot(511);
plot(input3(1,:), input3(2,:));
title('Input');
hleg = legend('$p$');
set(hleg, 'Interpreter', 'Latex');
box('on');
grid('on');
ylim([ -0.55, 0.55]);
ylabel('Rad');
xlabel('t');

subplot(512)
plot(optinput3(1,:), optinput3(2,:));
hold on;
plot(input3(1,:), input3(2,:), 'r');
hold off;
title('OptimalInput');
hleg = legend('$u^*$','$p$');
set(hleg, 'Interpreter', 'Latex');
ylim([ -0.60, 0.60]);
ylabel('Rad');
xlabel('t');
box('on');
grid('on');

subplot(513)
plot(travel3(1,:), travel3(2,:));
title('Travel');
hold on;
plot(t,x1*(180/pi)-180, 'r');
hold off;
box('on');
grid('on');
hleg = legend('$\lambda$', '$\lambda_{opt}$');
set(hleg, 'Interpreter', 'Latex');
ylim([ -220, 60]);
ylabel('deg');
xlabel('t');

subplot(514)
plot(pitch3(1,:), pitch3(2,:));
title('Pitch');
hold on;
plot(t,x3*(180/pi), 'r');
hold off;
hleg = legend('$p_c$','$p$');
set(hleg, 'Interpreter', 'Latex');
box('on');
grid('on');
ylim([ -35, 35]);
ylabel('deg');
xlabel('t');

subplot(515)
plot(elevation3(1,:), elevation3(2,:));
title('Elevation');
box('on');
grid('on');
hleg = legend('$e$');
set(hleg, 'Interpreter', 'Latex');
ylim([ -30, 30]);
ylabel('deg');
xlabel('t');

