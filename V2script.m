t=MD2.time;
u=MD2.signals(1).values(:,1);
y=MD2.signals(1).values(:,2);

y_inf=1.52;
u_inf=2;
y_max=1.966;

K=y_inf / u_inf;
T=1.275;
Mp=0.31;
Omega=(2*pi)/T;
D=0.365;
Omega0=Omega/sqrt(1-D*D);
G=tf(K, [1/Omega0^2 2*D/Omega0 1]);

ym=lsim(G, u, t);

plot(t,u,t,y,t,ym);
xlabel('Time/s');
ylabel('Signals/V');
legend({'u', 'y', 'y_M'});
title('Validation of System 2');
