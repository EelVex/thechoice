import graph;

size(250,200,IgnoreAspect);

real Sin(real t, real w) {return sin(w*t);}

draw(graph(new real(real t) {return cos(t)+t;},0,3),blue,"$\cos(x)+x$");
draw(graph(new real(real t) {return sin(t);},0,3),red,"$\sin(x)$");

xaxis("$x$",BottomTop,Ticks);
yaxis("$f(x)$",LeftRight,Ticks);

attach(legend(),point(E),20E,UnFill);
