(defun next-y-rk4 (x y F h)
  (let ((k (list y)))
    (dolist (m '(0 .5d0 .5d0 1))
      (push (mapcar #'(lambda (x) (* h x))
                   (mapcar #'apply F (loop repeat (length F) collect
                        (mapcar #'(lambda (a b) (+ a (* m b))) (cons x y) (cons h (first k))))))
        k))
    (mapcar #'(lambda (x k1 k2 k3 k4) (+ x (/ (+ k1 (* 2 k2) (* 2 k3) k4) 6)))
        y (fourth k) (third k) (second k) (first k))))

(defmacro solve-rk4 (initial-values x0 x1 h F)
  `(let ((y ,initial-values) (result nil))
     (loop for x from ,x0 below ,x1 by ,h do
       (setf y (next-y-rk4 x y ,F ,h))
       (push (cons (+ ,h x) y) result))
     (reverse result)))

(defun f1 (x y1 y2)
  (- 1 y2))

(defun f2 (x y1 y2)
  (- y1 x))

(defparameter *h* 0.01d0 "Step for RK4")
(defparameter *initial-values* '(1.0d0 0.0d0) "Initial values f1(x0), f2(x0), ...")
(defparameter *x0* 0.0d0)
(defparameter *x1* 3.0d0)

(setf v (solve-rk4 *initial-values* *x0* *x1* *h* '(f1 f2)))
