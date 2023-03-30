t=MD1.time;
u=MD1.signals(1).values(:,1);
y=MD1.signals(1).values(:,2);

y_inf=3;
u_inf=2;

K=y_inf / u_inf;
T=0.5;
G=tf(K, [T 1]);

ym=lsim(G, u, t);

plot(t,u,t,y,t,ym);
xlabel('Time/s');
ylabel('Signals/V');
legend({'u', 'y', 'y_M'});
title('Validation of System 1');
