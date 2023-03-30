Ts=0.01;
w=MD_P.signals(1).values(:,1);

% P controller:
t_p=MD_P.time;
y_p=MD_P.signals(1).values(:,2);
u_p=MD_P.signals(2).values(:,1);

% PI controller:
t_pi=MD_PI.time;
y_pi=MD_PI.signals(1).values(:,2);
u_pi=MD_PI.signals(2).values(:,1);


% PID controller:
t_pid=MD_PID.time;
y_pid=MD_PID.signals(1).values(:,2);
u_pid=MD_PID.signals(2).values(:,1);

subplot(2,1,1);
plot(t_p,w, t_p,y_p, t_pi,y_pi, t_pid,y_pid);

xlabel('Time/s');
ylabel('Signals/V');
legend({'w', 'Y_{P}', 'Y_{PI}', 'Y_{PID}'});
title('System output with different controllers');

subplot(2,1,2);
plot(t_p,u_p, t_pi,u_pi, t_pid,u_pid);
xlabel('Time/s');
ylabel('Signals/V');
legend({'U_{P}', 'U_{PI}', 'U_{PID}'});
title('Controls signals');
