step =: 3 : 0
    a =: (Fs`:0) ({:v)
    b =: (Fs`:0) ({:v) + 2%~dx*(1,a)
    c =: (Fs`:0) ({:v) + 2%~dx*(1,b)
    d =: (Fs`:0) ({:v) + dx*(1,c)

    D =: dx*6%~+/(1 2 2 1) * |:(a,.b,.c,.d)

    v =: v, (({:v) + (dx, D))
)

F1 =: 3 :'1 - 2{y'
F2 =: 3 :'-/ 1 0 { y'
Fs =: F1`F2

dx =: 0.01

v =: ,:0 1 0     NB. Vector of initial values 'x0, y1, y2'

(step^:300) 0   NB. Run 300 steps
